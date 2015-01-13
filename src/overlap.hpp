#ifndef OVERLAP_HPP_
#define OVERLAP_HPP_

namespace OLC
{
class Overlap
{
  private:
  	int startFirst_;
  	int endFirst_;
  	int startSecond_;
  	int endSecond_;
   public:
   	Overlap(const int startFirst, const int endFirst, const int startSecond, const int endSecond);
   	int getStartFirst() const;
   	int getEndFirst() const;
   	int getStartSecond() const;
   	int getEndSecond() const;
};
}

#endif