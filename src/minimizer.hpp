#ifndef MINIMIZER_HPP_
#define MINIMIZER_HPP_

#include <vector>
#include <string>

#include "nucleotide.hpp"

namespace OLC
{

// Class representing the minimizer of a vector of nucleotides of a given length, while also storing the position of the
// start of the minimizer in the original vector. Operations on the minimizer are the same as if working with a vector of
// nucleotides
class Minimizer
{
  private:
    std::vector<Nucleotide> vector_;
    int position_;

  public:
    Minimizer(const std::vector<Nucleotide> &vector, const int position);
    Minimizer(uint32_t size);
    Nucleotide operator[](unsigned int index) const;
    std::size_t size() const;
    int getPosition() const {return position_;}

    std::string toValueString() const;
    std::string toNucleotideString() const;
};

inline bool operator<(const Minimizer &first, const Minimizer &second)
{
  for (std::size_t i = 0; i < first.size(); ++i)
  {
    if (first[i].getValue() < second[i].getValue())
      return true;

    if (first[i].getValue() > second[i].getValue())
      return false;
  }

  return false;
}

inline bool operator==(const Minimizer& first, const Minimizer &second)
{
  const std::size_t thisSize = first.size();
  const std::size_t otherSize = second.size();

  if (thisSize != otherSize)
    return false;

  for (std::size_t i = 0; i < thisSize; ++i)
  {
    if (first[i].getValue() != second[i].getValue())
      return false;
  }

  return true;
}

}


#endif
