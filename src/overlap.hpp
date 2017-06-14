#ifndef OVERLAP_HPP_
#define OVERLAP_HPP_

namespace OLC
{

class Overlap final
{
  private:
    int32_t startFirst_;
    int32_t endFirst_;
    int32_t startSecond_;
    int32_t endSecond_;

   public:
    Overlap() = default;

    Overlap(const int32_t startFirst, const int32_t endFirst, const int32_t startSecond, const int32_t endSecond) noexcept :
        startFirst_(startFirst),
        endFirst_(endFirst),
        startSecond_(startSecond),
        endSecond_(endSecond)
    {

    }

    inline int32_t getStartFirst() const noexcept
    {
      return startFirst_;
    }

    inline int32_t getEndFirst() const noexcept
    {
      return endFirst_;
    }

    inline int32_t getStartSecond() const noexcept
    {
      return startSecond_;
    }

    inline int32_t getEndSecond() const noexcept
    {
      return endSecond_;
    }

};

}


#endif // OVERLAP_HPP_
