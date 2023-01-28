#include "BST.h"
#include <stdio.h>
#include <stdlib.h>

BST_NODE* createBSTNode(int key, BST_NODE* L, BST_NODE* R, BST_NODE* P) {
	BST_NODE* node = (BST_NODE*)malloc(sizeof(BST_NODE)); // allocate memory
	node->key = key; // initialize key
	node->left = L; // initialize left pointer
	node->right = R; // initialize right pointer
	node->parent = P; // initialize parent pointer
	node->height = 0; // initialize height
	return node;
}

BST* createBST(int max) {
	BST* B = (BST*)malloc(sizeof(BST)); // allocate memory
	B->root = NULL; // initialize root
	B->maxSize = max; // initialize max size
	B->size = 0; // initialize size
	return B;
}

void preorderWalkHelper(BST_NODE* node) {
	if (node != NULL) { // if node is not null
		printf("%d ", node->key); // print key
		preorderWalkHelper(node->left); // recursively call left subtree
		preorderWalkHelper(node->right); // recursively call right subtree
	}
}
void preorderWalk(BST* B) {
	preorderWalkHelper(B->root); // call helper function
}

void inorderWalkHelper(BST_NODE* node) {
	if (node != NULL) { // if node is not null
		inorderWalkHelper(node->left); // recursively call left subtree
		printf("%d ", node->key); // print key
		inorderWalkHelper(node->right); // recursively call right subtree
	}
}

void inorderWalk(BST* B) {
	inorderWalkHelper(B->root); // call helper function
}

void postorderWalkHelper(BST_NODE* node) {
	if (node != NULL) { // if node is not null
		postorderWalkHelper(node->left); // recursively call left subtree
		postorderWalkHelper(node->right); // recursively call right subtree
		printf("%d ", node->key); // print key
	}
}

void postorderWalk(BST* B) {
	postorderWalkHelper(B->root); // call helper function
}


int isEmpty(BST* B) {
	if (B->root == NULL) { // if size is 0
		return 1;
	}
	else { // if size is not 0
		return 0;
	}
}

int isFull(BST* B) {
	if (B->size == B->maxSize) { // if size is equal to max size
		return 1;
	}
	else { // if size is not equal to max size
		return 0;
	}
}

int max(int a, int b) {
	if (a > b) { // if a is greater than b
		return a;
	}
	else { // if b is greater than a
		return b;
	}
}

void insert(BST* B, BST_NODE* node) {
	if (isEmpty(B)) { // if BST is empty
		B->root = node; // set root to node
		B->root->height = 0; // set height to 0
		B->size++; // increment size
	}
	else {
		BST_NODE* temp = B->root; // create temp node
		while (temp != NULL) { // while temp is not null
			// print the key of the current node
			// printf("%d (key inside while loop)\n", temp->key);
			if (node->key < temp->key) { // if node key is less than temp key
				if (temp->left == NULL) { // if temp left is null
					temp->left = node; // set temp left to node
					node->parent = temp; // set node parent to temp
					B->size++; // increment size
					break;
				}  {
					temp = temp->left; // set temp to temp left
				}
			} else {
				if (temp->right == NULL) { // if temp right is null
					temp->right = node; // set temp right to node
					node->parent = temp; // set node parent to temp
					B->size++; // increment size
					break;
				} else {
					temp = temp->right; // set temp to temp right
				}
			}
		}
		// printf("%d (key outside while loop)\n", temp->key);
		// printf("%d (key updating)\n", temp->key);
		while (temp!=NULL) { // while temp is not null
			// printf("%d (key updating height)\n", temp->key);
			if (temp->left != NULL && temp->right != NULL) { // if temp left and temp right are not null
				temp->height = max(temp->left->height, temp->right->height) + 1; // update height
			} else if (temp->left == NULL && temp->right != NULL) { // if temp left is null and temp right is not null
				temp->height = temp->right->height + 1; // update height
			}
			else {
				temp->height = temp->left->height + 1; // update height
			}
			temp = temp->parent; // set temp to temp parent
			}
		}
		
	}

BST_NODE* search(BST* B, int key) {
	BST_NODE* temp = B->root; // create temp node
	while (temp != NULL) { // while temp is not null
		if (temp->key == key) { // if temp key is equal to key
			return temp;
		}
		else if (key < temp->key) { // if key is less than temp key
			temp = temp->left; // set temp to temp left
		}
		else { // if key is greater than temp key
			temp = temp->right; // set temp to temp right
		}
	}
	return NULL;
}

BST_NODE* minimum(BST_NODE* n) {
	BST_NODE* temp = n; // create temp node
	while (temp->left != NULL) { // traverse the left subtrees
		temp = temp->left; 
	}
	return temp;
}

BST_NODE* maximum(BST_NODE* n) {
	BST_NODE* temp = n; // create temp node
	while (temp->right != NULL) { // traverse the right subtrees
		temp = temp->right; 
	}
	return temp;
}

BST_NODE* successor(BST_NODE* node) {
	if (node->right != NULL) { // if there is right child
		return minimum(node->right); // get the minimum of thr right subtree
	} else {
		BST_NODE* temp = node->parent; // create temp node initialize to the parent of the node
		while (temp != NULL && node == temp->left) { // temp is not NULL and the left child of parent is equal to node
			node = temp; // set node to temp
			temp = temp->parent; // set temp to parent of temp
		}
		return temp;
	}
}

