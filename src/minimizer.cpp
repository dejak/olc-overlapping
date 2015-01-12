#include "minimizer.hpp"

namespace OLC
{

Minimizer::Minimizer(const std::vector<Nucleotide> &vector, const int position)
  :vector_(vector), position_(position)
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

Nucleotide Minimizer::operator[](unsigned int index) const
{
  return vector_[index];
}

std::size_t Minimizer::size() const
{
  return vector_.size();
}

}
