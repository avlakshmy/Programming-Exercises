#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define INSERT 1
#define DELETE 2

int* insert(int** arr, int* n, int  element, int* leastInd);
int* delete(int** arr, int* n, int* leastInd);
void copy(int *initArr, int n1, int *finArr, int n2, int op);
void fill(int* arr, int startIndex, int size, int flag);
int tossSimulator();
void printList(int* arr, int* size);

int main()
{
	int* arr; //pointer to the first place in the table
	int size = 1;
	int no_of_op;
	arr = (int*)malloc(size*sizeof(int)); //allotting space to the table
	*arr = -1; //assigning a dummy value of -1 to the first place
	int leastAvInd = 0; //to keep track of where to add elements or where to delete elements from
	int toss;
	int j;
	
	printf("Enter the number of operations:\n"); //asking the user for the number of operations to perform
	scanf("%d", &no_of_op);

	srand(time(NULL));
	
	clock_t start, end; //clock variables to keep track of time taken
	
	start = clock(); //noting down the start time of the calculations

	for(j = 1; j <= no_of_op; j++)
	{
		toss = tossSimulator(); //to simulate the tossing of a biased coin which gives heads 60% of the time, and tails 40% of the time

		if(toss == 1) //if heads, insert element
		{			
			arr = insert(&arr, &size, rand()%10, &leastAvInd);			
		}
		else //if tails, delete the last filled element
		{
			if(leastAvInd == 0)
			{
				continue;
			}
			else
			{
				arr = delete(&arr, &size, &leastAvInd);
			}
		}
		printList(arr, &size); //printing the table
	}

	end = clock(); //noting down the end time of calculations

	float timeTaken = (float)(end - start)/CLOCKS_PER_SEC; //finding the total time taken
	printf("\n");
	printf("For no. of operations = %d, time taken = %.10f\n", no_of_op, timeTaken); //printing time taken
	return 0;
}

void copy(int* initArr, int n1, int* finArr, int n2, int op) //function to copy the elements from one table to another
{
	int i = 0;	
	
	if(op == INSERT) //in the case of insert, the table size would double, so we need to copy elements upto n1 index
	{
		while(i < n1)
		{
			finArr[i] = initArr[i];
			i++;
		}
		fill(finArr, i, n2, -1);
		
	}
	else if(op == DELETE) //in the case of delete, the table size would half, so we need to copy elements upto n2 index
	{
		while(i < n2)
		{
			finArr[i] = initArr[i];
			i++;
		}
	}
}
	
				
int* insert(int** arr, int* n, int element, int* leastInd) //function to insert element into the table
{
	int x = *leastInd; 
	int s = 2*(*n);
	int* ptr;
	
	if(x == *n) //if table is full
	{
		ptr = (int*)malloc(s*sizeof(int)); //doubling the size of the table
		(*leastInd)++; //updating leastAvInd
		copy(*arr, *n, ptr, s, INSERT); //copying all the elements to the new table
		ptr[x] = element;
		fill(ptr, x+1, s, -1);
		*n = s;
		free(*arr);
		return ptr; //returning the new location of the table
	}
	
	(*arr)[x] = element;

	while((*arr)[*leastInd] >= 0 && (*leastInd)<(*n))
	{
		(*leastInd)++; //finding the least available position in the table
	}

	return (*arr);
}

int* delete(int** arr, int* n, int* leastInd) //function to delete the last-filled element in the table
{
	int* ptr;
	int s = (*n)/4;	
	int x = *leastInd;
	if(x == 0)
	{
		printf("No elements to delete...\n"); //if table is empty
		return *arr;
	}
	else
	{
		(*leastInd)--; //updating leastAvInd
		(*arr)[*leastInd] = -1; //shifting the least available index back by one position, automatically ensures that the last position is now given up
		if(s > 0 && x == s) //if filled elements occupy only 1/4 of the table size
		{
			ptr = (int*)malloc(s*sizeof(int)); //allocate memory space equal to half of the current size
			copy(*arr, *n, ptr, s, DELETE); //copy all the elements
			if(*leastInd != 0)
			{
				ptr[x+1] = -1;
			}
			free(*arr);
			*n = s;
			return ptr; //return pointer to new location of table
		}
		else
		{
			if(*n == 2 || *n == 1)
			{
				ptr = (int*)malloc(sizeof(int)); 
				*ptr = (*arr)[0];
				free(*arr);
				*n = 1;
				return ptr;
			}
			else
			{
				return *arr;
			}
		}
	}	
}
		
//function to fill the remaining entries of table with a flag (-1) to show that space is available but unoccupied
void fill(int arr[], int startIndex, int size, int flag) 
{
	while(startIndex < size)
	{
		arr[startIndex] = flag;
		startIndex++;
	}
}

int tossSimulator()
{
	if((rand()%100) < 60)
	{
		return 1; //out of 100, 60 times it will return 1 (heads)
	}
	else
	{
		return 0; //out of 100, 40 times it will return 0 (tails)
	}
}


void printList(int* arr, int* size) //function to print the table
{
	int i, d = *size;
	printf("\n");
	if(arr[0] == -1) //if table is empty, don't print anything
	{
		printf("-----\n");
		return;
	}	
	for(i = 0; i < d; i++)
	{
		if(arr[i] == -1) //signifies end of table
		{
			break;
		}
		else
		{
			printf("%d   ", arr[i]);
		}
	}
	printf("\n");
}


