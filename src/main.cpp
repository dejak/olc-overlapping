#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <tuple>

#include "input_file_reader.hpp"
#include "minimize.hpp"
#include "comparator.hpp"

// mutex that locks the resources that are shared
static std::mutex g_tasks_mutex;

// global queue with two pointers to the sequences
// they are compared directly if the both sequence lengths are small enough
static std::queue<std::tuple<OLC::Sequence*, OLC::Sequence*>> g_sequence_pairs;

// global queue with two pointers to vectors of minimizers
// we use this instead if the sequences are too long
static std::queue<std::tuple<std::vector<OLC::Minimizer>*, std::vector<OLC::Minimizer>*>> g_minimizer_pairs;

static void worker()
{
  std::tuple<uint32_t, uint32_t> task = g_tasks.front();

  return;
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
      g_sequence_pairs.emplace(sequences[i], sequences[j]);
      g_minimizer_pairs.emplace(&minimizers[i], &minimizers[j]);
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

  return 0;
}
