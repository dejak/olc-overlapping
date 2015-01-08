#include "minimizer.hpp"
#include <iostream>

namespace OLC
{
	std::vector<Nucleotide> slice(const std::vector<Nucleotide> &vector, int start = 0, int end = -1) {
		int oldlen = vector.size();
		int newlen;

		if (end == -1 || end >= oldlen) {
			newlen = oldlen - start;
		} else {
			newlen = end - start;
		}

		std::vector<Nucleotide> nv;
		for (int i = 0; i < newlen; i++) {
			nv.push_back(vector[start + i]);
		}

		return nv;
	}

	std::vector<std::vector<Nucleotide>> findKMers(const std::vector<Nucleotide> &vector, int k) {
		std::vector<std::vector<Nucleotide>> kMers;

		for (int i = 0; i < vector.size() - k + 1; i++) {
			kMers.push_back(slice(vector, i, i + k));
		}

		//TODO: Sortiraj ovo
		return kMers;
	}


	std::vector<std::vector<Nucleotide>> findInnerMinimizers(const std::vector<Nucleotide> &vector, int w, int k) {
		std::vector<std::vector<Nucleotide>> minimizers;

		for (int i = 0; i < vector.size() - w - k + 2; i++) {
			std::vector<Nucleotide> window = slice(vector, i, i + w + k - 1);
			std::vector<std::vector<Nucleotide>> kMers = findKMers(window, k);
			std::vector<Nucleotide> minimizer = kMers[0];
			//TODO: Samo ako vec ne postoji
			minimizers.push_back(minimizer);
		}

		return minimizers;
	}

	std::vector<std::vector<Nucleotide>> findOuterMinimizers(const std::vector<Nucleotide> &vector, int k) {
		std::vector<std::vector<Nucleotide>> minimizers;

		minimizers.push_back(slice(vector, 0, k));
		minimizers.push_back(slice(vector, vector.size() - k, vector.size()));
	
		return minimizers;
	}


	std::vector<std::vector<Nucleotide>> minimize(std::vector<Nucleotide> nucleotideVector, int w, int k) { 
		std::vector<std::vector<Nucleotide>> innerMinimizers = findInnerMinimizers(nucleotideVector, w, k);
		std::vector<std::vector<Nucleotide>> outerMinimizers = findOuterMinimizers(nucleotideVector, k);

		std::cout << "INNER MINIMIZERS:" << std::endl;
		for (int i = 0; i < innerMinimizers.size(); i++) {
			std::vector<Nucleotide> minimizer = innerMinimizers[i];
			for (int j = 0; j < minimizer.size(); j++) {
				std::cout << minimizer[j].getNucleotide() << " ";
			}
			std::cout << std::endl;
		}

		std::cout << "OUTER MINIMIZERS:" << std::endl;
		for (int i = 0; i < outerMinimizers.size(); i++) {
			std::vector<Nucleotide> minimizer = outerMinimizers[i];
			for (int j = 0; j < minimizer.size(); j++) {
				std::cout << minimizer[j].getNucleotide() << " ";
			}
			std::cout << std::endl;
		}

		return innerMinimizers;
	}


}