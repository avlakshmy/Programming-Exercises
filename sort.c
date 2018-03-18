#include<stdio.h>

void createArray(int array[], int size); 
void printArr(int array[], int size);
void swap(int array[], int ind1, int ind2);
void quicksort(int array[], int start, int end);
int findPivot(int array[], int start, int end);
void mergesort(int array[], int start, int end);
void merge(int array[], int start, int mid, int end);
void mergesortSpl(int array[], int start, int end);
void mergeSpl(int array[], int start, int mid, int end);
void copy(int arrayFrom[], int arrayTo[], int start, int end);

int main()
{
	int n, m;
	printf("Enter 0 for merge sort, 1 for quick sort, and 2 for merge sort (special)\n"); //displaying the menu for different operations
	scanf("%d", & m);
	printf("Enter the number of elements:\t"); //asking the user for number of elements to be sorted
	scanf("%d", &n);
	int array[n];
	printf("Enter the elements one by one:\n"); //asking the user to enter the array elements one by one
	createArray(array, n); //creating the array
	//using a switch statement to call the appropriate functions
	switch(m)
	{
		case 0:
			mergesort(array, 0, n-1); //merge sort function
			break;
		case 1:
			quicksort(array, 0, n-1); //quick sort function
			break;
		case 2:
			mergesortSpl(array, 0, n-1); //merge sort without using an extra array
			break;
		default:
			printf("Invalid entry!\n"); //to take care of undesirable entries 
			break;
	}
	printArr(array, n); //printing the sorted array

	return 0;
}

void createArray(int array[], int size) //a function to create the array as per user input
{	
	int i;
	for(i = 0; i < size; i++)
	{
		scanf("%d", &array[i]);
	}
}

void quicksort(int array[], int start, int end) //function to implement quicksort
{
	int pivot;
	if(start < end)
	{
		pivot = findPivot(array, start, end); //putting the pivot element in its correct place, and returning the pivot element's new index
		quicksort(array, start, pivot - 1); //recursively following the same procedure for the part of the array to the left of the pivot
		quicksort(array, pivot + 1, end); //recursively following the same procedure for the part of the array to the right of the pivot
	}	
}

int findPivot(int array[], int start, int end) //function to get the pivot element in its correct place
{
	int pivot = start; //we take the pivot element as the first element in the array
	int left = start;
	int right = end;

	swap(array, pivot, right); //swapping the pivot element with the last element

	while(left < right)
	{
		while(array[left] <= array[pivot] && left <= end) //moving the left variable to the right till we reach an element larger than the pivot element
		{
			left++;
		}
		while(array[right] > array[pivot]) //moving the right variable to the left till we reach an element smaller than the pivot element
		{
			right--;
		}
		if(left < right) //if the left and right variables have crossed each other, we swap the elements stored in them
		{
			swap(array, left, right);
		}
	}

	swap(array, pivot, right); //finally, we swap back the right element and the pivot
	return right; 
}

void mergesort(int array[], int start, int end) //function to implement merge sort
{
	int mid;
	if(start < end)
	{
		mid = (start + end)/2;	//calculating the middle index
		mergesort(array, start, mid); //sorting the left subarray
		mergesort(array, mid + 1, end); //sorting the right subarray
		merge(array, start, mid, end); //merging the two sorted subarrays
	}
	
}

void merge(int array[], int start, int mid, int end) //function to merge two sorted subarrays into a single array, using O(n) extra space
{
	int n1 = mid - start + 1; //number of elements in the first part
	int n2 = end - mid; //number of elements in the second part
	int arr1[n1];
	int arr2[n2];	
	copy(array, arr1, start, mid); //storing the first part in a separate array
	copy(array, arr2, mid + 1, end); //storing the second part in a separate array
	int a, b, c;
	c = start;
	a = b = 0;
	//the actual merge procedure
	while(a < n1 && b < n2)
	{
		if(arr1[a] < arr2[b]) 
		{
			array[c] = arr1[a];
			a++;
		}
		else
		{
			array[c] = arr2[b];
			b++;
		}
		c++;
	}
	while(a < n1) //if any more elements are there in the first array, they are already sorted, so they can be directly copied into the final array
	{	
		array[c] = arr1[a];
		a++;
		c++;
	}
	while(b < n2) //if any more elements are there in the second array, they are already sorted, so they can be directly copied into the final array
	{	
		array[c] = arr2[b];
		b++;
		c++;
	}		
}

void mergesortSpl(int array[], int start, int end) //function to implement merge sort 
{
	int mid;
	if(start < end)
	{
		mid = (start + end)/2; //finding the middle index
		mergesort(array, start, mid); //sorting the left half
		mergesort(array, mid + 1, end); //sorting the right half
		mergeSpl(array, start, mid, end); //merging the two sorted halves without using an extra array
	}
	
}

void mergeSpl(int array[], int start, int mid, int end)
{
	int n1 = mid - start + 1; //the number of elememts in the first part
	int n2 = end - start + 1; //the number of elements in the second part
	
	int i, temp, j;

	for(i = n1; i < n2; i++) //applying insertion sort from the second part onwards, into the first part
	{
		temp = array[i];
		j = i-1;

		while(j >= 0 && array[j] > temp)
		{
			array[j+1] = array[j];
           		j--;
		}
		array[j+1] = temp;
	}		
}			

void copy(int arrayFrom[], int arrayTo[], int start, int end) //a function to copy the elements of one array into another
{
	int i, j;
	j = 0;
	for(i = start; i <= end; i++)
	{
		arrayTo[j] = arrayFrom[i];
		j++;
	}
}	

void printArr(int array[], int size) //a function to print the array elements
{
	printf("Printing array elements:\n");	
	int i;
	for(i = 0; i < size; i++)
	{
		printf("%d ", array[i]);
	}
	
	printf("\n");
}

void swap(int array[], int ind1, int ind2) //a function to swap two array elements
{
	int temp;
	temp = array[ind1];
	array[ind1] = array[ind2];
	array[ind2] = temp;
}
