#include "result.hpp"

namespace OLC
{
Result::Result(const std::string identifier1, const std::string identifier2, const int length, const int ahang, const int bhang)
  :identifier1_(identifier1), identifier2_(identifier2), length_(length), ahang_(ahang), bhang_(bhang)
{}

std::tuple<std::string, std::string> Result::getIdentifiers() {
	return std::make_tuple(identifier1_, identifier2_);
}

}