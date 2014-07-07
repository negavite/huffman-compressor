// Michael Chen <mhc002>

#include "HCNode.hpp"

// Less-than comparison, so HCNodes will work in std::priority_queue
bool HCNode::operator<(const HCNode& other) {
	if(count != other.count) {
		return count > other.count;
	}

	return symbol < other.symbol;
}
