#include "minimizer.hpp"

namespace OLC
{

Minimizer::Minimizer(const std::vector<Nucleotide> &vector, const int position)
  : vector_(vector),
    position_(position)
{

}

Minimizer::Minimizer(uint32_t size)
  : vector_(std::vector<Nucleotide>(size, Nucleotide(NucleotideLetter::G)))
{

}


Nucleotide Minimizer::operator[](unsigned int index) const
{
  return vector_[index];
}

std::size_t Minimizer::size() const
{
  return vector_.size();
}

std::string Minimizer::toValueString() const
{
  std::string output(size(), '\0');

  for (std::size_t i = 0; i < size(); ++i)
    output[i] = static_cast<char>(vector_[i].getValue() + 48);

  return output;
}

std::string Minimizer::toNucleotideString() const
{
  std::string output(size(), '\0');

  for (std::size_t i = 0; i < size(); ++i)
    output[i] = vector_[i].getNucleotide();

  return output;
}

}
