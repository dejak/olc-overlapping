#include <iostream>

#include "input_file_reader.hpp"
#include "minimize.hpp"
#include "comparator.hpp"

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
    auto vec = sequences[i]->getNucleotides()->getSequence();

    // calculate minimizers - both interior and end minimizers
    auto minimizers = minimize(vec, w, k);
  }

  // TODO: Maknuti nakon testinga

  // find overlaps
  std::vector<int> first;
  first.push_back(3);
  first.push_back(1);
  first.push_back(1);
  first.push_back(2);
  first.push_back(4);
  first.push_back(3);
  std::vector<int> second;
  second.push_back(4);
  second.push_back(1);
  second.push_back(2);
  second.push_back(4);
  second.push_back(2);
  second.push_back(1);

  std::vector<OLC::Position> overlapPath = OLC::compare(first, second);
  int overlapFirstEnd = overlapPath[0].get(0);
  int overlapSecondEnd = overlapPath[0].get(1);
  int overlapFirstStart = overlapPath[overlapPath.size() - 1].get(0);
  int overlapSecondStart = overlapPath[overlapPath.size() - 1].get(1);
  std::cout << "Preklapanje duljine " << overlapPath.size() << std::endl;
  for (int i  = overlapFirstStart; i <= overlapFirstEnd; i++) {
    std::cout << first[i] << " ";
  }
  std::cout << std::endl;
  for (int i = overlapSecondStart; i <= overlapSecondEnd; i++) {
    std::cout << second[i] << " ";
  }
  std::cout << std::endl;

  // cleanup
  for (size_t i = 0; i < sequences.size(); ++i)
    delete sequences[i];

  return 0;
}
