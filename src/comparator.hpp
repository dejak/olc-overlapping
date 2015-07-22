#ifndef COMPARATOR_HPP_
#define COMPARATOR_HPP_

#include <vector>
#include <tuple>

#include "overlap.hpp"
#include "nucleotide.hpp"

namespace OLC
{

// Helper class representing an (i, j) coordinate in the matrix formed by carthesian product of two vectors x and y.
// Decodes to x[i] and y[j] to enable backtracking to find the longest overlap of the vectors.
using Position = std::tuple<uint32_t, uint32_t>;

// Compares two vectors to find the longest possible overlap using the Smith-Waterman algorithm with a bit of a 
// bigger price for insertions and removals to allow for more strict overlaps while maintaining the possibility
// to handle large error reads.
template <typename T>
Overlap compare(const std::vector<T>& first, const std::vector<T>& second)
{
  std::vector<std::vector<int32_t>> values;
  std::vector<std::vector<Position>> positions;

  for (std::size_t i = 0; i < first.size() + 1; ++i)
  {
    std::vector<int32_t> row;
    std::vector<Position> positionRow;

    for (std::size_t j = 0; j < second.size() + 1; ++j)
    {
      row.emplace_back(0);
      positionRow.emplace_back(0, 0);
    }

    values.push_back(row);
    positions.push_back(positionRow);
  }

  int32_t maxValue = 0;
  Position maxPosition(0, 0);

  for (std::size_t  i = 1; i < first.size() + 1; ++i)
  {
    for (std::size_t  j = 1; j < second.size() + 1; ++j)
    {
      const int32_t up    = values[i-1][j] - 15;
      const int32_t left  = values[i][j-1] - 15;
      int32_t diagonal    = values[i-1][j-1] - 8;

      if (first[i-1] == second[j-1])
        diagonal += 18;

      if (up > left && up > diagonal)
      {
        values[i][j] = up;
        const Position prev(i - 1, j);
        positions[i][j] = prev;

        if (up > maxValue)
        {
          maxValue = up;
          maxPosition = prev;
        }
      }
      else if (left > up && left > diagonal)
      {
        values[i][j] = left;
        const Position prev(i, j - 1);
        positions[i][j] = prev;

        if (left > maxValue)
        {
          maxValue = left;
          maxPosition = prev;
        }
      }
      else
      {
        values[i][j] = diagonal;
        const Position prev(i - 1, j - 1);
        positions[i][j] = prev;

        if (diagonal > maxValue)
        {
          maxValue = diagonal;
          maxPosition = prev;
        }
      }
    }
  }

  std::vector<Position> path;
  Position current = maxPosition;

  while (true)
  {
    if (values[std::get<0>(current)][std::get<1>(current)] == 0)
      break;

    path.push_back(current);
    current = positions[std::get<0>(current)][std::get<1>(current)];
  }

  return Overlap(std::get<0>(path[path.size()-1]), std::get<0>(path[0]), std::get<1>(path[path.size()-1]), std::get<1>(path[0]));
}

}

#endif // COMPARATOR_HPP_
