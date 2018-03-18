#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define SENTINEL -10101
#define UNMARKED 0
#define MARKED 1
#define DUMMY 9999

//declaration of struct node
struct node 
{
	int key;
	int isDeleted;
	struct node *left;
	struct node *right;
	struct node *parent;
};
typedef struct node Tree;

Tree* newNode(int key) //a function that constructs a new node, assigns the key, initializes the other fields to default values and returns the pointer to the node
{
    	Tree* temp =  (Tree*)malloc(sizeof(Tree)); //standard malloc call
    	temp->key = key; //assigning the key value as given in the parameter to the function
    	temp->left = NULL; //initializing the left child pointer to NULL
	temp->right = NULL; //initializing the right child pointer to NULL
	temp->parent = NULL; //initializing the parent pointer to NULL
	temp->isDeleted = UNMARKED; //initializing the markedDeleted field to 0, as the node has not yet been deleted
    	return temp; //returning the pointer to this node
}

void rebuild(Tree** node, int a[], int l, int r) //a function that builds (or rebuilds to give) a balanced tree, given an array with the keys in sorted order
{
	int mid = (l+r)/2; //finding the middle index
	(*node)->key = a[mid]; //storing the key at the middle index position, in the root

	if(l >= 0 && r >= 0 && l < r) //if there are more keys left in the array
	{	
		//create a new node for the left and right children as the case may be, and maintain the link with the parent
		if(l != mid)
		{
			(*node)->left = newNode(DUMMY);
			((*node)->left)->parent = *node;
		}
		else
		{
			(*node)->left = NULL;
		}
		if(r != mid)
		{
			(*node)->right = newNode(DUMMY);
			((*node)->right)->parent = *node;
		}
		else
		{
			(*node)->right = NULL;
		}

		/*as long as the children of the root ar not NULL, recursively rebuild the left and
		right subtrees of the root, by passing the appropriate index positions of the array*/
		if((*node)->left != NULL)
		{
			rebuild(&((*node)->left), a, l, mid-1);
		}
		
		if((*node)->right != NULL)
		{
			rebuild(&((*node)->right), a, mid+1, r);
		}
	}
}

void createTree(int array[], int n, Tree** root) //a function to create the tree initially
{
	//assigning some predefined values to the nodes' keys (indirectly through the array elements), to start with
	array[0] = 25;
	array[1] = 50;
	array[2] = 75;
	array[3] = 100;
	array[4] = 125;
	array[5] = 150;
	array[6] = 160;
	array[7] = 175;
	array[8] = 180;

	rebuild(root, array, 0, n-1); 

	/*We are calling the "rebuild" function here, to "build" the tree, as it constructs a balanced tree. 
	If we continuously insert the nodes into the tree using a for loop that runs through all the 
	array elements, then, unless we have initialized the array in a particular order, there is no 
	guarantee that the resulting tree will be balanced, and we will have to do the rebuilding
	anyway. So, to save time and unnecessary computation, we just call rebuild() here.*/
}

