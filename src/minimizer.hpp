#ifndef MINIMIZER_HPP_
#define MINIMIZER_HPP_

#include "nucleotides.hpp"

namespace OLC
{
	std::vector<std::vector<Nucleotide>> minimize(std::vector<Nucleotide> nucleotides, int w, int k);
}

#endif