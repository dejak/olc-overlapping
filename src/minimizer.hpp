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
    Nucleotide operator[](unsigned int index) const;
    std::size_t size() const;
    int getPosition() const {return position_;}

    bool operator==(const Minimizer &other) const;
    std::string toValueString() const;
    std::string toNucleotideString() const;
};

bool operator<(const Minimizer &first, const Minimizer &second);

}


#endif
