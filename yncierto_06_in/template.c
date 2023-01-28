/* ********************************************************* *
 * template.c                                                *
 *                                                           *
 * Template C Source File for AVL Insert.                    *
 *                                                           *
 * !!! DO NOT EDIT THE CONTENTS OF THE MAIN FUNCTION !!!     *
 *                                                           *
 * ********************************************************* */
#include "AVL.h"
#include <stdio.h>
#include <stdlib.h>

AVL_NODE * createAVLNode(int key){
    return createBSTNode(key, NULL, NULL, NULL);
}

AVL * createAVL(int max){
    return createBST(max);
}

/**** PUT YOUR FUNCTIONS HERE ******************************/
void leftRotate(AVL *A, AVL_NODE *node) {
	printf("Success\n");
	BST_NODE *temp = node->right; // pivot
	
	 if (node==A->root) {
 		printf("YES\n");
 		A->root = temp;
 		temp->parent = NULL;
 	}
 	
 	if(temp->left != NULL) {
 		BST_NODE *temp2 = temp->left; // left child of the pivot
 		node->right = temp2; // assign the left child of the pivot as the right child of the node
 		printf("not null\n");
 		temp2->parent = node;
 	}
 	
 	printf("null\n");
 	temp->left = node; // assign the node as the left child of the pivot
 	node->parent = temp; // make the pivot the parent of node

 	// update height
 	
 	node->height = max(heightOf(node->left), heightOf(node->right));
 	temp->height = max(heightOf(temp->left), heightOf(temp->right));
}

void rightRotate(AVL *A, AVL_NODE *node) {
 	BST_NODE *temp = node->left; // pivot
 	if (node==A->root) {
 		printf("YES\n");
 		A->root = temp;
 		temp->parent = NULL;
 	}
 	if(temp->left != NULL) {
 		BST_NODE *temp2 = temp->right; // left child of the pivot
 		node->left = temp2; // assign the left child of the pivot as the right child of the node
 		printf("not null\n");
 		temp2->parent = node;
 	}
 	temp->right = node; // assign the node as the right child of the pivot
 	node->parent = temp; // make the pivot the parent of node
 	// update height
 	node->height = max(heightOf(node->left), heightOf(node->right));
 	temp->height = max(heightOf(temp->left), heightOf(temp->right));
}

int heightOf(AVL_NODE *node) {
	if (node == NULL) 
		return -1;
	return node->height;
}

int checkBalance(AVL_NODE *node) {
	// if (node==NULL) 
	//	return 0;
	return heightOf(node->left) - heightOf(node->right);
}

AVL_NODE *getCritNode(AVL_NODE *node) {

	if(abs(checkBalance(node->parent)) > 1)
		return node->parent;
	node = node->parent->parent;
}

AVL_NODE *getPivot(AVL_NODE *node) {
	if(heightOf(node->left) > heightOf(node->right))
			return node->left;
	else 
			return node->right;
}
void AVLInsert(AVL *A, AVL_NODE *node) {
	AVL_NODE *pivot, *critNode;
	insert(A, node);
	int balance = checkBalance(A->root);
	printf("Height balanced: %d\n", balance);
	printf("node:%d\n", node->key);
	printf("Balanced: %d\n", abs(balance));
	
	if (abs(balance) > 1) {
		printf("critNode:%d\n", getCritNode(node)->key);
		critNode = getCritNode(node);
		pivot = getPivot(critNode);
		printf("pivot:%d\n", pivot->key);
		
		if(critNode->right == pivot && pivot->right == node) {  // right-right
			printf("here\n");
			leftRotate(A, critNode);
			}
			
		if(critNode->left == pivot && pivot-> left== node) // left-left
			rightRotate(A, critNode);
			
		if(critNode->right == pivot && pivot->left == node) { // right-left
			rightRotate(A, pivot);
			leftRotate(A, critNode);
		}
		
		if(critNode->left == pivot && pivot ->right == node) { // left-right
			leftRotate(A, pivot);
			rightRotate(A, critNode);
		}
	}
}


/**** FUNCTIONS ABOVE **************************************/

int main(){

	char command;
	int key, result;

	AVL *A = createAVL(100);
	AVL_NODE* node;
	while(1){
		scanf(" %c", &command);

		switch(command){
			case '+':
				scanf("%d", &key);
				printf("Inserting key: %d\n", key);
				AVLInsert(A, createAVLNode(key));
				break;
			case 'p':
				printf("Tree (rotated +90 degrees): \n");
				showTree(A);
				printf("\n");
				break;
			case 'C':
				printf("Removing all contents.\n");
				clear(A);
				break;
			case 'Q':
				clear(A);
				free(A);
				return 0;
            default:
                printf("Unknown command %c\n", command);
       }
    }
}
