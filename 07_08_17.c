#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 1000

void initializeLists(int allotInd[], int allotMem[], int freeInd[], int freeMem[]);
int request(int memSpace, int allotListStartIndex[], int allotListMemFilled[], int freeListIndex[], int freeListMemAvail[]);
int freeMem(int index, int allotListStartIndex[], int allotListMemFilled[], int freeListIndex[], int freeListMemAvail[]);
void clumpFreeSpace(int arrInd[], int arrMem[], int index);
void clumpAllottedSpace(int arrInd[], int arrMem[], int index);
void sortAllottedSpace(int allotInd[], int allotMem[]);
void sortFreeSpace(int freeInd[], int freeMem[]);
int findLeastEmptyIndex(int arr[]);
void shiftIndices(int indexArr[], int memArr[], int index);
void printList(int arrInd[], int arrMem[]);
int totalFreeSpace(int freeMem[]);

int main(void)
{
	int arr[MAX_SIZE]; //formally defining the memory array, but never used it in the code
	int allotListStartIndex[MAX_SIZE]; //an array to maintain the starting indices from which memory is allotted
	int allotListMemFilled[MAX_SIZE]; //an array to store the number of units of memory allotted from the corresponding start index onwards 
	int freeListIndex[MAX_SIZE]; //an array to maintain the starting indices of the free blocks of memory
	int freeListMemAvail[MAX_SIZE]; //an array to maintain the number of free units of memory available from the corresponding start index onwards
	
	int choice, ind, memReq, result;
	int itr = 1, j, h, n, var;

	initializeLists(allotListStartIndex, allotListMemFilled, freeListIndex, freeListMemAvail); //initialising the lists to their default values

	printf("Enter the number of funtion calls:\n"); //asking the user for the number of function calls
	scanf("%d", &n);
	
	printf("Enter <1><space><memory> to request for memory, or <2><space><index> to free memory at that index\n");	

	while(itr <= n) //while loop to accept the requests from the user
	{
		scanf("%d %d", &choice, &var); 
		//the choice variable is for allocating/freeing memory
		//the var variable is for memory to be allocated or start index of memory to be freed, respectively
		
		if(choice == 1) //for memory allotment
		{
			memReq = var;
			result = request(memReq, allotListStartIndex, allotListMemFilled, freeListIndex, freeListMemAvail); //calling the request function
			if(result == -1)
			{
				printf("Unable to allot this much memory\n");
			}
		}	
		else if(choice == 2) //for freeing memory
		{
			if(freeListIndex[0] == 0 && freeListMemAvail[0] == MAX_SIZE) //if the entire memory is already free
			{
				printf("No memory has been allotted that can be freed...\n");
				continue;
			}
			if(allotListStartIndex[var] == -1 || allotListMemFilled[var] == 0) //to check if any memory has at all been allocated at that index
			{
				printf("No memory has been allotted at that index\n");
				continue;
			}
			
			
			h = freeMem(var, allotListStartIndex, allotListMemFilled, freeListIndex, freeListMemAvail); //calling the freeMem function
			sortFreeSpace(freeListIndex, freeListMemAvail); //to sort the order of free space in the free list
			clumpFreeSpace(freeListIndex, freeListMemAvail, h); //to clump together free space, if required
			
			sortAllottedSpace(allotListStartIndex, allotListMemFilled); //to sort the order of allotted memory space in the allot list
		}
		//printing the current situation of memory allocation for the user to see
		printf("\n");
		printf("allotlist\n");
		printList(allotListStartIndex, allotListMemFilled);
		printf("\n");
		printf("freelist\n");
		printList(freeListIndex, freeListMemAvail);
		printf("\n");
		itr++;
	}

	printf("FINAL MEMORY ALLOTMENT AND FREE SPACE AVAILABLE:\n\n"); //printing final allocation of memory
	
	printf("\n");
	printf("allotlist\n");
	printList(allotListStartIndex, allotListMemFilled);
	printf("\n");
	printf("freelist\n");
	printList(freeListIndex, freeListMemAvail);
	printf("\n");

	return 0;
}

