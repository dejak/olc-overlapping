#ifndef SEQUENCE_HPP_
#define SEQUENCE_HPP_

#include <string>
#include <vector>

#include "nucleotidesequence.hpp"

namespace OLC
{

class FASTQSequence
{
  private:
    std::string identifier_;
    std::string description_;
    NucleotideSequence nucleotides_;
    std::string quality_;

  public:
    FASTQSequence(const std::string& identifier, const std::string& description, const NucleotideSequence& nucleotides, const std::string& quality);
    ~FASTQSequence();

    const std::string& getIdentifier()        const { return identifier_; }
    const std::string& getDescription()       const { return description_; }
    OLC::NucleotideSequence getNucleotides()  const { return nucleotides_; }
    const std::string& getQuality()           const { return quality_; }
};

}

#endif  // SEQUENCE_HPP_
