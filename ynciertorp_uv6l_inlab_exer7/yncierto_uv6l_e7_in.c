/*
 * Name: 
 * Lab Section: 
 * Program Description: 
*/

#include "heap.h"
#include <stdio.h>
#include <stdlib.h>


HEAP* createHeap(int maxSize) {
	HEAP* H = (HEAP*) malloc(sizeof(HEAP));
	H->heap = (int*) malloc(sizeof(int)*maxSize);
	H->size = 0;
	H->maxSize = maxSize;
	return H;
}

int isFull(HEAP *H) {
	if (H->size == H->maxSize) {
		return 1;
	} else {
		return 0;
	}
}

int isEmpty(HEAP *H) {
	if (H->size == 0) {
		return 1;
	} else {
		return 0;
	}
}	

void clear(HEAP *H) {
	H->size=0;
}

int left(int index){
  return(2 * index); 
}

int right(int index){
  return(2 * index + 1); 
}

int parent(int index){
  return(index / 2); 
}

void insert(HEAP *H, int key) {
	if(isFull(H)) {
		return;
	}
	H->size++;
	// printf("size: %d\n", H->size);
	H->heap[H->size] = key;
	int P = parent(H->size);
	// printf("parent: %d\n", P);
	int current = H->size;
	// printf("current: %d\n", current);
	while(P!=0) {
		// printf("current value: %d\n", H->heap[current]);
		// printf("parent parent value: %d\n", H->heap[P]);
		if(H->heap[current] < H->heap[P]) {
			// printf("TRUE\n");
			int temp = H->heap[P];
			H->heap[P] = H->heap[current];
			H->heap[current] = temp;
			// printf("after current value: %d\n", H->heap[current]);
			// printf("after parent value: %d\n", H->heap[P]);
			current = P;
			// printf("current: %d\n", current);
			P = parent(current);
			// printf("parent: %d\n", P);
		} else {
			break;
		}
	}
}

int deleteM(HEAP *H) {
	return 0;
}

/*
int deleteM(HEAP *H) {
	if(isEmpty(H)) {
	}
	// printf("size: %d\n", H->size);
	if(H->size == 1) {
		// printf("TRUE");
		int key = H->heap[1];
		H->size = 0;
		return key;
	}
	int temp = H->heap[1];
	H->heap[1] = H->heap[H->size];
	H->heap[H->size] = temp;
	printf("root value: %d\n", H->heap[1]);
	printf("last value: %d\n", H->heap[H->size]);
	int L = left(1);
	int R = right(1);
	int current = 1;
	while (L <= H->size) {
		if (R > H->size) {
				int temp = H->heap[current];
				H->heap[current] = H->heap[H->size];
				H->heap[H->size] = temp;
				current = L;
		}
	}
}

	int L = left(1);
	int R = right(1);
	printf("left: %d\n", L);
	printf("left: %d\n", R);
	int current = 1;
	while (L <= H->size) {
		if (R > H->size) {
				int temp = H->heap[current];
				H->heap[current] = H->heap[H->size];
				H->heap[H->size] = temp;
				current = L;
		}
		if (R <= H->size) {
			if (H->heap[L] < H->heap[R]) {
				if(H->heap[current] > H->heap[L]) {
					int temp = H->heap[current];
					H->heap[current] = H->heap[L];
					H->heap[L] = temp;
					current = L;
					L= left (L);
					R = right(L);
				}
			} else {
				if(H->heap[current] > H->heap[R]) {
					int temp = H->heap[current];
					H->heap[current] = H->heap[R];
					H->heap[R] = temp;
					current = L;
					L= left (R);
					R = right(R);
			}
		}
		}
	
		}
		return 0;
		}
		*/
	

void printHeapHelper(HEAP *H, int index, int tabs){
	if(index > H->size) return;
	else{
		printHeapHelper(H, right(index), tabs + 1);
		for(int i=0; i<tabs; i++) printf("\t");
		printf("%d\n", H->heap[index]);
		printHeapHelper(H, left(index), tabs + 1);
	}
}

void printHeap(HEAP *H){
	if(H!=NULL && H->size>0){
		printHeapHelper(H, 1, 0);
	}else{
		printf("Empty heap!\n");
	}
}


// IMPLEMENT FUNCTIONS HERE



int main(){

	char command;
	int key, result, type;
    int* sorted;

	HEAP *H = createHeap(30);

	while(1){
		scanf(" %c", &command);

		switch(command){
			case '+':
				scanf("%d", &key);
				printf("Inserting key: %d...\n", key);
				insert(H, key);
				break;
			case '-':
				printf("Removing root from tree...\n");
				result = deleteM(H); // result is unused
				break;
			case 'p':
				printf("Printing the heap (rotated +90 degrees)...\n");
				printHeap(H);
				printf("\n");
				break;
			case 'E':
				printf("Heap %s empty.\n", isEmpty(H)?"is":"is not");
				break;
			case 'F':
				printf("Heap %s full.\n", isFull(H)?"is":"is not");
				break;
			case 'C':
				printf("Removing all contents...\n");
				clear(H);
				break;
			/* uncomment this for postlab
			case '~':
				printf("The sorted version of the heap:\n");
				sorted = heapSort(H);
				for(key=1; key <= H->size; key++)
					printf("%4d", sorted[key]);
				printf("\n");
				free(sorted);
				break;
			*/
			case 'Q':
				free(H->heap);
				free(H);
				return 0;
			default:
				printf("Unknown command: %c\n", command);
		}
	}

	return 0;
}