int isLeaf(Tree* ptr) //a simple function that checks if a given node is a leaf, i.e, if both its children point to NULL
{
	if(ptr->left == NULL && ptr->right == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

Tree* lookup(Tree* root, int query) //a function that searches for a node with a given query element as its key
{
	if(root != NULL) //if the pointer passed to the function is not yet NULL
	{
		if(query == root->key) //if the query key is found
		{
			return root;
		}
		else if(query > root->key) //if the query element is larger than the current node's key, recursively search in the right subtree
		{
			return lookup(root->right, query);
		}
		else if(query < root->key) //if the query element is smaller than the current node's key, recursively search in the left subtree
		{
			return lookup(root->left, query);
		}
	}
	else //if the pointer is NULL, that means we have reached the end of the path, after a leaf
	{
		return NULL; //so the element is not found
	}

	/*Note that, here we are not checking if a given node is marked deleted or not. 
	That is checked, whenever and wherever required, in the main function itself.*/
}

Tree* findMin(Tree* root) //a simple function that iteratively finds the minimum key in a tree, by continuously following the left pointers from the root
{
	while(root->left != NULL)
	{
		root = root->left;
	}
	return root;
}

Tree* findMax(Tree* root) //a simple function that iteratively finds the maximum key in a tree, by continuously following the right pointers from the root
{
	while(root->right != NULL)
	{
		root = root->right;
	}
	return root;
}
  
void insertNode(Tree** root, int value) //a function to insert a node with a given key value into the tree
{
	Tree* prev;
	Tree* curr;
	prev = NULL;
	curr = *root;  	
	
	while(curr != NULL) //travelling down the tree to find the correct place to insert the new node
	{
		prev = curr;
		if(value < curr->key)
		{
			curr = curr->left;
		}
		else
		{
			curr = curr->right;
		}
	}

	//creating a new node and making prev as its parent
	Tree* node;
	node = newNode(value);
	node->parent = prev;
	
	if(prev == NULL) //in case the new node is the root itself
	{
		*root = node;	
	}
	//maintaining the relation between prev (parent) and new node (child)
	else if(value < prev->key)
	{
		prev->left = node;
	}
	else
	{
		prev->right = node;
	} 
}	

void inOrderTraversal(Tree* root) //a function that performs the standard in-order traversal of the tree
{
	if(root->left != NULL)
	{
		inOrderTraversal(root->left);
	}
		
	if(root->isDeleted == UNMARKED) //if the node is not marked deleted, nothing to worry about
	{
		printf("%d ", root->key);
	}

	else if(root->isDeleted == MARKED) //if a node is marked deleted, then we print (d) beside it to make this clear
	{
		printf("%d (d) ", root->key);
	}

	if(root->right != NULL)
	{
		inOrderTraversal(root->right);
	}
}

void printToArray(int a[], int key) //a function that stores the key sent by inOrder() in the next "unfilled" position of the array
{
	int i = 0;
	while(a[i] != SENTINEL) //the fact that all the elements in the array were initially set to a sentinel value helps here
	{
		i++;
	}
	a[i] = key;

}

void inOrder(Tree* root, int a[]) //a function that traverses the tree in order, and stores the keys into an array
{
	if(root->left != NULL)
	{
		inOrder(root->left, a);
	}
		
	printToArray(a, root->key); //storing the key in an array, a[]
	
	if(root->right != NULL)
	{
		inOrder(root->right, a);
	}
}

int find_n(Tree* node) //a recursive function that finds the "size" of a node, i.e., the number of nodes in the tree rooted at this node
{
	int i = 1;
	if(node == NULL) //base case
	{
		return 0;
	}
	if(isLeaf(node)) //another base case; if the node is a leaf, then only one node is there in the tree rooted at that node
	{
		return 1;
	}
	//depending on whether the node has a left child or a right child or both, using recursion to find out the "size" of the node
	else if(node->right == NULL && node->left != NULL)
	{
		i = i + find_n(node->left);
	}
	else if(node->right != NULL && node->left == NULL)
	{
			i = i + find_n(node->right);
	}
	else 
	{
		i = i + find_n(node->left) + find_n(node->right);
	}

	return i;
}

void reviseArray(int array[], int N, int d, Tree* root) //a function that revises the array of keys of all nodes present, to make it store only the unmarked ones
{
	int i, j;
	Tree* temp;
	
	for(i = 0; i < N; i++) //looping through the array, and replacing the keys all the nodes that are marked with a predefined sentinel value
	{
		temp = lookup(root, array[i]);
		if(temp->isDeleted == MARKED)
		{
			array[i] = SENTINEL;
		}
	}
	
	for(i = 0; i < N; i++) //shifting only the relevant values forward and pushing the sentinels to the end of the array
	{
		if(array[i] == SENTINEL)
		{
			j = i+1;
			while(j < N && array[j] == SENTINEL)
			{
				j++;
			}
			if(j < N)
			{
				array[i] = array[j];
				array[j] = SENTINEL;
			}
		}



	}	
}

int generate_choice() //a simple function that generates the option of which operation is to be performed on the tree
{
	if(rand()%2 == 1) //~half the time, look-up operation
	{
		return 1;
	}

	else
	{
		if(rand()%100 < 65) //~65% of the remaining time, insert operation
		{
			return 2; 
		}
		else //otherwise, delete operation
		{
			return 3; 
		}
	}
}

void deleteLeaf(Tree** leaf) //a function that deleted a leaf node by setting its parent's child fields to NULL appropriately, and freeing the node itself
{	
	if(((*leaf)->parent)->left == *leaf)
	{
		((*leaf)->parent)->left = NULL;
	}
	else
	{
		((*leaf)->parent)->right = NULL;
	}
	free(*leaf);
}

void deleteSubTree(Tree** node) //a  recursive function to delete (free) all the nodes of a subtree, uses post order traversal
{
	if((*node)->left != NULL)
	{
		deleteSubTree(&((*node)->left));
	}

	if((*node)->right != NULL)
	{
		deleteSubTree(&((*node)->right));
	}

	deleteLeaf(node);
}

void delete(Tree** ptr) //a function that well-and-truly deletes a node in a tree (not lazy-delete, or mark delete)
{
	Tree* temp;
	if(isLeaf(*ptr)) //if the node to be deleted is a leaf, it is a straight-forward step
	{
		deleteLeaf(ptr);
	}
	else if((*ptr)->right != NULL) //if the right child of the node is not NULL
	{
		if((*ptr)->left == NULL) //if the left child is NULL, then we just have to make the node's parent's right child, the node's right child
		{
			((*ptr)->parent)->right = (*ptr)->right;
		}
		else //if the left child is also not NULL
		{
			temp = findMin((*ptr)->right); //find the left-most child of the right subtree of the node	
			(*ptr)->key = temp->key; //put that key value in place of the key value of the node
			//now, we delete that left-most child; it is either a leaf, or has a right subtree alone
			if(isLeaf(temp))
			{			
				deleteLeaf(&temp);
			}
			else
			{
				(temp->parent)->left = temp->right;
			}
		}
	}
	else //if the right child of the node is NULL; obviously left child can't be NULL, as it would have been taken care in the leaf case
	{
		temp = findMax((*ptr)->left); //find the right-most child of the left subtree of the node
		(*ptr)->key = temp->key; //put that key value in place of the key value of the node
		//now, we delete that right-most child; it is either a leaf, or has a left subtree alone
		if(isLeaf(temp))
		{
			deleteLeaf(&temp);
		}
		else
		{
			(temp->parent)->right = temp->left;
		}
	}
}

int isLeftChild(Tree* node) //a simple function that checks if a given node is the left child of its parent, or not
{
	if((node->parent)->left == node)	
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void printLevel(Tree* node, int level) //a function to print the keys at a given height
{
	if(node == NULL) //trivial base case
	{
		return;
	}
	else if(level == 1) //base case
	{
		printf("%d ", node->key);
	}
	else if(level > 1) //recursive steps
	{
		printLevel(node->left, level-1);
		printLevel(node->right, level-1);
	}
}

int height(Tree* root) //a function to calculate the height of the tree
{
	if(root == NULL) //base case
	{
		return 0;
	}

	else
	{
		int leftHt = height(root->left); //find the height of the left tree
		int rightHt = height(root->right); //find the height of the right tree
		
		//height of the tree is the length of the longest path (either along the left subtree or the right one) from the root to a descendant leaf
		if(leftHt > rightHt) 
		{
			return(1 + leftHt);
		}
		else
		{
			return(1 + rightHt);
		}
	}
}	

void levelOrderTraversal(Tree* root) //a function to print the keys in level order
{
	int i, h;

	h = height(root);
	printf("Height of tree = %d\n", h); //printing the height of the tree

	for(i = 1; i <= h; i++) //running a loop to print the keys level by level
	{
		printLevel(root, i); //calling the printLevel() function for each level
		printf("\n");
	}
}
