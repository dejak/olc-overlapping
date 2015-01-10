#ifndef MINIMIZATOR_HPP_
#define MINIMIZATOR_HPP_

#include "nucleotides.hpp"
#include "minimizer.hpp"

namespace OLC
{
  std::vector<Minimizer> minimize(std::vector<Nucleotide> nucleotides, int w, int k);
}

#endif
