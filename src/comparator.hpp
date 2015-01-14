#ifndef COMPARATOR_HPP_
#define COMPARATOR_HPP_

#include <vector>
#include "overlap.hpp"
#include "nucleotide.hpp"

namespace OLC
{

// Compares two vectors to find the longest possible overlap using the Smith-Waterman algorithm with a bit of a 
// bigger price for insertions and removals to allow for more strict overlaps while maintaining the possibility
// to handle large error reads.
Overlap compare(const std::vector<int32_t>& first, const std::vector<int32_t>& second);
Overlap compare(const std::vector<Nucleotide>& first, const std::vector<Nucleotide>& second);

}

#endif // COMPARATOR_HPP_
