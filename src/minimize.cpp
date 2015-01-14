#include "minimize.hpp"

#include <algorithm>

namespace OLC
{

// Helper function returning a slice of the given vector from start to end position (start included, end not included)
static std::vector<Nucleotide> slice(const std::vector<Nucleotide>& vector, int start = 0, int end = -1)
{
  int oldlen = vector.size();
  int newlen;

  if (end == -1 || end >= oldlen)
    newlen = oldlen - start;
  else
    newlen = end - start;

  std::vector<Nucleotide> nv;
  for (int i = 0; i < newlen; ++i)
    nv.push_back(vector[start + i]);

  return nv;
}

// Finds all the subvectors of length k of the original vector
static std::vector<Minimizer> findKMers(const std::vector<Nucleotide> &vector, const int k, const int offset)
{
  std::vector<Minimizer> kMers;

  for (std::size_t i = 0; i < vector.size() - k + 1; ++i)
    kMers.push_back(Minimizer(slice(vector, i, i+k), i + offset));

  std::sort(kMers.begin(), kMers.end());
  return kMers;
}

// Find all the inner minimizers of the vector. Inner (w, k) minimizers are defined as the minimal set of vectors
// of length k that can represent the original vector and they are retrieved using a sliding vector covering w
// k-mers and returning always the one which is first alphabetically (alphabet order defined as in the paper introducing
// this algorithm).
static std::vector<Minimizer> findInnerMinimizers(const std::vector<Nucleotide> &vector, const int w, const int k)
{
  std::vector<Minimizer> minimizers;

  for (std::size_t i = 0; i < vector.size() - w - k + 2; ++i)
  {
    const std::vector<Nucleotide> window = slice(vector, i, i + w + k - 1);
    const std::vector<Minimizer> kMers = findKMers(window, k, i);
    const Minimizer minimizer = kMers[0];
    minimizers.push_back(minimizer);
  }

  return minimizers;
}

//Grabs the 2 minimizers on the edges of the vector as it is often the case they are not included
//in the inner minimizers
static std::vector<Minimizer> findOuterMinimizers(const std::vector<Nucleotide> &vector, const int k)
{
  std::vector<Minimizer> minimizers;

  minimizers.push_back(Minimizer(slice(vector, 0, k), 0));
  minimizers.push_back(Minimizer(slice(vector, vector.size() - k, vector.size()), vector.size() - k));

  return minimizers;
}

std::vector<Minimizer> minimize(const std::vector<Nucleotide>& nucleotideVector, const int w, const int k)
{
  std::vector<Minimizer> minimizers;

  const std::vector<Minimizer> innerMinimizers = findInnerMinimizers(nucleotideVector, w, k);
  const std::vector<Minimizer> outerMinimizers = findOuterMinimizers(nucleotideVector, k);

  minimizers.insert(minimizers.end(), innerMinimizers.begin(), innerMinimizers.end());
  minimizers.insert(minimizers.end(), outerMinimizers.begin(), outerMinimizers.end());

  std::sort(minimizers.begin(), minimizers.end());

  std::vector<Minimizer> uniqueMinimizers;

  for (std::size_t i = 0; i < minimizers.size(); i++) {
    if (!std::binary_search(uniqueMinimizers.begin(), uniqueMinimizers.end(), minimizers[i])) {
      uniqueMinimizers.push_back(minimizers[i]);
    }
  }

  return uniqueMinimizers;
}

}
