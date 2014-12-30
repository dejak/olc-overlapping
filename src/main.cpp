#include <iostream>
#include <memory>

#include "reader.hpp"
#include "sequence.hpp"

int main(int argc, char** argv)
{
  std::ios_base::sync_with_stdio(false);

  // TODO (josko): use getopts?

  if (argc != 3)
  {
    std::cout << "Usage " << argv[0] << " <overlap length L> <fastq file>\n";
    return 1;
  }

  // L = w + k -1 with w <= k

  const uint32_t L = std::stoi(argv[1]);
  const std::string file = std::string(argv[2]);

  // read phase

  std::unique_ptr<OLC::FASTQReader> reader(new OLC::FASTQReader(file));
  std::vector<OLC::FASTQSequence> sequences = reader.get()->readSequences();

  // calculate minimizers - both interior and end minimizers

  // find overlaps

  return 0;
}
