#include "minimizer.hpp"

namespace OLC
{
	Minimizer::Minimizer(const std::vector<Nucleotide> vector)
		:vector_(vector)
	{

	}

	
	bool operator<(const Minimizer &first, const Minimizer &second) {
		for (int i = 0; i < first.size(); i++) {
			if (first[i].getValue() < second[i].getValue()) {
				return true;
			}
			if (first[i].getValue() > second[i].getValue()) {
				return false;
			}
		}


		return false;
	}

	Nucleotide Minimizer::operator[](unsigned int index) const{
		return vector_[index];
	}

	int Minimizer::size() const {
		return vector_.size();
	}
}