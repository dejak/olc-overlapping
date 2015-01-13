#ifndef RESULT_HPP_
#define RESULT_HPP_

#include <tuple>
#include <string>
#include "overlap.hpp"

namespace OLC
{
class Result
{
  private:
  	std::string identifier1_, identifier2_;
  	int length_;
  	int ahang_;
  	int bhang_;
  public:
  	Result(const std::string identifier1, const std::string identifier2, const int length, const int ahang, const int bhang);
  	std::tuple<std::string, std::string> getIdentifiers();
  	int getAhng() const { return ahang_; }
  	int getBhng() const { return bhang_; }
  	int getLength() const { return length_; }
};
}

#endif