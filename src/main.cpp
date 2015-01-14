#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <tuple>
#include <condition_variable>
#include <algorithm>

#include "input_file_reader.hpp"
#include "minimize.hpp"
#include "comparator.hpp"
#include "result.hpp"
#include "minimizer.hpp"

// mutex for shared resources
static std::mutex g_resource_mutex;

// mutex for result vector
static std::mutex g_result_mutex;

// global queue with two pointers to the sequences
// they are compared directly if the both sequence lengths are small enough
static std::queue<std::tuple<uint32_t, OLC::Sequence*, uint32_t, OLC::Sequence*>> g_sequence_pairs;

// global queue with two pointers to vectors of minimizers
// we use this instead if the sequences are too long
static std::queue<std::tuple<uint32_t, std::vector<OLC::Minimizer>*, uint32_t, std::vector<OLC::Minimizer>*>> g_minimizer_pairs;

// global vector with results
static std::vector<OLC::Result*> g_results;

static const uint32_t SEQUENCE_THRESHOLD_LENGTH = 20000;

void worker()
{
  while(true)
  {
    // Get the task and remove it from the pool
    uint32_t first_read_number;
    OLC::Sequence* first_sequence;
    std::vector<OLC::Minimizer>* first_minimizer;

    uint32_t second_read_number;
    OLC::Sequence* second_sequence;
    std::vector<OLC::Minimizer>* second_minimizer;

    {
      std::lock_guard<std::mutex> resource_lock(g_resource_mutex);

      if (g_sequence_pairs.empty())
        return;

      std::tie(first_read_number, first_sequence, second_read_number, second_sequence) = g_sequence_pairs.front();
      g_sequence_pairs.pop();
      std::tie(first_read_number, first_minimizer, second_read_number, second_minimizer) = g_minimizer_pairs.front();
      g_minimizer_pairs.pop();
    }

    // Pull out the wrapped nucleotide vectors
    const std::vector<OLC::Nucleotide> nucleotides1 = first_sequence->getNucleotides()->getSequence();
    const std::vector<OLC::Nucleotide> nucleotides2 = second_sequence->getNucleotides()->getSequence();

    // If small enough, no need to use minimizers
    if (nucleotides1.size() < SEQUENCE_THRESHOLD_LENGTH && nucleotides2.size() < SEQUENCE_THRESHOLD_LENGTH)
    {
      const OLC::Overlap overlap = compare(nucleotides1, nucleotides2);
      const uint32_t overlapFirstEnd = overlap.getEndFirst();
      const uint32_t overlapSecondEnd = overlap.getEndSecond();
      const uint32_t overlapFirstStart = overlap.getStartFirst();
      const uint32_t overlapSecondStart = overlap.getStartSecond();
      const uint32_t overlapLength = overlapFirstEnd - overlapFirstStart + 1;

      int32_t ahang = overlapFirstStart;
      int32_t bhang = nucleotides2.size() - overlapSecondEnd;

      if (overlapSecondStart > overlapFirstStart)
        ahang *= -1;

      if (nucleotides1.size() > overlapSecondEnd)
        bhang *= -1;

      OLC::Result* result = new OLC::Result(first_read_number, second_read_number, overlapLength, ahang, bhang);

      {
        std::lock_guard<std::mutex> result_lock(g_result_mutex);
        g_results.push_back(result);
      }
    }
    else
    {
      std::vector<OLC::Minimizer> allMinimizers; 
      for (size_t i = 0; i < first_minimizer -> size(); i++) {
        allMinimizers.push_back((*first_minimizer)[i]);
      }
      std::sort(allMinimizers.begin(), allMinimizers.end());
      for (size_t i = 0; i < second_minimizer -> size(); i++) { 
        if (!std::binary_search(allMinimizers.begin(), allMinimizers.end(), (*second_minimizer)[i])) {
          allMinimizers.push_back((*second_minimizer)[i]);
        }
      }
      std::sort(allMinimizers.begin(), allMinimizers.end());

      std::vector<int> codedSequence1;
      for (size_t i = 0; i < first_minimizer -> size(); i++) {
        auto lower = std::lower_bound(allMinimizers.begin(), allMinimizers.end(), (*first_minimizer)[i]);
        int index = std::distance(allMinimizers.begin(), lower);
        codedSequence1.push_back(index);
      }

      std::vector<int> codedSequence2;
      for (size_t i = 0; i < second_minimizer -> size(); i++) {
        auto lower = std::lower_bound(allMinimizers.begin(), allMinimizers.end(), (*second_minimizer)[i]);
        int index = std::distance(allMinimizers.begin(), lower);
        codedSequence2.push_back(index);
      }
 
      const OLC::Overlap overlap = OLC::compare(codedSequence1, codedSequence2);
      const uint32_t overlapFirstEnd = (*first_minimizer)[overlap.getEndFirst()].getPosition() + (*first_minimizer)[overlap.getEndFirst()].size();
      const uint32_t overlapSecondEnd = (*second_minimizer)[overlap.getEndSecond()].getPosition() + (*second_minimizer)[overlap.getEndSecond()].size();
      const uint32_t overlapFirstStart = (*first_minimizer)[overlap.getStartFirst()].getPosition();
      const uint32_t overlapSecondStart = (*second_minimizer)[overlap.getStartSecond()].getPosition();
      const uint32_t overlapLength = overlapFirstEnd - overlapFirstStart + 1;
      int32_t ahang = overlapFirstStart;
      int32_t bhang = nucleotides2.size() - overlapSecondEnd;

      if (overlapSecondStart > overlapFirstStart)
        ahang *= -1;

      if (nucleotides1.size() > overlapSecondEnd)
        bhang *= -1;

      OLC::Result* result = new OLC::Result(first_read_number, second_read_number, overlapLength, ahang, bhang);

      {
        std::lock_guard<std::mutex> result_lock(g_result_mutex);
        g_results.push_back(result);
      }

    }
  }
}

