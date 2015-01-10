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
    Sequence(const std::string& identifier, const std::string& description, OLC::Nucleotides* nucleotides);
    ~Sequence();

    const std::string getIdentifier()        const { return identifier_; }
    const std::string getDescription()       const { return description_; }
    const OLC::Nucleotides *getNucleotides()  const { return nucleotides_; }
};

}

#endif // SEQUENCE_HPP_
