#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "input_file_reader.hpp"
#include "minimizator.hpp"

TEST_CASE("reader can read nonexisting files", "[input]")
{
  OLC::InputFileReader reader("../data/nonexisting.fastq");
  const auto sequences = reader.readSequences();

  SECTION("read nonexisting file")
  {
    REQUIRE(sequences.empty() == true);
  }
}

TEST_CASE("reader can read empty files", "[input]")
{
  OLC::InputFileReader reader("../data/empty.fastq");
  const auto sequences = reader.readSequences();

  SECTION("read empty file")
  {
    REQUIRE(sequences.empty() == true);
  }
}

TEST_CASE("reader can read a valid fastq file", "[fastq]")
{
  OLC::InputFileReader reader("../data/valid.fastq");
  const auto sequences = reader.readSequences();

  SECTION("read valid data")
  {
    REQUIRE(sequences.size() == 4);
  }

  SECTION("first sequence is correct")
  {
    const auto sequence = sequences.at(0);

    REQUIRE(sequence->getIdentifier() == "identifier");
    REQUIRE(sequence->getDescription() == "description");
    REQUIRE(sequence->getNucleotides()->toString() == "AAAATTTTCGGGG");
  }

  SECTION("second sequence is correct")
  {
    const auto sequence = sequences.at(1);

    REQUIRE(sequence->getIdentifier() == "identifier2");
    REQUIRE(sequence->getDescription() == "");
    REQUIRE(sequence->getNucleotides()->toString() == "AAAATTTTCGGGT");
  }

  SECTION("third sequence is correct")
  {
    const auto sequence = sequences.at(2);

    REQUIRE(sequence->getIdentifier() == "identifier3");
    REQUIRE(sequence->getDescription() == "description3");
    REQUIRE(sequence->getNucleotides()->toString() == "AAAATTTTCGGGC");
  }

  SECTION("fourth sequence is random")
  {
    const auto sequence = sequences.at(3);
    const auto nucleotideSequence = sequence->getNucleotides()->getSequence();

    REQUIRE(sequence->getIdentifier() == "random_sequence");
    REQUIRE(sequence->getDescription() == "");

    for (const auto nucleotide : nucleotideSequence)
    {
      // our reader should replace unknown reads aka dashes with
      // random nucleotides

      REQUIRE(nucleotide.getNucleotide() != '-');
    }
  }
}

TEST_CASE("reader can read a valid fasta file", "[fasta]")
{
  OLC::InputFileReader reader("../data/valid.fasta");
  const auto sequences = reader.readSequences();

  SECTION("read valid data")
  {
    REQUIRE(sequences.size() == 3);
  }

  SECTION("first sequence is correct")
  {
    const auto sequence = sequences.at(0);

    REQUIRE(sequence->getNucleotides()->toString() == "AAAATTTTCGGGT");
  }

  SECTION("second sequence is correct")
  {
    const auto sequence = sequences.at(1);

    REQUIRE(sequence->getNucleotides()->toString() == "AAAATTTTCGGGC");
  }

  SECTION("third sequence is random")
  {
    const auto sequence = sequences.at(2);
    const auto nucleotideSequence = sequence->getNucleotides()->getSequence();

    REQUIRE(sequence->getDescription() == "");

    for (const auto nucleotide : nucleotideSequence)
    {
      // our reader should replace unknown reads aka dashes with
      // random nucleotides

      REQUIRE(nucleotide.getNucleotide() != '-');
    }
  }
}

TEST_CASE("reader can read a different valid fasta file", "[fasta]")
{
  OLC::InputFileReader reader("../data/valid2.fasta");
  const auto sequences = reader.readSequences();

  SECTION("read valid data")
  {
    REQUIRE(sequences.size() == 3);
  }

  SECTION("first sequence is correct")
  {
    const auto sequence = sequences.at(0);

    REQUIRE(sequence->getNucleotides()->toString() == "AAAATTTTCGGGT");
  }

  SECTION("second sequence is correct")
  {
    const auto sequence = sequences.at(1);

    REQUIRE(sequence->getNucleotides()->toString() == "AAAATTTTCGGGC");
  }

  SECTION("third sequence is random")
  {
    const auto sequence = sequences.at(2);
    const auto nucleotideSequence = sequence->getNucleotides()->getSequence();

    REQUIRE(sequence->getDescription() == "");

    for (const auto nucleotide : nucleotideSequence)
    {
      // our reader should replace unknown reads aka dashes with
      // random nucleotides

      REQUIRE(nucleotide.getNucleotide() != '-');
    }
  }
}

TEST_CASE("reader can read a multiline fasta sequence", "[fasta]")
{
  OLC::InputFileReader reader("../data/big.fasta");
  const auto sequences = reader.readSequences();

  SECTION("read valid data")
  {
    REQUIRE(sequences.size() == 3);
  }

  SECTION("test multiline sequence 1")
  {
    const auto sequence = sequences.at(0);

    REQUIRE(sequence->getNucleotides()->toString() == "AAAATTTTCGGGTAAAATTTTCGGGTAAAATTTTCGGGT");
  }

  SECTION("test single line sequence 2")
  {
    const auto sequence = sequences.at(1);

    REQUIRE(sequence->getNucleotides()->toString() == "ATCG");
  }

  SECTION("test multiline sequence 3")
  {
    const auto sequence = sequences.at(2);

    REQUIRE(sequence->getNucleotides()->toString() == "AAAATTTTCGGGGAAAATTTTCGGGGAAAATTTTCGGGG");
  }
}
