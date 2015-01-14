#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <tuple>
#include <condition_variable>

#include "input_file_reader.hpp"
#include "minimize.hpp"
#include "comparator.hpp"
#include "result.hpp"

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
    if (nucleotides1.size() < 20000 && nucleotides2.size() < 20000)
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
    minimizers.push_back(minimize(sequence, w, k));
  }

  // generate tasks so we can do this in parallel if possible
  std::queue<std::tuple<uint32_t, uint32_t>> tasks;

  for (uint32_t i = 0; i < sequences.size(); ++i)
  {
    for (uint32_t j = i + 1; j < sequences.size(); ++j)
    {
      g_sequence_pairs.emplace(i, sequences[i], j, sequences[j]);
      g_minimizer_pairs.emplace(i, &minimizers[i], j, &minimizers[j]);
    }
  }

  // use concurrent minimizer matching
  std::vector<std::thread> threads(std::thread::hardware_concurrency());

  for (uint8_t i = 0; i < threads.size(); ++i)
    threads[i] = std::thread(worker);

  for (uint8_t i = 0; i < threads.size(); ++i)
    threads[i].join();

  // cleanup
  for (size_t i = 0; i < sequences.size(); ++i)
    delete sequences[i];

  for (size_t i = 0; i < g_results.size(); ++i)
    delete g_results[i];

  return 0;
}
