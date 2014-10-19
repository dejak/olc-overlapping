#ifndef READER_HPP_
#define READER_HPP_

#include <string>
#include <vector>

namespace FASTQ {

class Sequence;
class Reader
{
  private:
    std::string _filename;
    std::vector<Sequence> _sequences;

  public:
    Reader(const std::string& filename);
    ~Reader();

    std::vector<Sequence>& _readSequences();
};

}

#endif  // READER_HPP_
