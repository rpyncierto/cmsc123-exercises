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
	if (B->size == 0) { // if size is 0
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
			case 'E':
				printf("BST %s empty.\n", isEmpty(B)?"is":"is not");
				break;
			case 'F':
				printf("BST %s full.\n", isFull(B)?"is":"is not");
				break;
			// for the postlab, uncomment this
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
			
			case 'Q':
				return 0;
			default:
				printf("Unknown command: %c\n", command);
		}
	}
	return 0;
}