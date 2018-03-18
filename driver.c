#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"disjoint_set.h"

int main(void)
{
	printf("Disjoint set union and find operation!\n");
	int n;
	printf("Enter the number of singleton disjoint 'sets'\n"); //taking the value of number of elements in the set
	scanf("%d", &n);
	int i, j;
	Node* temp[n]; //creating an array of "nodes"
	printf("Please supply the values of the elements one-by-one...\n");
	for(i = 0; i < n; i++) //initializing the array of nodes, as per the values entered by the user
	{
		temp[i] = (Node*)malloc(sizeof(Node));
		printf("Enter the element, array[%d]\t", i);
		scanf("%d", &j);
		make(&(temp[i]), j); //calling the make function that creates a new "node"
	}

	printf("The array of elements is:\n");
	//printing the array of elements
	for(i = 0; i < n; i++)
	{
		printf("%d\t", temp[i]->key);
	}

	printf("\n");

	int m, x1, x2, choice;
	Node* x;
	Node* y;
	printf("Enter the number of operations\n"); //taking the number of unite + findSet operations to be performed on the set
	scanf("%d", &m);

	for(i = 1; i <= m; i++) //running a for-loop 'm' number of times
	{
		printf("Enter the choice: 1-union, 2-findset\t"); //asking the user for the choice
		scanf("%d", &choice);
		if(choice == 1) //unite operation
		{
			printf("Enter the two keys whose sets you want to unite (separated by a space)\t");
			scanf("%d %d", &x1, &x2);
			x = lookup(x1, n, temp);
			y = lookup(x2, n, temp);
			if(x == NULL || y == NULL) //if no such element is there in the array
			{
				printf("Invalid entries\n");
				continue;
			}
			else
			{
				printf("Uniting the sets of %d and %d\n", x1, x2);
				unite(&x, &y); //calling the unite() function
			}
		}
		else if(choice == 2)//findSet operation
		{
			printf("Enter the key, the leader of whose set you want to find\t");
			scanf("%d", &x1);			
			x = lookup(x1, n, temp);
			if(x == NULL) //if no such element is there in the array
			{
				printf("Invalid entry\n");
				continue;
			}
			else
			{
				printf("Finding the leader of the set containing %d\n", x1);
				y = findSet(&x); //calling the findSet() function
				printf("The leader of this set is %d\n", y->key);
			}				
		}
		else
		{
			printf("Sorry, invalid entry!\n");
			continue;
		}
	

		for(j = 0; j < n; j++) //printing the keys with thir parents
		{
			printf("%d--->%d\t", temp[j]->key, (temp[j]->parent)->key);
		}
		printf("\n\n");		
	}

	printf("\n\n\n");
	//printing the nodes and their parents
	printf("Finally...\n");
	printf("Nodes and their parents are:\n\n");
	for(i = 0; i < n; i++)
	{
		printf("%d--->%d\t", temp[i]->key, (temp[i]->parent)->key);
	}
	printf("\n\n");

	return 0;
}
