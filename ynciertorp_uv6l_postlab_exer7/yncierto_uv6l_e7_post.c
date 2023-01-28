/*
 * Name: Reymond P. Yncierto
 * Lab Section: UV6L
 * Program Description: This program is an implementation of heap and the operations that can be done on it.
*/

#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

int left(int index){
  return(2 * index); 
}

int right(int index){
  return(2 * index + 1); 
}

int parent(int index){
  return(index / 2); 
}


void swap(int *a, int *b){ // swaps the values of a and b
  int temp = *a;
  *a = *b;
  *b = temp;
}


HEAP* createHeap(int maxSize){ // create a heap which accepts maxSize number of elements, initializes fields of the structure
  HEAP *H = (HEAP*)malloc(sizeof(HEAP)); // allocate memory for the heap
  H->heap = (int*)malloc(sizeof(int) * maxSize); // allocate memory for the heap array
  H->size = 0; // initialize
  H->maxSize = maxSize; // initialize
  return H; // return the heap
}

int isFull(HEAP *H){ // returns 1 if the heap is full, otherwise returns 0
  if(H->size == H->maxSize){
	return 1;
  }
  return 0;
}

int isEmpty(HEAP *H){ // returns 1 if the heap is empty, otherwise returns 0
  if(H->size == 0){
	return 1;
  }
  return 0;
}


void clear(HEAP *H){ // clear the heap
  H->size = 0; // set the size to 0
}


void insert(HEAP *H, int key) { // inserts key to the MIN HEAP H
	  if(isFull(H)){ // if the heap is full, return
	return;
  }
  H->size++; // increment the size
  H->heap[H->size] = key; // insert the key
  int index = H->size; // set the index to the size
  while(index > 1 && H->heap[parent(index)] > H->heap[index]){ // percolate up through the heap
	swap(&H->heap[parent(index)], &H->heap[index]); // swap the heap values
	index = parent(index); // swap the index
  }
}


int deleteM(HEAP *H){ // deletes the minimum value in the heap
	if(isEmpty(H)){ // if the heap is empty, return 
		return -1;
	}
	int temp; // temporary variable
	int min = H->heap[1]; // set the min to the root
	H->heap[1] = H->heap[H->size]; // swap the heap values
	H->size--; // decrement the size
	int current = 1; // set the current to 1
	while(current <= H->size){ // percolate down through the heap
		if(left(current) <= H->size && right(current) > H->size){ // if the root has only left child
			if(H->heap[current] > H->heap[left(current)]){ // if root key is greater than left child key, swap the heap values
				swap(&H->heap[current], &H->heap[left(current)]);
				// temp = H->heap[current]; 
				// H->heap[current] = H->heap[left(current)];
				// H->heap[left(current)] = temp;
				current = left(current);
			}
			else break;
		} else if(left(current) <= H->size && right(current) <= H->size){ // if the root has 2 children
			if(H->heap[current] > H->heap[left(current)] || H->heap[current] > H->heap[right(current)]){ // if root key is greater than left or right child key 
				if(H->heap[left(current)] < H->heap[right(current)]){ // if left key is smaller than right key, swap the heap values
					swap(&H->heap[current], &H->heap[left(current)]);
					// temp = H->heap[current];
					// H->heap[current] = H->heap[left(current)];
					// H->heap[left(current)] = temp;
					current = left(current);
				}
				else{ // if right key is smaller than left key, swap the heap values
					swap(&H->heap[current], &H->heap[right(current)]);
					// temp = H->heap[current];
					// H->heap[current] = H->heap[right(current)];
					// H->heap[right(current)] = temp;
					current = right(current);
				}
			}
			else break;
		}
		else break;
		
	}
  	return min;
}

int* heapSort(HEAP *H){ // returns an array containing the sorted values of the min heap without modifying the heap
	int *arr = (int*)malloc(sizeof(int) * H->size); // allocate memory for the array
	HEAP *temp = createHeap(H->size); // create a temporary heap
	for(int i = 1; i <= H->size; i++){ // loop through the heap
		insert(temp, H->heap[i]); // insert the heap values to the temporary heap
	}
	for(int i = H->size; i >= 1; i--){ // loop through the heap
		arr[i] = deleteM(temp); // delete the heap values to the temporary heap and store them in the array
	}
	return arr; // return the sorted array
}

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
				// printf("Removed root: %d\n", result);
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
			// uncomment this for postlab
			case '~':
				printf("The sorted version of the heap:\n");
				sorted = heapSort(H);
				for(key=1; key <= H->size; key++)
					printf("%4d", sorted[key]);
				printf("\n");
				free(sorted);
				break;
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