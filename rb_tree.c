#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define RED 0
#define BLACK 1
#define DEFAULT 7
#define DUMMY 9999
#define LEAF -1

typedef struct node
{
	int key;
	int colour;
	struct node *left;
	struct node *right;
	struct node *parent;
}Tree;

Tree* nil() //a function to create a leaf (or nil) node
{
    	Tree* temp =  (Tree*)malloc(sizeof(Tree));
    	temp->key = LEAF; //the key is assigned a special value, denoted by LEAF
    	temp->left = NULL;
	temp->right = NULL;
	temp->parent = NULL;
	temp->colour = BLACK; //coloured black in colour
    	return temp;
}

Tree* newNode(int key) //a function to create a new node, with a given key
{
    	Tree* temp =  (Tree*)malloc(sizeof(Tree));
    	temp->key = key; //assigning the key value to the new node
    	temp->left = nil();
	temp->right = nil();
	(temp->left)->parent = temp;
	(temp->right)->parent = temp;
	temp->parent = NULL;
	temp->colour = BLACK; //by default, we colour a new node black; if reqd, it is made red in the respective functions
    	return temp;
}

void build(Tree** node, int a[], int l, int r) //a function that builds a balanced tree, given an array with the keys in sorted order
{
	int mid = (l+r)/2; //finding the middle index
	(*node)->key = a[mid]; //storing the key at the middle index position, in the root

	if(l >= 0 && r >= 0 && l < r) //if there are more keys left in the array
	{	
		//create a new node for the left and right childs as the case may be, and maintain the link with the parent
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

		/*as long as the children of the root are not NULL, recursively rebuild the left and
		right subtrees of the root, by passing the appropriate index positions of the array*/
		if((*node)->left != NULL)
		{
			build(&((*node)->left), a, l, mid-1);
		}
		
		if((*node)->right != NULL)
		{
			build(&((*node)->right), a, mid+1, r);
		}
	}
}

Tree* lookup(Tree* root, int query) //a standard look-up function, which tells us whether or not a particular key value is present in the tree
{
	if(root->key != LEAF) //as long as the root of the subtree we are searching is not a leaf
	{
		if(query == root->key) //if found
		{
			return root;
		}
		else if(query > root->key) //if we need to search the right subtree
		{
			return lookup(root->right, query);
		}
		else if(query < root->key) //if we need to search the left subtree
		{
			return lookup(root->left, query);
		}
	}
	else //if not found
	{
		return NULL;
	}
}

void createTree(int n, Tree** root) //a function that creates an initial tree
{
	int array[n];
	//creating an array with some predefined key values
	array[0] = 25;
	array[1] = 50;
	array[2] = 75;
	array[3] = 100;
	array[4] = 125;
	array[5] = 150;
	array[6] = 175;

	build(root, array, 0, n-1); //building a balanced binary search tree, whose nodes are all coloured black
}

Tree* findMin(Tree* root) //a function to find the minimum-key-containing node in the tree, by continuously following the left pointers from the root
{
	while((root->left)->key != LEAF)
	{
		root = root->left;
	}
	return root;
}

