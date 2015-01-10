#ifndef MINIMIZER_HPP_
#define MINIMIZER_HPP_

#include <vector>

#include "nucleotide.hpp"

namespace OLC
{

class Minimizer
{
  private:
    std::vector<Nucleotide> vector_;

  public:
    Minimizer(const std::vector<Nucleotide> &vector);
    void push_back(const Nucleotide &nucleotides);
    Nucleotide operator[](unsigned int index) const;
    std::size_t size() const;

};

bool operator<(const Minimizer &first, const Minimizer &second);

}


#endif
