#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"rb_tree.h"

#define RED 0
#define BLACK 1
#define DEFAULT 7
#define DUMMY 9999
#define LEAF -1

int main(void)
{
	srand(time(NULL));

	printf("Let us look at the simulation of a red-black tree!\n\n");	
	int n = DEFAULT;	
	
	Tree* root = newNode(DUMMY); //creating the root node
	root->parent = nil(); //making the parent of root, nil

	createTree(n, &root); //creating an initial red-black tree, having nodes with some predefined keys, all black in colour

	levelOrderTraversal(root); //printing the initial tree
	
	int q, choice, lim, ctr;
	Tree* temp;

	printf("Enter the number of runs:\n"); //asking the user for number of runs
	scanf("%d", &lim);

	clock_t start, end; //declaring the clock variables to store the start and end time of execution
	
	start = clock(); //storing the start time of execution

	ctr = 1; 
	while(ctr <= lim)
	{
		choice = generate_choice(); //generating a random option to decide which operation is to be carried out		

		/*if(choice == 1) //look-up operation
		{
			q = (rand()%1000) + 1; //generating a random key between 1 and 1000 to be looked up
			lookup(root, q); //calling the look-up function
		}
		*/

		if(choice == 2)//delete operation
		{
			q = 1 + rand()%1000; //generating a random key between 1 and 1000 to be deleted from the tree
			temp = lookup(root, q); //checking if the key is present in the tree or not
			if(temp != NULL)
			{
				deleteNode(&root, &temp); //deleting the node from the tree
			}
			printf("deletion\n");
		}
		else //insert operation
		{
			q = (rand()%1000) + 1; //generating a random key between 1 and 1000 to be inserted into the tree
			temp = lookup(root, q); //checking if that key is already present in the tree or not
			if(temp == NULL)
			{
				temp = newNode(q); //creating a new node
				insertNode(&root, &temp); //inserting the node into the red black tree				
			}
			printf("insertion\n");
		}
		
		levelOrderTraversal(root); //printing the tree at this stage

		ctr++; //incrementing the value of the loop counter variable
		
	}

	end = clock(); //storing the end time of execution
	
	double time_taken = (double)(end - start)/CLOCKS_PER_SEC; //finding the total execution time
	printf("Avg time taken = %.10lf\n", time_taken/lim); //printing the avg execution time
	
	return 0;
}
