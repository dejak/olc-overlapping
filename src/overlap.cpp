#include "overlap.hpp"

namespace OLC
{
Overlap::Overlap(const int startFirst, const int endFirst, const int startSecond, const int endSecond)
  : startFirst_(startFirst), endFirst_(endFirst), startSecond_(startSecond), endSecond_(endSecond)
  {}

int Overlap::getStartFirst() const {
	return startFirst_;
}

int Overlap::getEndFirst() const {
	return endFirst_;
}

int Overlap::getStartSecond() const {
	return startSecond_;
}

int Overlap::getEndSecond() const {
	return endSecond_;
}

}