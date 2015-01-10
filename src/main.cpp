#include <iostream>

#include "input_file_reader.hpp"
#include "minimizator.hpp"

int main(int argc, char** argv)
{
  std::ios_base::sync_with_stdio(false);

  if (argc != 3)
  {
    std::cout << "Usage " << argv[0] << " <minimum overlap length L> <FASTQ or FASTA file>\n";
    return 1;
  }

  // L = w + k -1 with w <= k

  const uint32_t L = std::stoi(argv[1]);
  const std::string file = std::string(argv[2]);

  const uint32_t w = (L + 1) / 2;
  const uint32_t k = (L + 1) / 2;

  // read phase

  OLC::InputFileReader reader(file);
  std::vector<std::unique_ptr<OLC::Sequence>> sequences = reader.readSequences();

  // calculate minimizers - both interior and end minimizers
  // TODO: Maknuti nakon testinga
  std::vector<OLC::Nucleotide> vec;
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x02)));
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x03)));
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x01)));
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x00)));
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x03)));
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x02)));
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x01)));
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x00)));
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x01))); 
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x02)));
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x03))); 
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x03)));
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x01)));
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x00)));
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x01)));  


  minimize(vec, w, k);


  // find overlaps

  return 0;
}
