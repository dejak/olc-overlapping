#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "reader.hpp"
#include "sequence.hpp"

TEST_CASE("reader can read empty fastq files", "[reader]")
{
  FASTQ::Reader reader("../data/empty.fastq");
  const auto sequences = reader._readSequences();

  SECTION("read empty file")
  {
    REQUIRE(sequences.empty() == true);
  }
}

TEST_CASE("reader can read an invalid file", "[reader]")
{
  FASTQ::Reader reader("../data/invalid.fastq");
  const auto sequences = reader._readSequences();

  SECTION("read invalid data")
  {
    REQUIRE(sequences.size() == 1);
  }

  SECTION("the valid part is correct")
  {
    const FASTQ::Sequence sequence= sequences.at(0);

    REQUIRE(sequence._getDescription() == "description");
    REQUIRE(sequence._getIdentifier() == "identifier");
    REQUIRE(sequence._getSequence() == "AAAATTTTCGGGG");
    REQUIRE(sequence._getQuality() == "!!!!!!!!!!!!!");
  }
}

TEST_CASE("reader can read a valid file", "[reader]")
{
  FASTQ::Reader reader("../data/valid.fastq");
  const auto sequences = reader._readSequences();

  SECTION("read valid data")
  {
    REQUIRE(sequences.size() == 3);
  }

  SECTION("first sequence is correct")
  {
    const FASTQ::Sequence sequence= sequences.at(0);

    REQUIRE(sequence._getIdentifier() == "identifier");
    REQUIRE(sequence._getDescription() == "description");
    REQUIRE(sequence._getSequence() == "AAAATTTTCGGGG");
    REQUIRE(sequence._getQuality() == "!!!!!!!!!!!!!");
  }

  SECTION("second sequence is correct")
  {
    const FASTQ::Sequence sequence= sequences.at(1);

    REQUIRE(sequence._getIdentifier() == "identifier2");
    REQUIRE(sequence._getDescription() == "");
    REQUIRE(sequence._getSequence() == "AAAATTTTCGGGT");
    REQUIRE(sequence._getQuality() == "!!!!!!!!!!!!!");
  }

  SECTION("third sequence is correct")
  {
    const FASTQ::Sequence sequence= sequences.at(2);

    REQUIRE(sequence._getDescription() == "description3");
    REQUIRE(sequence._getIdentifier() == "identifier3");
    REQUIRE(sequence._getSequence() == "AAAATTTTCGGGC");
    REQUIRE(sequence._getQuality() == "!!!!!!!!!!!!!");
  }
}
