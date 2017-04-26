#ifndef OVERLAP_HPP_
#define OVERLAP_HPP_

namespace OLC
{

class Overlap
{
  private:
    int32_t startFirst_;
    int32_t endFirst_;
    int32_t startSecond_;
    int32_t endSecond_;

   public:
    Overlap(const int32_t startFirst, const int32_t endFirst, const int32_t startSecond, const int32_t endSecond) :
        startFirst_(startFirst),
        endFirst_(endFirst),
        startSecond_(startSecond),
        endSecond_(endSecond)
    {

    }

    inline int32_t getStartFirst() const
    {
      return startFirst_;
    }

    inline int32_t getEndFirst() const
    {
      return endFirst_;
    }

    inline int32_t getStartSecond() const
    {
      return startSecond_;
    }

    inline int32_t getEndSecond() const
    {
      return endSecond_;
    }

};

}


#endif // OVERLAP_HPP_
