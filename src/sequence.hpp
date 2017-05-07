#ifndef SEQUENCE_HPP_
#define SEQUENCE_HPP_

#include <string>
#include <vector>

#include "nucleotides.hpp"

namespace OLC
{

class Sequence
{
  private:
    std::string identifier_;
    std::string description_;
    OLC::Nucleotides *nucleotides_;

  public:
    template<typename I, typename D>
    Sequence(I&& identifier, D&& description, OLC::Nucleotides* nucleotides) :
      identifier_(std::forward<I>(identifier)),
      description_(std::forward<D>(description)),
      nucleotides_(nucleotides)
    {

    }

    ~Sequence()
    {
      if (nucleotides_ != nullptr)
        delete nucleotides_;
    }

    const std::string& getIdentifier()        const { return identifier_; }
    const std::string& getDescription()       const { return description_; }
    const OLC::Nucleotides *getNucleotides()  const { return nucleotides_; }
};

}

#endif // SEQUENCE_HPP_
