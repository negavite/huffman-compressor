// Michael Chen <mhc002>

#include "HCTree.hpp"

// Post-order tree traversal to delete all nodes
void HCTree::makeEmpty(HCNode* n) {
	if(n != nullptr) {
		makeEmpty(n->c0);
		makeEmpty(n->c1);
		delete n;
	}

	n = nullptr;
}

// Deconstructor
HCTree::~HCTree() {
	makeEmpty(root);
}

// Use the Huffman algorithm to build a Huffman coding trie
void HCTree::build(const vector<int>& freqs) {
	priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;

	for(int i = 0; i < freqs.size(); ++i) {
		if(freqs[i] > 0) {
			leaves[i] = new HCNode(freqs[i], i);
			pq.push(leaves[i]);
		}
	}

	while(pq.size() > 1){
		HCNode* c0 = pq.top();
		pq.pop();

		HCNode* c1 = pq.top();
		pq.pop();

		int count = c0->count + c1->count;

		HCNode* p = new HCNode(count, c0->symbol, c0, c1);

		c0->p = p;
		c1->p = p;

		pq.push(p);
	}

	root = pq.top();
	pq.pop();
}

// Write to the given BitOutputStream the sequence of bits coding the given symbol.
void HCTree::encode(byte symbol, BitOutputStream& out) const {
	HCNode* current = leaves[symbol];
	stack<int> s;

	while(current->p != nullptr) {
		HCNode* p = current->p;

		if(p->c0 == current) {
			s.push(0);
		} else if (p->c1 == current) {
			s.push(1);	
		}

		current = p;
	}

	while(!s.empty()) {
		out.writeBit(s.top());
		s.pop();
	}
}

// Return symbol coded in the next sequence of bits from the stream.
int HCTree::decode(BitInputStream& in) const {
	HCNode* current = root;

	while(current->c0 != nullptr) {
		int bit = in.readBit();

		if(bit == 0) {
			current = current->c0;
		} else if (bit == 1) {
			current = current->c1;
		}
	}

	return current->symbol;
}

