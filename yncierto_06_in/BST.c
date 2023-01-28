/* ********************************************************* *
 * BST.c                                                     *
 *                                                           *
 * Contains the function definitions of all functions        *
 *    declared in BST.h.                                     *
 *                                                           *
 * !!! DO NOT EDIT LINES 11-28 !!!                           *
 *                                                           *
 * ********************************************************* */
#include "BST.h"
#include <stdio.h>
#include <stdlib.h>

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

/***********************************************************************/
/* Copy your previous function definitions for the functions in BST.h. */
/* PASTE THEM BELOW THIS COMMENT.                                      */
/***********************************************************************/

//your implementation for the functions in BST.h below !!!

// import your BST

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

/*
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
*/

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

void updateHeightInsertion(BST_NODE* node) {
	while (node != NULL) { // if node is not null
		if (node->left != NULL && node->right != NULL) { // if node left and node right are not null
			node->height = max(node->left->height, node->right->height) + 1; // update height
		} else if (node->left == NULL && node->right != NULL) { // if node left is null and node right is not null
			node->height = node->right->height + 1; // update height
		}
		else {
			node->height = node->left->height + 1; // update height
		}
		node = node->parent; // update node
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
		updateHeightInsertion(temp); // call update height helper function
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
		while (n->left != NULL) { // while n left is not null
			n = n->left; // set n to n left
		}
		return n; // return n
}

BST_NODE* maximum(BST_NODE* n) {
		while (n->right != NULL) { // while n right is not null
			n = n->right; // set n to n right
		}
		return n; // return n
}
/*
BST_NODE* predecessor(BST_NODE* node) {
	if (node->left != NULL) { // if node left is not null
		return maximum(node->left); // return maximum of node left
	}
	else { // if node left is null
		BST_NODE* temp = node->parent; // create temp node
		while (temp != NULL && node == temp->left) { // while temp is not null and node is equal to temp left
			node = temp; // set node to temp
			temp = temp->parent; // set temp to temp parent
		}
		return temp; // return temp
	}
}
*/
BST_NODE* successor(BST_NODE* node) {
	if (node->right != NULL) { // if node right is not null
		return minimum(node->right); // return minimum of node right
	}
	else { // if node right is null
		BST_NODE* temp = node->parent; // create temp node
		while (temp != NULL && node == temp->right) { // while temp is not null and node is equal to temp right
			node = temp; // set node to temp
			temp = temp->parent; // set temp to temp parent
		}
		return temp; // return temp
	}
}

void updateHeightDeletion(BST_NODE* node) {
	// traverse up the tree and update the height of each node
	if (node->parent == NULL) { // if node parent is null
		return;
	}
	else if (node->parent->left == NULL && node->parent->right == NULL) { // if node parent left and node parent right are null
		node->parent->height = 0;
	}
	else if (node->parent->left == NULL && node->parent->right != NULL) { // if node parent left is null and node parent right is not null
		node->parent->height = node->parent->right->height + 1;
	}
	else if (node->parent->left != NULL && node->parent->right == NULL) { // if node parent left is not null and node parent right is null
		node->parent->height = node->parent->left->height + 1;
	}
	else { // if node parent left and node parent right are not null
		node->parent->height = max(node->parent->left->height, node->parent->right->height) + 1;
	}
	updateHeightDeletion(node->parent); // call update height helper function
}

int delete(BST* B, int key) {
	BST_NODE* temp = search(B, key); // create temp node initialized as the pointer of the key
	// printf("%d (temp key)\n", temp->key);
	// printf("%d (root key)\n", B->root->key);
	if (temp == B->root) { // if temp is equal to root
		// if the root has no children
		if (temp->left == NULL && temp->right == NULL) {
			B->root = NULL; // set root to null
			B->size--; // decrement size
			free(temp); // free temp
		}
		// if the root has one child
		else if (temp->left == NULL && temp->right != NULL) {
			B->root = temp->right; // set root to temp right
			temp->right->parent = NULL; // set temp right parent to null
			B->size--;
			free(temp); // free temp
		}
		else if (temp->left != NULL && temp->right == NULL) {
			B->root = temp->left; // set root to temp left
			temp->left->parent = NULL; // set temp left parent to null
			B->size--;
			free(temp); // free temp
		} else { // if the root has two children
			BST_NODE* temp2 = successor(temp); // create temp2 node
			// printf("%d (temp2 key)", temp2->key);
			B->root->key = temp2->key; // set root key to temp2 key
			if (temp2->parent->left == temp2) { // if temp2 parent left is equal to temp2
				temp2->parent->left = temp2->right; // set temp2 parent left to temp2 right
			}
			else { // if temp2 parent left is not equal to temp2
				temp2->parent->right = temp2->right; // set temp2 parent right to temp2 right
			}
			if (temp2->right != NULL) { // if temp2 right is not null
				temp2->right->parent = temp2->parent; // set temp2 right parent to temp2 parent
			}
			if(temp2->right != NULL) { // if temp2 right is not null
				// printf("%d (temp2 right key)", temp2->right->key);
				temp2->right->height = temp2->height - 1; // set temp2 right height to temp2 height - 1
				updateHeightDeletion(temp2->right); // call update height deletion helper function
			}
			else {
				updateHeightDeletion(temp2->parent); // call update height deletion helper function
				//printf("%d (temp2 parent key)", temp2->parent->key);
			}
			free(temp2); // free temp2
			B->size--; // decrement size
		}
	}
	// node deletion with temp has no child
	else if (temp->left == NULL && temp->right == NULL) { // if temp left and temp right are null
		if (temp->parent->left == temp) { // if temp parent left is equal to temp
			temp->parent->left = NULL; // set temp parent left to null
		}
		else { // if temp parent left is not equal to temp
			temp->parent->right = NULL; // set temp parent right to null
		}
		free(temp); // free temp
		B->size--; // decrement size
	}
	// node deletion with temp has one child
	else if (temp->left == NULL || temp->right == NULL) { // if temp left or temp right is null
		if (temp->left == NULL) { // if temp left is null
			if (temp->parent->left == temp) { // if temp parent left is equal to temp
				temp->parent->left = temp->right; // set temp parent left to temp right
			}
			else { // if temp parent left is not equal to temp
				temp->parent->right = temp->right; // set temp parent right to temp right
			}
			temp->right->parent = temp->parent; // set temp right parent to temp parent
			free(temp); // free temp
			B->size--; // decrement size
		}
		else { // if temp left is not null
			if (temp->parent->left == temp) { // if temp parent left is equal to temp
				temp->parent->left = temp->left; // set temp parent left to temp left
			}
			else { // if temp parent left is not equal to temp
				temp->parent->right = temp->left; // set temp parent right to temp left
			}
			temp->left->parent = temp->parent; // set temp left parent to temp parent
			free(temp); // free temp
			B->size--; // decrement size
		}
	}
	// node deletion with two children
	else { // if temp left and temp right are not null
		BST_NODE* temp2 = successor(temp); // create temp2 node
		temp->key = temp2->key; // set temp key to temp2 key
		if (temp2->parent->left == temp2) { // if temp2 parent left is equal to temp2
			temp2->parent->left = temp2->right; // set temp2 parent left to temp2 right
		}
		else { // if temp2 parent left is not equal to temp2
			temp2->parent->right = temp2->right; // set temp2 parent right to temp2 right
		}
		if (temp2->right != NULL) { // if temp2 right is not null
			temp2->right->parent = temp2->parent; // set temp2 right parent to temp2 parent
		}
		free(temp2); // free temp2
		B->size--; // decrement size
	}
	// printf("%d (key after deletion)\n", temp->key);
	updateHeightDeletion(temp); // call update height deletion helper function
	return key;// return key
}

void clear(BST* B) {
	// clear the BST `B` by deleting the root until it exhaust the nodes
	while (B->root != NULL) {
		delete(B, B->root->key); // call delete function
	}
	B->size = 0;// set root to null
}
