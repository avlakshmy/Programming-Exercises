#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "linked_list.h" //header file where all the function prototypes are specified

void recDoub(Node** head, Node* ptr[], int k, int n);

int main(int argc, char* argv[]) //main function, accepting k value from command line
{
	int n, k;
	k = atoi(argv[1]);	
	n = pow(2,k); //computing n value
	Node* head; //pointer to the first node of the linked list
	Node* ptr[n+1];	//an array of next pointers to each of the subsequent nodes of the linked list

	printf("Enter %d numbers, separated by space:\n", n);	
	
	createList(&head, ptr, n); //creating the linked list using the numbers entered by the user

	recDoub(&head, ptr, k, n); //calling the recDoub() function which implements recursive doubling to find prefix sums

	printf("The modified list is as follows:\n");
	printList(head, ptr, n);
	
	return 0;
}

void recDoub(Node** head, Node* ptr[], int k, int n) //to find the prefix sums using recursive doubling
{
	int i, j;
	Node* temp;
	temp = (*head);
	for(i = 0; i < k; i++)
	{
		for(j = 0; j < n; j++)
		{
			if(temp->next == NULL) 
			{
				continue;
			}
			else //recursive doubling implementation
			{
				(temp->value) += ((temp->next)->value); //adding the value stored in temp->next to the current temp->value
				(temp->next) = (temp->next)->next; //modifying the next pointer of the current node to next of next
				temp = ptr[j]; //moving temp to the next node of the linked list
			}
		}
		temp = *head; //resetting temp back to the beginning of the linked list
	}
}
