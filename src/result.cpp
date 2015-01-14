#include "result.hpp"

namespace OLC
{

Result::Result(const uint32_t identifier1, const uint32_t identifier2, const uint32_t length, const int32_t ahang, const int32_t bhang)
  : identifier1_(identifier1),
    identifier2_(identifier2),
    length_(length),
    ahang_(ahang),
    bhang_(bhang)
{

}

std::tuple<uint32_t, uint32_t> Result::getIdentifiers()
{
  return std::make_tuple(identifier1_, identifier2_);
}

}
