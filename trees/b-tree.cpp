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
constexpr uint32_t DEGREE = 2;
constexpr uint32_t MIN_KEYS = DEGREE - 1;
constexpr uint32_t MAX_KEYS = 2*DEGREE - 1;
/*
 
 *- For a node in a B-tree of degree `t`, the maximum number of keys it can contain is:
 *- 2t - 1 

 *- each node can have # of keys + 1
 *- (2t-1) + 1

 */


template<typename T>
using Scope = std::unique_ptr<T>;

template<typename T, typename ... Args>
constexpr Scope<T> MakeScope(Args&& ... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}


struct Node
{
	uint32_t n; // # of keys
	std::array<int, MAX_KEYS> keys;
	std::array<Scope<Node>, MAX_KEYS + 1> children; 

	// will be explained later in an example	
	bool IsLeaf;
	
	Node(int key)
	: n(1), keys(), children(), IsLeaf(true)
	{
		keys[0] = key;
		// so we only sort the first n elements
		std::sort(keys.begin(), keys.begin() + n);
	}


	Node()
	: n(0), keys(), children(), IsLeaf(true)
	{	
	}

	void AddKey(int key)
	{
		if(n < MAX_KEYS)
		{
			keys[n] = key;
			n+=1;
			std::sort(keys.begin(), keys.begin()+n);
		}
		else
		{
			std::cout << "Failed to add key ... Max Keys Reached";
		}

	}

	void Print(uint32_t tabDepth)
	{
		for(uint32_t i = 0 ; i < n ; i++)
		{
			for(uint32_t j = 0 ; j < tabDepth; j++)
			{
				std::cout << '\t';
			}

			std::cout << keys[i] << '\n';
		}

		std::cout << '\n';
	}

};

// returns index of the search if successful, also where the child node is
int binsearch(const std::array<int, MAX_KEYS>& nums, uint32_t len, int key);

int split(Scope<Node>& node, int key, Scope<Node>& newRight);
void insert(Scope<Node>& root, int key);
Node* find(Scope<Node>& root, int key);
void print(Scope<Node>& root, uint32_t tabDepth);


int main(int argc, char* argv[])
{
	
	Scope<Node> head = MakeScope<Node>();

	insert(head, 1);
	insert(head, 2);
	insert(head, 3);
	insert(head, 4);
	insert(head, 5);
	
	find(head,5);
	
	print(head, 0);
	return 0;
}



void print(Scope<Node>& root, uint32_t tabDepth)
{
	if(root == nullptr)
	{
		return;
	}
	root->Print(tabDepth);

	for(int i = static_cast<int>(root->n); i >= 0; i--)
	{

		print(root->children[i], tabDepth + 1);
		std::cout << '\n';
	}

}



int binsearch(const std::array<int, MAX_KEYS>& nums, uint32_t len, int key)
{
	uint32_t l = 0;
	uint32_t r = len;
	uint32_t mid = 0;

	while( l <= r )
	{
		mid = (l+r)/2;
		if(nums[mid] == key)
		{
			break;	
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

	// will return where the key should be if it doesnt exist
	// and it will return where the key is if it does
	return mid;
}


// Returns index where key should be inserted into parent
int split(Scope<Node>& node, int key, Scope<Node>& newRight) {
    
    newRight->IsLeaf = node->IsLeaf;
    
    int insertPos = binsearch(node->keys, node->n, key);
    
    // Move higher half of keys to new node
    for (int i = MIN_KEYS + 1; i < MAX_KEYS; i++) 
    {
         newRight->AddKey(node->keys[i]);
    }
    
    // If it's not a leaf, move the children too
    if (!node->IsLeaf) 
    {
        for (int i = MIN_KEYS + 1; i = MAX_KEYS + 1; i++) 
	{
            newRight->children[i - (MIN_KEYS + 1)] = std::move(node->children[i]);
        }
    }
    
    node->n = MIN_KEYS;
    
    // Insert the new key into the appropriate node
    if (insertPos <= MIN_KEYS) 
    {
        node->AddKey(key);
    }
    else 
    {
        newRight->AddKey(key);
    }
    
    return MIN_KEYS;  // Return the middle key position
}

void insert(Scope<Node>& root, int key) {
    if (root->IsLeaf) 
    {
        if (root->n < MAX_KEYS) 
	{
            root->AddKey(key);
        } 
	else
       	{
            // Need to split
            Scope<Node> newRight = MakeScope<Node>();
            int midKey = split(root, key, newRight);
            
            // Create new root
            Scope<Node> newLocalRoot = MakeScope<Node>();
            newLocalRoot->IsLeaf = false;
	    newLocalRoot->AddKey(root->keys[midKey]);
            newLocalRoot->children[0] = std::move(root);
            newLocalRoot->children[1] = std::move(newRight);
            
            root = std::move(newLocalRoot);
        }
    } 
    else 
    {
        int index = binsearch(root->keys, root->n, key);
        insert(root->children[index], key);
        
        // Check if child was split and we need to handle the promoted key
        // This would be handled similarly to the leaf split case
    }
}


Node* find(Scope<Node>& root, int key)
{

	if(root == nullptr)
	{
		std::cout << "Failed to find: " << key << '\n';
		return nullptr;
	}

	int foundIndex = binsearch(root->keys, root->n, key);
	if(root->keys[foundIndex]==key)
	{
	       	std::cout << "Found " << key << '\n';
		return root.get();
	}

	// foundIndex will always be in bounds since 
	// keys is of length root->children.size()-1
	return find(root->children[foundIndex], key);

}
