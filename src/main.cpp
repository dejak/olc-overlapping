#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <tuple>

#include "input_file_reader.hpp"
#include "minimize.hpp"
#include "comparator.hpp"

static std::mutex g_tasks_mutex;
static std::queue<std::tuple<uint32_t, uint32_t>> g_tasks;

static void worker()
{
  const std::thread::id this_id = std::this_thread::get_id();

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
  std::vector<OLC::Sequence*> sequences = reader.readSequences();

  for (size_t i = 0; i < sequences.size(); ++i)
  {
    auto sequence = sequences[i]->getNucleotides()->getSequence();

    // calculate minimizers - both interior and end minimizers
    auto minimizers = minimize(sequence, w, k);
  }

  // generate basically tasks so we can do this in parallel if possible
  std::queue<std::tuple<uint32_t, uint32_t>> tasks;

  for (uint32_t i = 0; i < sequences.size(); ++i)
  {
    for (uint32_t j = i + 1; j < sequences.size(); ++j)
    {
      std::cout << "job (" << i << "," << j << ")\n";
      g_tasks.emplace(i, j);
    }
  }

  // use concurrent minimizer matching
  std::vector<std::thread> threads(std::thread::hardware_concurrency());

  for (uint8_t i = 0; i < threads.size(); ++i)
  {
    std::cout << "Thread [" << static_cast<int>(i + 1) << "] spawned\n";
    threads[i] = std::thread(worker);
  }

  for (uint8_t i = 0; i < threads.size(); ++i)
    threads[i].join();

  // cleanup
  for (size_t i = 0; i < sequences.size(); ++i)
    delete sequences[i];

  return 0;
}
