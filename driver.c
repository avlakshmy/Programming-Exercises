#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"partial_tree.h"

#define SENTINEL -10101
#define UNMARKED 0
#define MARKED 1
#define DUMMY 9999
#define DEFAULT 9

//main() function to implement a partially-rebuilding tree
int main(void)
{
	srand(time(NULL)); //to randomize the rand() functions used in the various functions of the program
	
	printf("Let us look at the simulation of a partially rebuilding tree!\n\n");
	int N = DEFAULT; //to start with, assume a default value for number of elements in the tree
	int array[N];

	Tree* root;
	root = newNode(DUMMY); //creating root node

	createTree(array, N, &root); //creating the tree

	printf("In-order traversal:\n");
	inOrderTraversal(root); //printing the keys stored in the nodes of the tree in ascending order (using an in-order traversal)
	printf("\n");
	
	//declaring variables to be used in course of the program	
	int x, y, q, r, num, choice, h, markedDeleted = 0;
	Tree* temp;	
	Tree* random;
	Tree* temp2;
	Tree* temp1;
	Tree* le;
	Tree* ri;
	Tree* pa;
	int leftchild, rightchild;
	leftchild = rightchild = 0;

	int lim;

	printf("Enter the number of runs:\n"); //asking the user for number of runs
	scanf("%d", &lim);

	clock_t start, end; //declaring the clock variables to store the start and end time of execution
	
	start = clock(); //storing the start time of execution

	int ctr = 1; //initializing the counter for the loop

	while(ctr <= lim) //while loop that runs 'lim' number of times
	{
		choice = generate_choice(); //randomly generating an operation to be performed on the tree (i.e, search, insert or delete)

		if(choice == 1) //look-up operation
		{
			q = (rand()%1000) + 1; //generating a random key between 1 and 1000 to be looked up

			random = lookup(root, q); //calling the look-up function
		}

		else if(choice == 2) //insert operation
		{
			x = (rand()%1000) + 1; //generating a random key between 1 and 1000 to be inserted into the tree

			temp2 = lookup(root, x); //checking if that key is already present in the tree or not

			if(temp2 != NULL) //the element is present in the tree
			{
				if(temp2->isDeleted == MARKED) //if that node is marked deleted, just mark it as not deleted
				{
					temp2->isDeleted = UNMARKED;
				}
			}
			else //the element is not present in the tree
			{
				insertNode(&root, x); //calling the insert function
				N++; //incrementing the value of N, to store the number of nodes currently present in the tree 

				/*starting from the root, going downwards, we check if the tree is balanced at each node on the 
				path followed for inserting the node; if at any node on the way, the tree is not balanced, 
				we call the rebuild procedure and re-balance the tree*/
				
				temp1 = root; 
				
				while(temp1 != NULL)
				{
					num = find_n(temp1); //"size" of the node temp1
					le = temp1->left; //temporary variable to store the left child of temp1
					ri = temp1->right; //temporary variable to store the right child of temp1
								
					if(num < 2*find_n(ri) || num < 2*find_n(le)) //checking if the balance condition is violated
					{
						int a[num]; //declaring a new array of the size of the node

						for(h = 0; h < num; h++) //initializing the elements of this array to some predefined sentinel value
						{
							a[h] = SENTINEL;
						}
						inOrder(temp1, a); //we do in-order traversal of the subtree rooted at temp1, and store the keys in a[]
						
						//we rebuild the subtree rooted at temp1, so first, we re-initialize the fields of the node to default values

						if(temp1 == root) //if temp1 is the root of the tree itself, we just create a new node in its place
						{
							root = newNode(DUMMY);
							rebuild(&root, a, 0, num-1); //calling the rebuild function to rebuild the subtree rooted at temp1
						}

						else //if temp1 is not the root, we need to take care of maintaining the relation between temp1 and its parent
						{
							pa = temp1->parent; //temporary variable to store the pointer to the parent of temp1

							//checking if temp1 is the left child or right child of its parent
							if(isLeftChild(temp1))
							{
								leftchild = 1;
							}
							else
							{
								rightchild = 1;
							}

							temp1 = newNode(DUMMY);
												
							//retining the relation between temp1 and its parent	
							temp1->parent = pa;
							if(leftchild)
							{
								pa->left = temp1;
							}
							else
							{
								pa->right = temp1;
							}
							rebuild(&temp1, a, 0, num-1); //calling the rebuild function to rebuild the subtree rooted at temp1
						}
						 		
						break; //one rebuild is sufficient, after that we can break out of this loop and go on to the next run
					}
					else //if the balance condition is not violated, go onto to the next node along the path in which the node got inserted
					{
						if(x > (temp1->key))
						{
							temp1 = temp1->right;
						}	
						else
						{
							temp1 = temp1->left;
						}
					}
					
				}
			}
		}

		else if(choice == 3) //delete operation
		{
			q = 1 + rand()%1000; //generating a random key between 1 and 1000 to be deleted from the tree

			temp = lookup(root, q); //checking if the key is present in the tree or not

			if(temp != NULL) //if the key is present in the tree
			{
				if(temp->isDeleted == UNMARKED) //if the node was not already marked deleted
				{
					temp->isDeleted = MARKED; //first, mark it as deleted...
					markedDeleted++; //...and update the number of nodes marked deleted

					if(2*markedDeleted > N) //if the number of nodes marked deleted is greater than half the number of nodes in the tree
					{
						int a[N]; //create a new array and initialize all its elements to a predefined sentinel value
						for(h = 0; h < N; h++)
						{
							a[h] = SENTINEL;
						}						
						inOrder(root, a); //do an in-order traversal of the tree and store all the keys in this array
						//revise the array to store only the nodes that are not marked deleted		
						reviseArray(a, N, markedDeleted, root);	
						N = N - markedDeleted; //update the value of N
						markedDeleted = 0; //update the value of the number of nodes that are marked deleted

						//delete all the subtrees of the root						
						deleteSubTree(&(root->left)); 
						deleteSubTree(&(root->right));

						root = newNode(DUMMY); //create a new node for the root
						
						//rebuild the tree using only the keys that are not marked deleted					
						rebuild(&root, a, 0, N-1); 
					} 
				}
			}
		}
		
		//printing the run no., and the keys of the nodes present in the tree
		//printf("Run No. %d\n", ctr);
		//inOrderTraversal(root);
		//printf("\n\n");

		ctr++; //incrementing the value of the loop counter variable
		
	}

	end = clock(); //storing the end time of execution

	levelOrderTraversal(root); //calling the level order function
	
	double time_taken = (double)(end - start)/CLOCKS_PER_SEC; //finding the total execution time
	printf("Time taken = %.10lf\n", time_taken); //printing the total execution time	
	
	return 0;
}
