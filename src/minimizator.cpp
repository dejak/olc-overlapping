#include "minimizator.hpp"

#include <iostream> 
#include <algorithm>

namespace OLC
{

std::vector<Nucleotide> slice(const std::vector<Nucleotide>& vector, int start = 0, int end = -1)
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

std::vector<Minimizer> findKMers(const std::vector<Nucleotide> &vector, const int k)
{
  std::vector<Minimizer> kMers;

  for (std::size_t i = 0; i < vector.size() - k + 1; ++i)
  {
    kMers.push_back(Minimizer(slice(vector, i, i+k)));
  }

  //TODO: Sortiraj ovo
  std::sort(kMers.begin(), kMers.end());
  return kMers;
}

std::vector<Minimizer> findInnerMinimizers(const std::vector<Nucleotide> &vector, const int w, const int k)
{
  std::vector<Minimizer> minimizers;

  for (std::size_t i = 0; i < vector.size() - w - k + 2; ++i)
  {
    const std::vector<Nucleotide> window = slice(vector, i, i + w + k - 1);
    const std::vector<Minimizer> kMers = findKMers(window, k);
    const Minimizer minimizer = kMers[0];
    //TODO: Samo ako vec ne postoji
    minimizers.push_back(minimizer);
  }

  return minimizers;
}

std::vector<Minimizer> findOuterMinimizers(const std::vector<Nucleotide> &vector, const int k)
{
  std::vector<Minimizer> minimizers;

  minimizers.push_back(Minimizer(slice(vector, 0, k)));
  minimizers.push_back(Minimizer(slice(vector, vector.size() - k, vector.size())));

  return minimizers;
}


std::vector<Minimizer> minimize(const std::vector<Nucleotide>& nucleotideVector, const int w, const int k)
{
  std::vector<Minimizer> minimizers;

  const std::vector<Minimizer> innerMinimizers = findInnerMinimizers(nucleotideVector, w, k);
  const std::vector<Minimizer> outerMinimizers = findOuterMinimizers(nucleotideVector, k);

  minimizers.insert(minimizers.end(), outerMinimizers.begin(), outerMinimizers.end());
  minimizers.insert(minimizers.end(), outerMinimizers.begin(), outerMinimizers.end());

  return minimizers;
}

}
