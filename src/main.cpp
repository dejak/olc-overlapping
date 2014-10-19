#include <iostream>
#include <memory>

#include "reader.hpp"
#include "sequence.hpp"

int main(int argc, char** argv)
{
  std::ios_base::sync_with_stdio(false);

  // TODO (josko): use getopts

  if (argc != 3)
  {
    std::cout << "Usage " << argv[0] << " <overlap length L> <fastq file>\n";
    return 1;
  }

  const int L = std::stoi(argv[1]);
  const std::string file = std::string(argv[2]);

  // read phase

  std::unique_ptr<FASTQ::Reader> reader(new FASTQ::Reader(file));
  std::vector<FASTQ::Sequence> sequences = reader.get()->_readSequences();

  // calculate minimizers

  // find overlaps

  return 0;
}