int isNil(Tree* node) //a function that checks if a given node is a leaf (or nil) node
{
	if(node->key == LEAF)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void rightRotate(Tree** root, Tree** x) //a function that right rotates the node passed to it
{	
	Tree* y;
	y = (*x)->left;
	(*x)->left = y->right;
	(y->right)->parent = *x;
	y->parent = (*x)->parent;
	if(isNil((*x)->parent)) //taking care of the case when the node rotated is the root
	{
		*root = y;
	}
	else if((*x) == ((*x)->parent)->right)
	{
		((*x)->parent)->right = y;
	}
	else
	{
		((*x)->parent)->left = y;
	}
	y->right = *x;
	(*x)->parent = y;
}

void leftRotate(Tree** root, Tree** x) //a function that left rotates the node passed to it
{	
	Tree* y;
	y = (*x)->right;
	(*x)->right = y->left;
	(y->left)->parent = *x;
	y->parent = (*x)->parent;
	if(isNil((*x)->parent)) //taking care of the case when the node rotated is the root
	{
		*root = y;
	}
	else if((*x) == ((*x)->parent)->left)
	{
		((*x)->parent)->left = y;
	}
	else
	{
		((*x)->parent)->right = y;
	}
	y->left = *x;
	(*x)->parent = y;
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

void validateInsert(Tree** root, Tree** z)
{
	//a function to check if all red-black properties are satisfied; if not, some alterations are done to the tree to satisfy the properties
	Tree* sibling;
	Tree* temp;
	
	if(((*z)->parent)->colour == RED) //any property is violated only if the parent of the new (red) node is also red
	{
		//case 2
		if((*z)->parent == (((*z)->parent)->parent)->left) //if parent of the new node is the left child of its parent
		{
			//case 2.1
			sibling = (((*z)->parent)->parent)->right; //storing the pointer to the sibling of the parent
			if(sibling->colour == RED) //if the sibling of the parent is red in colour
			{
				//case 2.1.2
				//recolour the nodes
				((*z)->parent)->colour = BLACK;
				sibling->colour = BLACK;
				(((*z)->parent)->parent)->colour = RED;
				//this pushes the red colour to the parent of the parent of the node
				//now, we need to check if that node's parent is also red, and hence, continue the process
				(*z) = ((*z)->parent)->parent; //changing the pointer from z to that node
				validateInsert(root, z); //checking the properties for that node
			}
			else 
			{
				//case 2.1.1
				//if the sibling of the parent is black in colour
				if(*z == ((*z)->parent)->right) //case 2.1.1.1
				{
					(*z) = (*z)->parent;
					leftRotate(root, z);
					//after this, it reduces to case 2.1.1.2 below
				}
				//case 2.1.1.2
				//recolour, and then right rotate the parent of the parent of the node
				((*z)->parent)->colour = BLACK;
				(((*z)->parent)->parent)->colour = RED;
				temp = ((*z)->parent)->parent;
				rightRotate(root, &temp);
			}
		}
		else
		{
			//case 2.2
			//if parent of the new node is the right child of its parent
			sibling = (((*z)->parent)->parent)->left; //storing the pointer to the sibling of the parent
			if(sibling->colour == RED) //if the sibling of the parent is red in colour
			{
				//case 2.2.2
				//recolour the nodes
				((*z)->parent)->colour = BLACK;
				sibling->colour = BLACK;
				(((*z)->parent)->parent)->colour = RED;
				//this pushes the red colour to the parent of the parent of the node
				//now, we need to check if that node's parent is also red, and hence, continue the process
				(*z) = ((*z)->parent)->parent; //changing the pointer from z to that node
				validateInsert(root, z); //checking the properties for that node
			}
			else 
			{
				//case 2.2.1
				//if the sibling of the parent is black in colour
				if(*z == ((*z)->parent)->left) //case 2.2.1.1
				{
					(*z) = (*z)->parent;
					rightRotate(root, z);
					//after this, it reduces to case 2.2.1.2 below
				}
				//case 2.2.1.2
				//recolour, and then left rotate the parent of the parent of the node
				((*z)->parent)->colour = BLACK;
				(((*z)->parent)->parent)->colour = RED;
				temp = ((*z)->parent)->parent;
				leftRotate(root, &temp);
			}	
		}
	}
	
	(*root)->colour = BLACK; //in the process, if the root is made red, we recolour it back to black in colour
}

void insertNode(Tree** root, Tree** z) //a function that inserts a node into the tree
{
	Tree* prev; 
	Tree* curr;
	//pointers used to locate the correct position in the tree where the new node is to be inserted
	prev = nil();
	curr = *root;

	while(!(isNil(curr))) //traversing down the tree to find the correct location where the new node is to be inserted
	{
		prev = curr;
		if((*z)->key < prev->key)
		{
			curr = curr->left;
		}
		else
		{
			curr = curr->right;
		}
	}
	
	(*z)->parent = prev; //assigning the new node's parent pointer to prev
	
	if(isNil(prev)) //taking care of the case when the new node is the root itself
	{
		*root = *z;
	}
	else if((*z)->key < prev->key)
	{
		prev->left = *z;
	}
	else
	{
		prev->right = *z;
	}

	//initializing the fields of the new node
	(*z)->left = nil();	
	(*z)->right = nil();
	(*z)->colour = RED; //colour is made red
	
	validateInsert(root, z); //calling the validateInsert() function, to check whether all the red-black properties are satisfied
}

void move(Tree** root, Tree** n1, Tree** n2) //moves the subtree rooted at node n2 to the place of n1
{
	if(isNil((*n1)->parent))
	{
		*root = *n2;
	}
	else if(*n1 == ((*n1)->parent)->left)
	{
		((*n1)->parent)->left = *n2;
	}
	else
	{
		((*n1)->parent)->right = *n2;
	}
	(*n2)->parent = (*n1)->parent;
}

void validateDelete(Tree** root, Tree** z) 
{
	//a function to check if all red-black properties are satisfied; if not, some alterations are done to the tree to satisfy the properties
	Tree* sibling;
	if(*z != *root && (*z)->colour == BLACK)
	{
		if(*z == ((*z)->parent)->left) //if z is the left child of its parent
		{
			//case 1
			sibling = ((*z)->parent)->right; //storing the pointer to the sibling of z
			if(sibling->colour == RED) //if the sibling of z is red in colour
			{
				//case 1.2
				//recolouring the nodes and then left rotating the parent of z
				sibling->colour = BLACK; 
				((*z)->parent)->colour = RED;
				leftRotate(root, &((*z)->parent));
				sibling = ((*z)->parent)->right; //reduces to case 1.1 below
			}
			
			//case 1.1, sibling of z is black in colour
			if((sibling->left)->colour == BLACK && (sibling->right)->colour == BLACK) //case 1.1.4
			{
				sibling->colour = RED; //recolour the sibling
				*z = (*z)->parent; //now validate delete for the parent of z
				validateDelete(root, z);
			}
			else if((sibling->left)->colour == RED && (sibling->right)->colour == BLACK) //case 1.1.3
			{
				//recolour, right rotate sibling, then reduces to case 1.1.1
				(sibling->left)->colour = BLACK;
				sibling->colour = RED;
				rightRotate(root, &sibling);
				sibling = ((*z)->parent)->right;
				validateDelete(root, z);
			}
			else //cases 1.1.2 and 1.1.1
			{
				//recolour the nodes, and left rotate the parent of z
				sibling->colour = ((*z)->parent)->colour;
				((*z)->parent)->colour = BLACK;
				(sibling->right)->colour = BLACK;
				leftRotate(root, &((*z)->parent));
			}
		}

		else
		{
			//z is the right child of its parent
			//case 2
			sibling = ((*z)->parent)->left; //storing the pointer to the sibling of z
			if(sibling->colour == RED) //if the sibling of z is red in colour
			{
				//case 2.2
				//recolouring the nodes and then right rotating the parent of z
				sibling->colour = BLACK;
				((*z)->parent)->colour = RED;
				rightRotate(root, &((*z)->parent));
				sibling = ((*z)->parent)->left; //reduces to case 2.1 below
			}
			
			//case 2.1, sibling of z is black in colour
			if((sibling->right)->colour == BLACK && (sibling->left)->colour == BLACK) //case 2.1.4
			{
				sibling->colour = RED; //recolour the sibling
				*z = (*z)->parent; //now validate delete for the parent of z
				validateDelete(root, z);
			}
			else if((sibling->right)->colour == RED && (sibling->left)->colour == BLACK) //case 2.1.3
			{
				//recolour, right rotate sibling, then reduces to case 2.1.1
				(sibling->right)->colour = BLACK;
				sibling->colour = RED;
				leftRotate(root, &sibling);
				sibling = ((*z)->parent)->left;
				validateDelete(root, z);
			}
			else //cases 2.1.2 and 2.1.1
			{
				//recolour the nodes, and left rotate the parent of z
				sibling->colour = ((*z)->parent)->colour;
				((*z)->parent)->colour = BLACK;
				(sibling->left)->colour = BLACK;
				rightRotate(root, &((*z)->parent));
			}
		}
	}

	(*z)->colour = BLACK;
}

void deleteNode(Tree** root, Tree** z) //a function to delete a node in the tree
{
	Tree* y;
	Tree* x;
	y = *z;
	int col;
	col = y->colour; //storing the colour of the node being deleted
	if(isNil((*z)->left)) //takes care of the cases where the node being deleted has no left child, or has no children at all
	{
		x = (*z)->right; //storing the pointer to the node (with subtree) being moved
		move(root, z, &((*z)->right)); //moving the right subtree to its parent's place
	}
	else if(isNil((*z)->right)) //takes care of the case when the node being deleted has no right child (but has a left child, else taken care in prev case)
	{
		x = (*z)->left; //storing the pointer to the node (with subtree) being moved
		move(root, z, &((*z)->left)); //moving the left subtree to its parent's place
	}
	else
	{
		//case where the node being deleted has both children
		y = findMin((*z)->right); //finding the leftmost child of the right subtree
		col = y->colour; //storing the colour of this node, that has to be deleted after copying its value to the place of the node being deleted
		x = y->right; //storing the pointer to the node (with subtree) being moved

		if(y->parent == (*z)) //if the left most child of the right subtree of z is the right child of z itself
		{
			x->parent = y;
		}
		else
		{
			move(root, &y, &(y->right)); //pushing the right child of y to position of y
			y->right = (*z)->right;
			(y->right)->parent = y;
		}

		move(root, z, &y); //moves subtree rooted at y to position of z
		y->left = (*z)->left;
		(y->left)->parent = y;
		y->colour = (*z)->colour;
	}

	if(col == BLACK)
	{
		validateDelete(root, &x); //checking to see if all r-b properties are satisfied; if not, do some operations to make them satisfy
	}
}

void printLevel(Tree* node, int level) //a function to print the keys at a given height
{
	if(node == NULL) //trivial base case
	{
		return;
	}
	else
	{
		if(level == 0) //base case
		{
			printf("%d ", node->key); //printing the key
			//printing the colour of the node
			if(node->colour == BLACK)
			{
				printf("B ");
	
			}
			else if(node->colour == RED)
			{
				printf("R ");
			}
		}
		else //recursive steps
		{
			printLevel(node->left, level-1);
			printLevel(node->right, level-1);
		}
	}
}

int height(Tree* root) //a function to calculate the height of the tree
{
	if(root->key == LEAF) //base case
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

	for(i = 0; i <= h; i++) //running a loop to print the keys level by level
	{
		printLevel(root, i); //calling the printLevel() function for each level
		printf("\n");
	}
}	


