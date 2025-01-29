/*
 * anakin :)
 * B-Tree in C++
*/


#include <iostream>
#include <array>
#include <memory>


// represents t ... t-1 the minimum number of nodes
// The root node is exemnt from this rule
constexpr uint32_t DEGREE = 3;
constexpr uint32_t MAX_KEYS = 2*DEGREE - 1;

/*
 
 *- For a node in a B-tree of degree `t`, the maximum number of keys it can contain is:
 *- 2t - 1 

 *- each node can have # of keys + 1
 *- (2t-1) + 1

 */


struct Node
{
	uint32_t n; // # of keys
	std::array<int, MAX_KEYS> keys;
	std::array<Node*, MAX_KEYS + 1> children; 

	// will be explained later in an example	
	bool IsLeaf;
	
	Node(int key)
	: n(1), keys(), children(), IsLeaf(true)
	{
		keys[0] = key;
	}

};


int main(int argc, char* argv[])
{
	
	Node a(1);
	for(uint32_t i = 0 ; i < a.n ; i++)
	       std::cout << a.keys[i] << " ";	

	return 0;
}
