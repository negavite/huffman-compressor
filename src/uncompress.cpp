// Michael Chen <mhc002>

#include "HCTree.hpp"

using namespace std;

int main(int argc, char** argv) {
	vector<int> freqs(256,0);

	// Open input file for reading
	ifstream in;
	in.open(argv[1], ios::binary);
	BitInputStream bitIn = BitInputStream(in);
	int charCount = 0;

	// Read file header and reconstruct Huffman coding tree
	for(int i = 0; i < freqs.size(); ++i){
		int freq = bitIn.readInt();
		freqs[i] = freq;
		charCount += freq;
	}

	// Read last space
	bitIn.readByte();

	// Rebuild tree
	HCTree huffman;
	huffman.build(freqs);

	// Open output file for writing
	ofstream out;
	out.open(argv[2], ios::binary); 
	BitOutputStream bitOut = BitOutputStream(out);

	int charCount2 = 0;

	while(charCount > 0) {
		int ascii = huffman.decode(bitIn);
		bitOut.writeByte(ascii);
		charCount--;
		charCount2++;
	}

	in.close();
	out.close();

	return 0;
}