#ifndef COMPARATOR_HPP_
#define COMPARATOR_HPP_

#include <vector>

namespace OLC
{

// Helper class representing an (i, j) coordinate in the matrix formed by carthesian product of two vectors x and y.
// Decodes to x[i] and y[j] to enable backtracking to find the longest overlap of the vectors.
class Position
{
  private:
    int i_, j_;
  public:
    Position(const int i, const int j);
    int get(int index) const;
};

// Compares two vectors to find the longest possible overlap using the Smith-Waterman algorithm with a bit of a 
// bigger price for insertions and removals to allow for more strict overlaps while maintaining the possibility
// to handle large error reads.
std::vector<Position> compare(const std::vector<int>& first, const std::vector<int>& second);

}

#endif // COMPARATOR_HPP_