int request(int memSpace, int allotListStartIndex[], int allotListMemFilled[], int freeListIndex[], int freeListMemAvail[]) //function to allot memory
{
	int i = 0, v;
	int flag = 0;
	int x; 
	if(freeListIndex[0] == MAX_SIZE || memSpace > MAX_SIZE || memSpace > totalFreeSpace(freeListMemAvail)) 
	//free list is already empty, or requested space is more than the max size of the memory, or requested space is more than the total available free space
	{
		return -1;
	}
	while(i<findLeastEmptyIndex(freeListMemAvail))
	{
		x = findLeastEmptyIndex(allotListStartIndex);
		if(freeListMemAvail[i] >= memSpace) //free space is available
		{
			flag = 1;
			//updating the allot lists and free lists accordingly
			allotListStartIndex[x] = freeListIndex[i];
			allotListMemFilled[x] = memSpace;
			if(freeListMemAvail[i] == memSpace)
			{
				shiftIndices(freeListIndex, freeListMemAvail, i);
      			}
			else
			{
				freeListIndex[i] += memSpace;
				freeListMemAvail[i] -= memSpace;
			}
			sortAllottedSpace(allotListStartIndex, allotListMemFilled); //sorting the allotted space
			return 0;
		}
		i++;
	}
	
	if(flag == 0) //if the memory is not available in contiguous locations
	{
		//garbage collection
		if(allotListStartIndex[0] != 0)
			allotListStartIndex[0] = 0;
		
		int j = 0;
		while(j < findLeastEmptyIndex(allotListStartIndex)-1)
		{
			if(allotListStartIndex[j] + allotListMemFilled[j] != allotListStartIndex[j+1])
			{
				clumpAllottedSpace(allotListStartIndex, allotListMemFilled, j+1); //grouping together the allotted spaces
			}
			else
			{
				j++;
			}
		}
		
		//updating freeList
		int y = findLeastEmptyIndex(allotListStartIndex);
		freeListIndex[0] = allotListStartIndex[y-1] + allotListMemFilled[y-1];
		freeListMemAvail[0] = MAX_SIZE - freeListIndex[0];
		v = 1;
		while(v <= findLeastEmptyIndex(freeListIndex)-1)
		{
			freeListIndex[v] = -1;
			v++;
		}

		//again checking the availability of required free space
		if(freeListMemAvail[0] >= memSpace)
		{
			//update allotList, freeList
			allotListStartIndex[y] = freeListIndex[0];
			allotListMemFilled[y] = memSpace;
			freeListIndex[0] += memSpace;
			freeListMemAvail[0] -= memSpace;
		}
		else //if fee space is still not sufficient
		{
			return -1;
		}
	}
}

int freeMem(int index, int allotListStartIndex[], int allotListMemFilled[], int freeListIndex[], int freeListMemAvail[]) //function to free memory
{
	int p = findLeastEmptyIndex(freeListIndex);
	freeListIndex[p] = allotListStartIndex[index];
	freeListMemAvail[p] = allotListMemFilled[index];
	allotListMemFilled[index] = 0;
	return p;	
}

void initializeLists(int allotInd[], int allotMem[], int freeInd[], int freeMem[]) //function that initializes the lists 
{
	int i = 0;

	while(i < MAX_SIZE)
	{
		allotInd[i] = allotMem[i] = -1; //indicates that no space is allocated yet
		i++;
	}

	freeInd[0] = 0;
	freeMem[0] = MAX_SIZE; //indicates that entire space is available for allocation
	
	i = 1;

	while(i < MAX_SIZE)
	{
		freeInd[i] = freeMem[i] = -1; 
		i++;
	}
}


int findLeastEmptyIndex(int arr[]) //function that finds the least unfilled index in the allot/ free lists
{
	int i = 0;
	for(i = 0; i < MAX_SIZE && arr[i] != -1; i++)
	{
		
	}
		return i;
}

