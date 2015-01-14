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
    uint32_t identifier1_;
    uint32_t identifier2_;
    uint32_t length_;
    int32_t ahang_;
    int32_t bhang_;

  public:
    Result(const uint32_t identifier1, const uint32_t identifier2, const uint32_t length, const int32_t ahang, const int32_t bhang);
    std::tuple<uint32_t, uint32_t> getIdentifiers();
    int32_t getAhng() const { return ahang_; }
    int32_t getBhng() const { return bhang_; }
    uint32_t getLength() const { return length_; }
};

}

#endif // RESULT_HPP_
