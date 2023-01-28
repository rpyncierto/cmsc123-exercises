#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <stdbool.h>

//Implement your functions here

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

void insertEdge(GRAPH *G, int u, int v, int w) {
	G->matrix[u][v] = w;
}

int *createVisited(GRAPH *G) {
 int *visited = (int*)malloc(sizeof(int)*G->num_vertices);
 for(int i= 0; i< G->num_vertices; i++) {
 	visited[i] = false;
 }
 return visited;
}

int *createDistance(GRAPH *G) {
	int *distance = (int*)malloc(sizeof(int)*G->num_vertices);
 for(int i= 0; i< G->num_vertices; i++) {
 	distance[i] = 99999;
 }
 return distance;
}

int *createParent(GRAPH *G) {
	int *parent = (int*)malloc(sizeof(int)*G->num_vertices);
 	for(int i= 0; i< G->num_vertices; i++) {
 		parent[i] = -1;
 }
 return parent;
}

void dijkstra(GRAPH *G, int source, int target) {
	int * visited = createVisited(G);
	int * distance = createDistance(G);
	int * parent = createParent(G);
	
	distance[source] = 0;
	
	// find u, u must not be visited, distance must not be 999 and must be the minimum
	int u;
	int min = 99999;
	while (true) {
		for(int i=0; i<G->num_vertices; i++) {
			if(!visited[i] && distance[i] != 999) {
				if(distance[i] < min) {
					min = distance[i];
					u = i;
				}
			}
		}
		// printf("%d", min);
		// printf("%d", u);
		// printf("finish");
		if (min == 99999) {
			break;SS
		}
		// printf("finish");
		visited[u] = true;
		for(int j = G->num_vertices; j>0; j++) {
			if(G->matrix[u][j] != 0 && !visited[j]) {
				int alt_distance = distance[u] + G->matrix[u][j];
				if (alt_distance <= distance[j]) {
					distance[j] = alt_distance;
					parent[j] = u;
				}
			}
		}
	}

	
	// printf("%d ", target);
	/*	
	while (parent[target] != -1) {
		printf("%d ", parent[target]);
	}
	*/
	
	// printf("PATH FROM %d to %d: ", source, target);
	// printf("DISTANCE FROM %d to %d: ", source, target);
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
	int vertices, lines, u, v, w, source, target;

	scanf("%d", &vertices);
	GRAPH *G = createGraph(vertices);

	while(1) {
		scanf(" %c", &command);

		switch(command) {
			case '+':
				scanf(" %d %d %d", &u, &v, &w);
				insertEdge(G, u-1, v-1, w); //there's a -1 since we use 0-indexing in the arrays
				printf("Successfully inserted edge %d %d\n", u, v);
				break;
			case '#':
				scanf(" %d %d", &source, &target);
				dijkstra(G, source-1, target-1);
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
