#ifndef MINIMIZATOR_HPP_
#define MINIMIZATOR_HPP_

#include "nucleotides.hpp"
#include "minimizer.hpp"

namespace OLC
{
  std::vector<Minimizer> minimize(const std::vector<Nucleotide>& nucleotides, const int w, const int k);
}

#endif // MINIMIZATOR_HPP_
