/*
 * anakin :)
 * B-Tree in C++
*/

#include <climits>
#include <iostream>
#include <array>
#include <memory>
#include <algorithm>

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
		std::sort(keys.begin(), keys.end());
	}

};


bool bsearch(const std::array<int, MAX_KEYS>& nums, int key);
Node* find(Node* root, int key);



int main(int argc, char* argv[])
{
	
	Node a(1);
	find(&a, 1);

	return 0;
}

bool bsearch(const std::array<int, MAX_KEYS>& nums, int key)
{
	uint32_t l = 0;
	uint32_t r = nums.size();

	while( l <= r )
	{
		uint32_t mid = (l+r)/2;
		if(nums[mid] == key)
		{
			return true;	
		}
		else if(nums[mid] < key)
		{
			l = mid + 1;	
		}
		else
		{
			r = mid - 1;
		}
	}

	return false;
}

Node* find(Node* root, int key)
{
	// to add more
	bool foundKey = bsearch(root->keys, key);
	if(foundKey)
	{
	       	std::cout << "Found " << key << '\n';
	}
	else
	{
		std::cout<< key << " Does Not Exist\n";
	}
	return root;
}
