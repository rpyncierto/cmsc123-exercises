#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "graph.h"

//Implement your functions here

LIST* createStack() { // create a new stack // working finally
    LIST* temp = (LIST*)malloc(sizeof(LIST)); // allocate memory
    temp->head = NULL; // initialize head to NULL
    return temp;
}

int isEmpty(LIST *L) { // check if stack is empty // working finally
    if (L->head == NULL) { 
        return 1;
    } else {
        return 0;
    }
}

void push(LIST *L, NODE* node) { // add to head // working finally
    if (isEmpty(L)) {
        L->head = node;
    } else {
        node->next = L->head;
        L->head = node;
    }
}

NODE* createNode(int data) { // create a new node // working finally
    NODE* temp = (NODE*)malloc(sizeof(NODE)); // allocate memory
    temp->value = data; // initialize node with value 'data'
    temp->next = NULL; // initialize node's next pointer to NULL
    return temp;
}

int pop(LIST *L) { // remove from head of stack // working finally
    NODE* temp = L->head; 
    L->head = L->head->next; // move head to next node
    int value = temp->value; // store value of node to be removed
    free(temp); // free memory
    return value;
}


GRAPH *createGraph(int vertices) {
	GRAPH *G = (GRAPH *)malloc(sizeof(GRAPH));
	G->num_vertices = vertices;
	G->matrix = (int **)malloc(sizeof(int*)*vertices);
	for(int i = 0; i<vertices; i++) {
		G->matrix[i] = (int *)malloc(sizeof(int)*vertices);
	}
	for(int j = 0; j<vertices; j++) {
		for (int k = 0; k<vertices; k++) {
			G->matrix[j][k] = 0;
		}
	}
	return G;
	
}

void insertEdge(GRAPH *G, int u, int v) {
	G->matrix[u][v] = G->matrix[v][u] = 1;
}

int *createVisited(GRAPH *G) {
 int *visited = (int*)malloc(sizeof(int)*G->num_vertices);
 for(int i= 0; i< G->num_vertices; i++) {
 	visited[i] = 0;
 }
 return visited;
}

void dfs(GRAPH *G, int start) {
	LIST* stack = createStack();
	int * visited = createVisited(G);
	push(stack, createNode(start));
	while(!isEmpty(stack)) {
		int u = pop(stack);
		if(!visited[u]) {
			visited[u] = 1;
			printf("%d ", u+1);
			for(int i = G->num_vertices; i>0; i--) {
				if(G->matrix[u][i] == 1) {
					push(stack, createNode(i));
				}
			}	
		}
	}
}

void printMatrix(GRAPH *G) {
	for(int j = 0; j<G->num_vertices; j++) {
		for (int k = 0; k<G->num_vertices; k++) {
			printf("%d\t",G->matrix[j][k]);
		}
		printf("\n");
	}
}

void freeMatrix(GRAPH *G) {
	for(int i = 0; i<G->num_vertices; i++) {
		free(G->matrix[i]);
	}
	free(G->matrix);
}


int main() {
	char command;
	int vertices, lines, u, v;

	scanf("%d", &vertices);
	GRAPH *G = createGraph(vertices);

	while(1) {
		scanf(" %c", &command);

		switch(command) {
			case '+':
				scanf(" %d %d", &u, &v);
				insertEdge(G, u-1, v-1); //there's a -1 since we use 0-indexing in the arrays
				printf("Successfully inserted edge %d %d\n", u, v);
				break;
			case '#':
				printf("\nDFS: ");
				dfs(G, 0); //0 is the initial value since we use 0-indexing (it still represents vertex 1)
				printf("\n");
				break;
			case 'p':
				printf("\nADJACENCY MATRIX: \n");
				printMatrix(G);
				break;
			case 'Q':
				freeMatrix(G);
				free(G);
				return 0;
			default:
				printf("Unknown command: %c\n", command);
		}
	}
}
