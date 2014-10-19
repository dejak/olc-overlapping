#include "sequence.hpp"

namespace FASTQ {

Sequence::Sequence(const std::string& identifier, const std::string& description, const std::string& sequence, const std::string& quality)
  : _identifier(identifier),
    _description(description),
    _sequence(sequence),
    _quality(quality)
{

}

Sequence::~Sequence()
{

}

}