int main(int argc, char** argv)
{
  std::ios_base::sync_with_stdio(false);

  if (argc != 3)
  {
    std::cout << "Usage: " << argv[0] << " <minimum overlap length L> <FASTQ or FASTA file>\n";
    return 1;
  }

  // file with the data
  const std::string file = std::string(argv[2]);

  // L is the minimum overlap length
  const uint32_t L = std::stoi(argv[1]);

  // window size
  const uint32_t w = (L + 1) / 2;

  // size of the k-mer
  const uint32_t k = (L + 1) / 2;

  // read phase
  OLC::InputFileReader reader(file);
  const std::vector<OLC::Sequence*> sequences = reader.readSequences();
  std::vector<std::vector<OLC::Minimizer>> minimizers;

  for (size_t i = 0; i < sequences.size(); ++i)
  {
    const auto sequence = sequences[i]->getNucleotides()->getSequence();

    // calculate minimizers - both interior and end minimizers
    if (sequence.size() >= SEQUENCE_THRESHOLD_LENGTH)
      minimizers.push_back(minimize(sequence, w, k));
    else
      minimizers.push_back(std::vector<OLC::Minimizer>());
  }

  // generate tasks so we can do this in parallel if possible
  std::queue<std::tuple<uint32_t, uint32_t>> tasks;

  for (uint32_t i = 0; i < sequences.size(); ++i)
  {
    for (uint32_t j = i + 1; j < sequences.size(); ++j)
    {
      g_sequence_pairs.emplace(i + 1, sequences[i], j + 1, sequences[j]);
      g_minimizer_pairs.emplace(i + 1, &minimizers[i], j + 1, &minimizers[j]);
    }
  }

  // use concurrent minimizer matching
  std::vector<std::thread> threads(std::thread::hardware_concurrency());

  for (uint8_t i = 0; i < threads.size(); ++i)
    threads[i] = std::thread(worker);

  for (uint8_t i = 0; i < threads.size(); ++i)
    threads[i].join();

  for (size_t i = 0; i < g_results.size(); ++i)
  {
    auto identifiers = g_results[i]->getIdentifiers();

    std::cout << "Found overlap with length of " << g_results[i]->getLength() << " between " << std::get<0>(identifiers) << " and " << std::get<1>(identifiers) << "\n";
  }

  // cleanup
  for (size_t i = 0; i < sequences.size(); ++i)
    delete sequences[i];

  for (size_t i = 0; i < g_results.size(); ++i)
    delete g_results[i];

  return 0;
}
