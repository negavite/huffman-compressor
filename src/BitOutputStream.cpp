// Michael Chen <mhc002>

#include "BitOutputStream.hpp"

// Write the least significant bit of the argument into the bit buffer, and 
// increment the bit buffer index. Flush to the ostream first if bit buffer 
// is full.
void BitOutputStream::writeBit(int bit) {
	if(bufi > 7) {
		flush();
	}

	buf.set(bufi, bit);
  	++bufi;
}

// Write the least significant byte of the argument to the ostream.
void BitOutputStream::writeByte(int b) {
	out << (char) b;
	out.flush();
}

// Write the argument to the ostream.
void BitOutputStream::writeInt(int i) {
	out << i;
	out.flush();
}

// If the bit buffer contains any bits, flush the bit buffer to the ostream, 
// clear the bit buffer, set the bit buffer index to 0 and flush the ostream.
void BitOutputStream::flush() {
	unsigned long i = buf.to_ulong();
  	unsigned char c = static_cast<char>(i);
  	out.put(c);
  	out.flush();

	buf.reset();
	bufi = 0;
}