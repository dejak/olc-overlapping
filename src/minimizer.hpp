#ifndef MINIMIZER_HPP_
#define MINIMIZER_HPP_

#include <vector>
#include <string>

#include "nucleotide.hpp"

namespace OLC
{

class Minimizer
{
  private:
    std::vector<Nucleotide> vector_;
    int position_;

  public:
    Minimizer(const std::vector<Nucleotide> &vector, const int position);
    void push_back(const Nucleotide &nucleotides);
    Nucleotide operator[](unsigned int index) const;
    std::size_t size() const;
    int getPosition() const;

    bool operator==(const Minimizer &other) const;
    std::string toString() const;
};

bool operator<(const Minimizer &first, const Minimizer &second);

}


#endif
