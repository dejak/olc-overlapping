#ifndef MINIMIZATOR_HPP_
#define MINIMIZATOR_HPP_

#include "nucleotides.hpp"

namespace OLC
{
	std::vector<std::vector<Nucleotide>> minimize(std::vector<Nucleotide> nucleotides, int w, int k);
}

#endif