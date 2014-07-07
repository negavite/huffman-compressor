// Michael Chen <mhc002>

#include "BitInputStream.hpp"

bitset<8> toBitset(unsigned char byte) {
    return bitset<8>(byte);
}

// Read the next bit from the bit buffer. If the bit buffer is currently empty,
// fill the bit buffer by reading a char from the istream first. Return the bit
// read as the least signficant bit of an int. Return -1 on EOF.
int BitInputStream::readBit() {
	if(!in.eof() && in.good()) {
		if(bufi == 8) {
			char ch = in.get();
			buf = toBitset(ch);
			bufi = 0;
		}

		return buf[bufi++];
	} else {
		return -1;
	}
}

// Read a byte from the ostream. Return -1 on EOF.
int BitInputStream::readByte() {
	if(!in.eof() && in.good()) {
		char ch = in.get();
		return ch;
	} else {
		return -1;
	}
}

// Read a non-negative int from the ostream.  Return -1 on EOF.
int BitInputStream::readInt() {
	if(!in.eof() && in.good()) {
		int count;
		in >> count;
		return count;
	} else {
		return -1;
	}
}


