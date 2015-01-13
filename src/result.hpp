#ifndef RESULT_HPP_
#define RESULT_HPP_

#include <tuple>
#include "overlap.hpp"

namespace OLC
{
class Result
{
  private:
  	int identifier1_, identifier2_;
  	int length_;
  	int ahang_;
  	int bhang_;
  public:
  	Result(const int identifier1, const int identifier2, const int length, const int ahang, const int bhang);
  	std::tuple<int, int> getIdentifiers();
  	int getAhng() const;
  	int getBhng() const;
  	int getLength() const;
};
}

#endif