#include "BST.h"
#include <stdio.h>
#include <stdlib.h>


BST_NODE* createBSTNode(int key, BST_NODE* L, BST_NODE* R, BST_NODE* P) {
	BST_NODE * node = (BST_NODE *)malloc(sizeof(BST_NODE)); // allocate memory
	node->left = NULL; //  initialize to NULL
	node->right = NULL; //  initialize to NULL
	node->parent = NULL; //  initialize to NULL
	node->key = key; //  initialize to key
	return node;
}

BST* createBST(int max) {
	BST *bst = (BST *)malloc(sizeof(BST)); // allocate memory
	bst->root = NULL; //  initialize to NULL
	bst->maxSize = max; //  initialize to max
	bst->size = 0; //  initialize to 0
	return bst;
}


int isEmpty(BST* B) {
	if (B->root == NULL) { // root of Tree or Tree is empty
		return 1;
	} else {
		return 0;
	}
}


int isFull(BST* B) {
	if ( B->size >= B->maxSize) { // check if Tree is full
		return 1;
	} else {
		return 0;
	}
}


void insert(BST* B, BST_NODE* node) {
	BST_NODE* current = B->root; // root pointer
	BST_NODE* parent = NULL; // parent pointer
	if (current == NULL) { // first node
		B->root=node;
	} else { 
		while(current!=NULL) { // if the current pointer has a value or != NULL
			parent = current; // store current value to parent
			if(node<current) { // node is less than current value
				current = current->left; // current = left pointer
			} else { 
				current = current->right; // current = right pointer
			}
		}
	 	if(node<parent) { // node less than the current value before it got NULL
			parent->left=node; // store node to the left pointer
		} else {
			parent->right=node; // store node to the right pointer
		}
	}

}
/*
	BST_NODE* current = B->root;
	while(current!=NULL) {
		if(node<current) {
			current = current->left;
		} else {
			current = current->right;
		}
	} node->parent = current;
	if (current == NULL) {
		B->root=node;
	} else if(node<current) {
		current->left=node;
	} else {
		current->right=node;
	}
	
	
	
}}	
		
		
		/*
		}
		if(node < current) {
			if(current->left == NULL) {
				current->left = node;
				node->parent = current;	
			}
		} else {
			if(current->right == NULL) {
				current->right = node;
				node->parent = current;
			}
		}
		}
	}
	
		
		/*
			if (node->left == NULL) {
			
			
				current->left = node;
				node->parent = current;
			} else {
				current->left = current;
		} else {
			current->right = node;
		} node->parent = current; 
}
}
	/*node->parent = parent;
	if (parent = NULL) {
		B->root = node;
	}
	else if (node < parent->root) {
		parent->left = node;
	} else {
		parent-right = node;
	}
	
}
	
	//BST_NODE current = B->root;
	//printf("%d", **node);
	//}
	/*
	BST_NODE parent = NULL;
	while(current != NULL) {
		parent = current;
		if(B->root > current->root) {
			
		}
}

BST_NODE* search(BST* int) {

}
*/

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
//				printf("Searching node with key: %d. Location: %p\n", key, search(B, key));
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
			/* for the postlab, uncomment this
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
			*/
			case 'Q':
				return 0;
			default:
				printf("Unknown command: %c\n", command);
		}
	}

	return 0;
}
