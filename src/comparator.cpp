#include "comparator.hpp"

namespace OLC
{
Position::Position(const int i, const int j) 
	:i_(i), j_(j)
{}

int Position::get(int index) const {
	if (index == 0) {
		return i_;
	} else {
		return j_;
	}
}

void compare(std::vector<int> first, std::vector<int> second) {
	std::vector<std::vector<int>> values;
	std::vector<std::vector<Position>> positions;

	for (int i = 0; i < first.size() + 1; i++) {
		std::vector<int> row;
		for (int j = 0; j < second.size() + 1; j++) {
			row.push_back(0);
		}
		values.push_back(row);
	}

	int maxValue = 0;
	Position maxPosition(0, 0);

	for (int i = 1; i < first.size() + 1; i++) {
		for (int j = 1; j < first.size() + 1; j++) {
			int up = values[i-1][j] - 4;
			int left = values[i][j-1] - 4;
			int diagonal = values[i-1][j-1] - 1;
			
			if (first[i-1] == second[j-1]) {
				diagonal += 3;
			}

			if (up > left && up > diagonal) {
				values[i][j] = up;
				Position prev(i-1, j);
				positions[i][j] = prev;
				if (up > maxValue) {
					maxValue = up;
					maxPosition = prev;
				}
			} else if (left > up && left > diagonal) {
				values[i][j] = left;
				Position prev(i, j-1);
				positions[i][j] = prev;
				if (left > maxValue) {
					maxValue = left;
					maxPosition = prev;
				}
			} else {
				values[i][j] = diagonal;
				Position prev(i-1, j-1);
				positions[i][j] = prev;
				if (diagonal > maxValue) {
					maxValue = diagonal;
					maxPosition = prev;
				}
			}
		}
	}

}

}