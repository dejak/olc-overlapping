#ifndef SEQUENCE_HPP_
#define SEQUENCE_HPP_

#include <string>
#include <vector>
#include <memory>

#include "nucleotides.hpp"

namespace OLC
{

class Sequence
{
  private:
    std::string identifier_;
    std::string description_;
    std::unique_ptr<OLC::Nucleotides> nucleotides_;

  public:
    Sequence(const std::string& identifier, const std::string& description, std::unique_ptr<Nucleotides> nucleotides);
    ~Sequence();

    const std::string getIdentifier()        const { return identifier_; }
    const std::string getDescription()       const { return description_; }
    const OLC::Nucleotides *getNucleotides()  const { return nucleotides_.get(); }
};

}

#endif // SEQUENCE_HPP_
