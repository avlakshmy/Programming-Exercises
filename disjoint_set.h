struct node
{
	int key;
	struct node *parent;
	int rank;
};
typedef struct node Node;

void make(Node** x, int key);
void unite(Node** x, Node** y);
void link(Node** x, Node** y);
Node* findSet(Node** x);
Node* lookup(int key, int n, Node* arr[]);
