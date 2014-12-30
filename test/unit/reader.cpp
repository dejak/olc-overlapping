#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "reader.hpp"
#include "sequence.hpp"

TEST_CASE("reader can read nonexisting files", "[reader]")
{
  OLC::FASTQReader reader("../data/nonexisting.fastq");
  const auto sequences = reader.readSequences();

  SECTION("read nonexisting file")
  {
    REQUIRE(sequences.empty() == true);
  }
}

TEST_CASE("reader can read empty fastq files", "[reader]")
{
  OLC::FASTQReader reader("../data/empty.fastq");
  const auto sequences = reader.readSequences();

  SECTION("read empty file")
  {
    REQUIRE(sequences.empty() == true);
  }
}

TEST_CASE("reader can read an invalid file", "[reader]")
{
  OLC::FASTQReader reader("../data/invalid.fastq");
  const auto sequences = reader.readSequences();

  SECTION("read invalid data")
  {
    REQUIRE(sequences.size() == 1);
  }

  SECTION("the valid part is correct")
  {
    const auto sequence = sequences.at(0);

    REQUIRE(sequence.getDescription() == "description");
    REQUIRE(sequence.getIdentifier() == "identifier");
    REQUIRE(sequence.getNucleotides().toString() == "AAAATTTTCGGGG");
    REQUIRE(sequence.getQuality() == "!!!!!!!!!!!!!");
  }
}

TEST_CASE("reader can read a valid file", "[reader]")
{
  OLC::FASTQReader reader("../data/valid.fastq");
  const auto sequences = reader.readSequences();

  SECTION("read valid data")
  {
    REQUIRE(sequences.size() == 4);
  }

  SECTION("first sequence is correct")
  {
    const auto sequence = sequences.at(0);

    REQUIRE(sequence.getIdentifier() == "identifier");
    REQUIRE(sequence.getDescription() == "description");
    REQUIRE(sequence.getNucleotides().toString() == "AAAATTTTCGGGG");
    REQUIRE(sequence.getQuality() == "!!!!!!!!!!!!!");
  }

  SECTION("second sequence is correct")
  {
    const auto sequence = sequences.at(1);

    REQUIRE(sequence.getIdentifier() == "identifier2");
    REQUIRE(sequence.getDescription() == "");
    REQUIRE(sequence.getNucleotides().toString() == "AAAATTTTCGGGT");
    REQUIRE(sequence.getQuality() == "!!!!!!!!!!!!!");
  }

  SECTION("third sequence is correct")
  {
    const auto sequence = sequences.at(2);

    REQUIRE(sequence.getIdentifier() == "identifier3");
    REQUIRE(sequence.getDescription() == "description3");
    REQUIRE(sequence.getNucleotides().toString() == "AAAATTTTCGGGC");
    REQUIRE(sequence.getQuality() == "!!!!!!!!!!!!!");
  }

  SECTION("fourth sequence is random")
  {
    const auto sequence = sequences.at(3);
    const auto nucleotideSequence = sequence.getNucleotides().getSequence();

    REQUIRE(sequence.getIdentifier() == "random_sequence");
    REQUIRE(sequence.getDescription() == "");

    for (const auto nucleotide : nucleotideSequence)
    {
      // our reader should replace unknown reads aka dashes with
      // random nucleotides

      REQUIRE(nucleotide.getNucleotide() != '-');
    }

    REQUIRE(sequence.getQuality() == "!!!!!!!!!!!!!");
  }
}
