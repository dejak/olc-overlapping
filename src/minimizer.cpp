#include "minimizer.hpp"

namespace OLC
{

Minimizer::Minimizer(const std::vector<Nucleotide> &vector, const int position)
  : vector_(vector),
    position_(position)
{

}

Minimizer::Minimizer(uint32_t size)
  : vector_(std::vector<Nucleotide>(size, Nucleotide(NucleotideLetter::A)))
{

}

bool operator<(const Minimizer &first, const Minimizer &second)
{
  for (std::size_t i = 0; i < first.size(); ++i)
  {
    if (first[i].getValue() < second[i].getValue())
    {
      return true;
    }

    if (first[i].getValue() > second[i].getValue())
    {
      return false;
    }
  }

  return false;
}

bool Minimizer::operator==(const Minimizer &other) const
{
  const std::size_t thisSize = size();
  const std::size_t otherSize = other.size();

  if (thisSize != otherSize)
    return false;

  for (std::size_t i = 0; i < thisSize; ++i)
  {
    if (vector_[i].getValue() != other[i].getValue())
      return false;
  }

  return true;
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
