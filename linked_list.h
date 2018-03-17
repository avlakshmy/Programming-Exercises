struct node
{
	int value;
	struct node *next;
};
typedef struct node Node;

void printList(Node* head, Node* ptr[], int n);
void createList(Node** head, Node* ptr[], int n);
