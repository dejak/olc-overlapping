#include "result.hpp"

namespace OLC
{
Result::Result(const int identifier1, const int identifier2, const int length, const int ahang, const int bhang)
  :identifier1_(identifier1), identifier2_(identifier2), length_(length), ahang_(ahang), bhang_(bhang)
{}

std::tuple<int, int> Result::getIdentifiers() {
	return std::make_tuple(identifier1_, identifier2_);
}


int Result::getAhng() const {
	return ahang_;
}

int Result::getBhng() const {
	return bhang_;
}
 
int Result::getLength() const {
	return length_;
}

}