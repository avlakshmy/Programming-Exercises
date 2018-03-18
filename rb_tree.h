typedef struct node
{
	int key;
	int colour;
	struct node *left;
	struct node *right;
	struct node *parent;
}Tree;

Tree* newNode(int key);
Tree* lookup(Tree* root, int query);
void createTree(int n, Tree** root);
Tree* findMin(Tree* root);
int isNil(Tree* node);
Tree* nil();
void rightRotate(Tree** x, Tree** root);
void leftRotate(Tree** root, Tree** z);
void insertNode(Tree** root, Tree** z);
void validateInsert(Tree** root, Tree** z);
void move(Tree** root, Tree** n1, Tree** n2);
void deleteNode(Tree** root, Tree** z);
void validateDelete(Tree** root, Tree** x);
void printLevel(Tree* node, int level);
int height(Tree* root);
void levelOrderTraversal(Tree* root);
void build(Tree** node, int a[], int l, int r);

