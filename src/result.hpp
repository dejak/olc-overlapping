#ifndef RESULT_HPP_
#define RESULT_HPP_

#include <tuple>
#include <string>

#include "overlap.hpp"

namespace OLC
{

class Result final
{
  private:
    uint32_t identifier1_;
    uint32_t identifier2_;
    uint32_t length_;
    int32_t ahang_;
    int32_t bhang_;

  public:
    Result(const uint32_t identifier1, const uint32_t identifier2, const uint32_t length, const int32_t ahang, const int32_t bhang) :
      identifier1_(identifier1),
      identifier2_(identifier2),
      length_(length),
      ahang_(ahang),
      bhang_(bhang)
    {
    }

    inline std::tuple<uint32_t, uint32_t> getIdentifiers() const
    {
      return std::make_tuple(identifier1_, identifier2_);
    }

    inline int32_t getAhng() const
    {
      return ahang_;
    }

    inline int32_t getBhng() const
    {
      return bhang_;
    }

    inline uint32_t getLength() const
    {
      return length_;
    }
};

}

#endif // RESULT_HPP_
