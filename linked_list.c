#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct node
{
	int value;
	struct node *next;
};
typedef struct node Node;

void createList(Node** head, Node* ptr[], int n) //to create the linked list, and initialize the ptr array
{
	*head = (Node*)malloc(sizeof(Node));
	scanf("%d", &((*head)->value));
	Node* headFinal;
	headFinal = *head;
	
	Node* temp;
	
	int i;
	for(i = 1; i < n; i++) //creating the linked list using values entered by the user
	{
		temp = (Node*)malloc(sizeof(Node));
		scanf("%d", &(temp->value));
		(*head)->next = temp;
		*head = temp;
	}
	//creating the last node
	*head = (Node*)malloc(sizeof(Node));
	(*head)->value = 0; //storing 0 in the last node
	(*head)->next = NULL;
	temp->next = *head;	
	*head = headFinal;

	temp = (*head)->next;
	for(i = 0; i < n; i++) //initializing the ptr array to point to the next node of each node in the linked list
	{
		ptr[i] = temp; 
		temp = temp->next;
	}
	ptr[n] = NULL;
}


void printList(Node* head, Node* ptr[], int n) //to print the elements of the linked list
{
	int i = 0;
	Node* temp;
	temp = head;
	while(i < n)
	{
		printf("%d  ", temp->value);
		temp = ptr[i];
		i++;
	}	
	printf("\n");
}
