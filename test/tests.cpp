#define CATCH_CONFIG_MAIN // This tells the Catch2 header to generate a main

#include "catch.hpp"

#include "huffle.hpp"

////////////////////////////////////////////////////////////////
SCENARIO("Huffman Coder", "[hfl][encode]")
{
  GIVEN("The following input string...")
  {
    std::string const text = "This ought to be a long enough string to use as an example of the Huffman coder. What do you think??";

    WHEN("...the string is passed through the Huffman coder...")
    {
      auto coder = hfl::tree_t{text};

      THEN("...the encoded string looks like this...")
      {
        std::string const encoded = coder.encode();
        std::string const expected = "111001001111001111101001111010111010011110110010111111000100111010000110001101101111100011010001010100011110101110100111001110110111100111001110001101000101111110001011110110100001101110100011010000010101100101011011000111100001101101010001111100100010110111101000111001101011001010010110001011010000001001011111100001010110011111000100110010001110110101100110000111100110111111110101001011011110011100011011100100001000";

        REQUIRE(encoded == expected);
      }
    }
  }
}