int delete(BST* B, int key) {
	BST_NODE* node = search(B, key); // search for the node, returns the pointer to the node
	BST_NODE* temp = successor(node); // get the successor of the node
	//printf("node");
	//printf("%p\n", node);
	//printf("%d\n", node->key);
	// if (node == B->root) { // node is equal to the root
		// B->root = NULL;
		//} else 
		if (node->left == NULL && node->right == NULL) { // node does not have a child
				if (node->parent->left == node) { // node is currently the left child of its parent
					node->parent->left = NULL;
			} else { // node is the right child of its parent
				node->parent->right = NULL;
			}
			B->size--; // decrement size
		BST_NODE* temp = B->root; // create a temp node initialize the root
		while (temp!=NULL) { // iterate as long as temp is not NULL
			// updates height
			if (temp->left != NULL && temp->right != NULL) {
				temp->height = max(temp->left->height, temp->right->height) + 1;
			} else if (temp->left == NULL && temp->right != NULL) {
					temp->height = temp->right->height + 1; 
				} else if (temp->left != NULL && temp->right==NULL) {
					temp->height = temp->left->height + 1;
				} else {
					temp->height = 0;
				}
				temp = temp->parent;
			}
		}
		 else if (node->left == NULL && node->right != NULL) { // right child only
			if (node->parent->left == node) { // node is the left child of its parent
				node->parent->left = node->right;
			} else {
				node->parent->right = node->right; // node is the right child of its parent
			}
			free(node); // free node
			B->size--; // decrement
		} else if (node->left != NULL && node->right == NULL) { // left child only
			if (node->parent->left == node) { // node is the left child of its parent
				node->parent->left = node->left;
			} else {
				node->parent->right = node->left; // node is the right child of its parent
			}
			free(node); // free node
			B->size--; // decrement
		} else {
				BST_NODE* temp = successor(node); // create temp initialized as the successor node
				//printf("%d", temp->key);
				node->key = temp->key; 
				//printf("successor");
				//printf("%d\n", temp->key);
				if (node->left == temp) {
					node->left = NULL;
				} else {
					node->right = NULL;
				}
				B->size--;
				}
}
/*
BST_NODE* predecessor(BST_NODE* node) {

}

*/

void clear(BST* B) {
	while(B->root != NULL) {
		B->root = NULL;
		B->root=successor(B->root);
		}
}


// a recursive subroutine to display the BST in tree mode
void showTreeHelper(BST_NODE* node, int tabs){

	if(!node) return; // node is null, do nothing
	showTreeHelper(node->right, tabs + 1);
	for(int i=0; i<tabs; i++) printf("\t");
	printf("%d(%d)\n", node->key, node->height);
	showTreeHelper(node->left, tabs + 1);

}


void showTree(BST* B){
	showTreeHelper(B->root, 0);
}



int main(){

	char command;
	int key, result;

	BST *B = createBST(100);
	BST_NODE* node;
	while(1){
		scanf(" %c", &command);

		switch(command){
			case '+':
				scanf("%d", &key);
				printf("Inserting key: %d\n", key);
				insert(B, createBSTNode(key, NULL, NULL, NULL));
				break;
			case '-':
				scanf("%d", &key);
				printf("Removing node with key: %d\n", key);
				result = delete(B, key); // result is unused. print if u want
				break;
			case '?':
				scanf("%d", &key);
				printf("Searching node with key: %d. Location: %p\n", key, search(B, key));
				// (nil) means NULL pointer
				break;
			case 'p':
				printf("Tree (rotated +90 degrees): \n");
				showTree(B);
				printf("\n");
				break;
			case '<':
				printf("Pre-order Traversal: ");
				preorderWalk(B);
				printf("\n");
				break;
			case '>':
				printf("Post-order Traversal: ");
				postorderWalk(B);
				printf("\n");
				break;
			case '/':
				printf("In-order Traversal: ");
				inorderWalk(B);
				printf("\n");
				break;
			case 'm':
				node = minimum(B->root);
				if(node) printf("Minimum value: %d\n", node->key);
				else printf("(BST empty)\n");
				break;
			case 'M':
				node = maximum(B->root);
				if(node) printf("Maximum value: %d\n", node->key);
				else printf("(BST empty)\n");
				break;
			case 'E':
				printf("BST %s empty.\n", isEmpty(B)?"is":"is not");
				break;
			case 'F':
				printf("BST %s full.\n", isFull(B)?"is":"is not");
				break;
			case 'C':
				printf("Removing all contents.\n");
				clear(B);
				break;
			/* uncomment this for postlab
			case '[':
				scanf("%d", &key);
				node = search(B, key);
				if(!node){
					printf("%d not found\n", key);
				}else{
					node = predecessor(node);
					if(node)printf("Predecessor of %d is %d.\n", key, node->key);
					else printf("No predecessor for %d\n", key);
				}
				break;
			case ']':
				scanf("%d", &key);
				node = search(B, key);
				if(!node){
					printf("%d not found\n", key);
				}else{
					node = successor(node);
					if(node)printf("Successor of %d is %d.\n", key, node->key);
					else printf("No successor for %d\n", key);
				}
				break;
			*/
			case 'Q':
				clear(B);
				free(B);
				return 0;
			default:
				printf("Unknown command: %c\n", command);
		}
	}
	return 0;
}
