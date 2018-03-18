#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct node
{
	int key;
	struct node *parent;
	int rank;
};
typedef struct node Node;

Node* lookup(int key, int n, Node* arr[]) //this function checks whether a given key is present in the array of nodes or not
{
	int i;
	for(i = 0; i < n; i++) //a simple for loop that runs through the entire array, checking for the given key at each step
	{
		if(arr[i]->key == key)
		{
			return arr[i]; //if found, return the pointer to the node
		}
	}
	return NULL; //if not found
}		

void make(Node** x, int key) //the make() function creates a new node, whose leader is itself
{
	(*x)->key = key;
	(*x)->parent = *x;
	(*x)->rank = 0;
}

void link(Node**x, Node** y) //the link() function links two sets together, by linking their leaders, as per the ranks
{
	if((*x)->rank > (*y)->rank)
	{
		(*y)->parent = *x;
	}
	else 
	{
		(*x)->parent = *y;
	}
	if((*x)->rank == (*y)->rank)
	{
		(*y)->rank = (*y)->rank + 1;
	}
}

Node* findSet(Node** x) //the findSet() function finds the leader of the set, and simultaneously does path compression 
{
	if((*x) != (*x)->parent)
	{
		(*x)->parent = findSet(&((*x)->parent));
	}
	return ((*x)->parent);
}

void unite(Node** x, Node** y) //the unite() function finds the leaders of the two sets, and "links" them
{
	Node* lx;
	Node* ly;
	lx = findSet(x);
	ly = findSet(y);	
	link(&lx, &ly);
}

