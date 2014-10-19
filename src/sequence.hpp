#ifndef SEQUENCE_HPP_
#define SEQUENCE_HPP_

#include <string>
#include <vector>

namespace FASTQ {

class Sequence
{
  private:
    std::string _identifier;
    std::string _description;
    std::string _sequence;
    std::string _quality;

  public:
    Sequence(const std::string& identifier, const std::string& description, const std::string& sequence, const std::string& quality);
    ~Sequence();

    std::string _getIdentifier()   const { return _identifier; }
    std::string _getDescription()  const { return _description; }
    std::string _getSequence()     const { return _sequence; }
    std::string _getQuality()      const { return _quality; }
};

}

#endif  // SEQUENCE_HPP_
