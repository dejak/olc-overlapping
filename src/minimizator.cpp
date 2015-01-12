#include "minimizator.hpp"

#include <iostream> 
#include <algorithm>

namespace OLC
{

static std::vector<Nucleotide> slice(const std::vector<Nucleotide>& vector, int start = 0, int end = -1)
{
  int oldlen = vector.size();
  int newlen;

  if (end == -1 || end >= oldlen)
  {
    newlen = oldlen - start;
  }
  else
  {
    newlen = end - start;
  }

  std::vector<Nucleotide> nv;
  for (int i = 0; i < newlen; ++i)
  {
    nv.push_back(vector[start + i]);
  }

  return nv;
}

static std::vector<Minimizer> findKMers(const std::vector<Nucleotide> &vector, const int k, const int offset)
{
  std::vector<Minimizer> kMers;

  for (std::size_t i = 0; i < vector.size() - k + 1; ++i)
  {
    kMers.push_back(Minimizer(slice(vector, i, i+k), i + offset));
  }

  //TODO: Sortiraj ovo
  std::sort(kMers.begin(), kMers.end());
  return kMers;
}

static std::vector<Minimizer> findInnerMinimizers(const std::vector<Nucleotide> &vector, const int w, const int k)
{
  std::vector<Minimizer> minimizers;

  for (std::size_t i = 0; i < vector.size() - w - k + 2; ++i)
  {
    const std::vector<Nucleotide> window = slice(vector, i, i + w + k - 1);
    const std::vector<Minimizer> kMers = findKMers(window, k, i);
    const Minimizer minimizer = kMers[0];
    //TODO: Samo ako vec ne postoji
    minimizers.push_back(minimizer);
  }

  return minimizers;
}

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
