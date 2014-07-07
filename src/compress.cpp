// Michael Chen <mhc002>

#include "HCTree.hpp"

using namespace std;

int main(int argc, char** argv) {
	// Open input file for reading
	ifstream in;
	in.open(argv[1], ios::binary);
	
	// Read bytes from file, counting number of occurrences of each byte value
	vector<int> freqs(256,0);

	while(in.good()) {
		int ascii = in.get();
		
		if(!in.good()) break;
		
		freqs[ascii]++;
	}

	// Check errors, then close file
	if(!in.eof()) {
		cerr << "There was an error reading the file" << endl;
		return 1;
	}

	in.close();

	// Use byte counts to construct a Huffman coding tree
	HCTree huffman;
	huffman.build(freqs);

	// Open the output file for writing
	ofstream out;
	out.open(argv[2], ios::binary); 

	// Write file header to enable reconstruction of coding tree
	BitOutputStream bitOut = BitOutputStream(out);
	
	for(int i = 0; i < freqs.size(); ++i) {
		bitOut.writeInt(freqs[i]);
		bitOut.writeByte(' ');
	}
	
	// Open input file for reading again
	in.open(argv[1], ios::binary);
	
	// Using tree, translate each byte from input file into its code and append
	// to a sequence of bits to the output file
	while(in.good()) {
		char symbol = in.get();
		
		if(!in.good()) break;
		
		huffman.encode(symbol, bitOut);
	}

	bitOut.flush();
	
	// Close input and output files
	in.close();
	out.close();

	return 0;
}
