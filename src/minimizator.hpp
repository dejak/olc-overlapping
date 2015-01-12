#ifndef MINIMIZATOR_HPP_
#define MINIMIZATOR_HPP_

#include "nucleotides.hpp"
#include "minimizer.hpp"

namespace OLC
{

  // Returns all the (w, k) inner and outer minimizers as defined in the (Roberts, 04) paper
  std::vector<Minimizer> minimize(const std::vector<Nucleotide>& nucleotides, const int w, const int k);
}

#endif // MINIMIZATOR_HPP_
