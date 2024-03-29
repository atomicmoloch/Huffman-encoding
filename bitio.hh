/*
 * A pair of simple classes tu perform stream I/O on individual bits.
 */
#include <iostream>
#include <fstream>

// BitInput: Read a single bit at a time from an input stream.
// Before reading any bits, ensure your input stream still has valid inputs.
class BitInput {
 public:
  // Construct with an input stream
  BitInput(std::istream& is);

  ~BitInput() = default;

  BitInput(const BitInput&) = default;
  BitInput(BitInput&&) = default;
  BitInput& operator=(const BitInput&) = default;
  BitInput& operator=(BitInput&&) = default;

  // Read a single bit (or trailing zero)
  // Allowed to crash or throw an exception if called past end-of-file.
  bool input_bit();
private:
    int countl = 8;
    unsigned char currentl = 0;
    std::istream* stream;
};

// BitOutput: Write a single bit at a time to an output stream
// Make sure all bits are written out by the time the destructor is done.
class BitOutput {
 public:
  // Construct with an input stream
  BitOutput(std::ostream& os);

  // Flushes out any remaining output bits and trailing zeros, if any:
  ~BitOutput();

  BitOutput(const BitOutput&) = default;
  BitOutput(BitOutput&&) = default;
  BitOutput& operator=(const BitOutput&) = default;
  BitOutput& operator=(BitOutput&&) = default;

  // Output a single bit (buffered)
  void output_bit(bool bit);
private:
    int count = 0; //keeps track of place in buffer
    void write(); //write-to-stream function
    char buffer [8] = {0, 0, 0, 0, 0, 0, 0, 0}; //buffer array
    std::ostream* stream;
};

