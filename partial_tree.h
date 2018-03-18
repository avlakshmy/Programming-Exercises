struct node 
{
	int key;
	int isDeleted;
	struct node *left;
	struct node *right;
	struct node *parent;
};
typedef struct node Tree;

void createTree(int array[], int n, Tree** root);
Tree* newNode(int key);
int isLeaf(Tree* ptr);
Tree* lookup(Tree* root, int query);
Tree* findMin(Tree* root);
Tree* findMax(Tree* root);
void rebuild(Tree** node, int a[], int l, int r);
void insertNode(Tree** root, int value);
void inOrderTraversal(Tree* root);
void inOrder(Tree* root, int a[]);
int find_n(Tree* node);
void printToArray(int a[], int key);
void reviseArray(int array[], int N, int d, Tree* root);
int generate_choice();
void deleteSubTree(Tree** node);
void delete(Tree** ptr);
void deleteLeaf(Tree** leaf);
int isLeftChild(Tree* node);
int height(Tree* root);
void printLevel(Tree* root, int level);
void levelOrderTraversal(Tree* root);
