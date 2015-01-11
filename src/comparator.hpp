#ifndef COMPARATOR_HPP_
#define COMPARATOR_HPP_

#include <vector>

namespace OLC
{


class Position {
	private:
		int i_, j_;
	public:
		Position(const int i, const int j);
		int get(int index) const;	
};

std::vector<Position> compare(std::vector<int> first, std::vector<int> second);

}


#endif // COMPARATOR_HPP_