void clumpFreeSpace(int arrInd[], int arrMem[], int index) //function to aggregate the free memory spaces, during garbage collection
{
	int i = 0;
	while(i < findLeastEmptyIndex(arrInd)-1)
	{
		if(arrInd[i] + arrMem[i] == arrInd[index]) //checking consecutive entries in the free lists from start
		{
			arrMem[i] += arrMem[index];
			arrInd[index] = arrMem[index] = -1;
			
			if(i < findLeastEmptyIndex(arrInd))
			{
				if(arrInd[i] + arrMem[i] == arrInd[i+1])
				{
					arrMem[i] += arrMem[i+1];
					shiftIndices(arrInd, arrMem, i+1);
				}
			}
		}
		if(arrInd[i] + arrMem[i] > arrInd[index])
		{
			break;
		}

		i++;
	}

	i = 0;
	while(i < findLeastEmptyIndex(arrInd)-1) //if after the given index clumping is required
	{
		if(arrInd[index] + arrMem[index] == arrInd[i])
		{
			arrInd[i] = arrInd[index];
			arrMem[i] += arrMem[index];
		}
		if(arrInd[index] + arrMem[index] > arrInd[i])
		{
			break;
		}

		i++;
	}

	i = 0;
	while(i < MAX_SIZE) //filling the rest of the lists with -1, to show that no entries are there
	{
		if(arrMem[i] == 0)
		{
			arrInd[i] = arrMem[i] = -1;
		}
		i++;
	}
}
	
void shiftIndices(int indexArr[], int memArr[], int index) //function to shift indices of the index and memory lists forward, to avoid unnecessary entries
{
	int x = findLeastEmptyIndex(indexArr) - 1;
	int i = index;

	while(i < x)
	{
		indexArr[i] = indexArr[i+1];
		memArr[i] = memArr[i+1];
		i++;
	}
		
	indexArr[i] = memArr[i] = -1;
}

void sortAllottedSpace(int allotInd[], int allotMem[]) //function to sort the allotted spaces in order of the index positions
{
	int i, temp, temp1, j, index;

	i = findLeastEmptyIndex(allotInd); 
	index = i-1;
	temp = allotInd[index];
	temp1 = allotMem[index];
	j = i-2;

	//somewhat similar to insertion sort algorithm, but only one pass is done through the array, 
	//since we are assuming that the rest of the list is sorted and only the last entry has to be shifted to its correct place

	while(j >= 0 && allotInd[j] > temp)
	{
		allotInd[j+1] = allotInd[j];
		allotMem[j+1] = allotMem[j];
         	j--;
	}
	allotInd[j+1] = temp;
	allotMem[j+1] = temp1;

}		

void clumpAllottedSpace(int allotInd[], int allotMem[], int index) //to clump together allotted space at that index position
{
	int d = allotInd[index-1] + allotMem[index-1];
	allotInd[index] = d;
}	

void printList(int arrInd[], int arrMem[]) //function to print the lists, index and memory
{
	int i, d = findLeastEmptyIndex(arrInd);
	for(i = 0; i < d; i++)
	{
		if(arrMem[i] == 0)
			continue;		
		printf("%d   %d    %d\n", i, arrInd[i], arrMem[i]);
	}
}

void sortFreeSpace(int freeInd[], int freeMem[]) //function to sort the free space in order of the indices
{
	int i, temp, temp1, j, index;
	i = findLeastEmptyIndex(freeInd); 
	index = i-1;
	temp = freeInd[index];
	temp1 = freeMem[index];
	j = i-2;
	
	//somewhat similar to insertion sort algorithm, but only one pass is done through the array, 
	//since we are assuming that the rest of the list is sorted and only the last entry has to be shifted to its correct place

	while(j >= 0 && freeInd[j] > temp) 
	{
		freeInd[j+1] = freeInd[j];
		freeMem[j+1] = freeMem[j];
         	j--;
	}
	freeInd[j+1] = temp;
	freeMem[j+1] = temp1;
}

int totalFreeSpace(int freeMem[]) //function to find out the total free space available
{
	int x = findLeastEmptyIndex(freeMem);
	int i = 0;
	int freeSpace = 0;
	while(i<x)
	{
		freeSpace += freeMem[i];
		i++;
	}
	return freeSpace;
}

			
