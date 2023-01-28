#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

//Implement your functions here
GRAPH *createGraph(int vertices) {
	GRAPH *G = (GRAPH *)malloc(sizeof(GRAPH)); //allocate memory for graph
	G->num_vertices = vertices; // set number of vertices
	G->matrix = (int **)malloc(sizeof(int*)*vertices); // allocate memory for matrix
	for(int i = 0; i<vertices; i++) {
		G->matrix[i] = (int *)malloc(sizeof(int)*vertices); // allocate memory for each row
	}
	for(int j = 0; j<vertices; j++) {
		for (int k = 0; k<vertices; k++) {
			G->matrix[j][k] = 0; // initialize all values to 0
		}
	}
	return G;
}

void insertEdge(GRAPH *G, int u, int v, int w) {
	G->matrix[u][v] = w; // inserts edge and sets weight to it
}

int *createVisited(GRAPH *G) {
	int *visited = (int *)malloc(sizeof(int) * G->num_vertices); // allocate memory for visited array
	for (int i = 0; i < G->num_vertices; i++) { 
		visited[i] = 0; // initialize all values to 0
	}
	return visited;
}

int *createDistance(GRAPH *G) {
	int *distance = (int *)malloc(sizeof(int) * G->num_vertices); // allocate memory for distance array
	for (int i = 0; i < G->num_vertices; i++) {
		distance[i] = 99999; // initialize all values to 99999
	}
	return distance;
}

int *createParent(GRAPH *G) {
	int *parent = (int *)malloc(sizeof(int) * G->num_vertices); // allocate memory for parent array
	for (int i = 0; i < G->num_vertices; i++) {
		parent[i] = -1; // initialize all values to -1
	}
	return parent;
}

void dijkstra(GRAPH *G, int source, int target) {
	int *visited = createVisited(G); // create visited array
	int *distance = createDistance(G); // create distance array
	int *parent = createParent(G); // create parent array

	distance[source] = 0; // set distance of source vertex to 0

	while (1) {
		int min = 99999; 
		int u = -1;
		for (int i = 0; i < G->num_vertices; i++) { // get vertex with minimum distance and is not visited
			if (visited[i] == 0 && distance[i] < min) {
				min = distance[i];
				u = i;
			}
		}
		if (u == -1) { // if no vertex is found, break
			break;
		}
		visited[u] = 1; // set vertex u to visited
		for (int v = 0; v < G->num_vertices; v++) { // update distance of all vertices adjacent to u if they are not visited and the distance[v] > distance[u] + weight(u,v) (alternate distance)
			if (G->matrix[u][v] != 0 && visited[v] == 0) {
				if (distance[v] > distance[u] + G->matrix[u][v]) {
					distance[v] = distance[u] + G->matrix[u][v];
					parent[v] = u;
				}
			}
		}
	}

	printf("\nPATH FROM %d TO %d: ", source+1, target+1);
	if (distance[target] == 99999) { // if distance of target is 99999, there is no path thus it is impossible from source to reach target
		printf("IMPOSSIBLE!");
	} else if (distance[target] == 0) { // if distance of target is 0, that means the source and target are the same
		printf("%d", source+1);
	} else {
		int *path = (int *)malloc(sizeof(int) * G->num_vertices); // allocate memory for path array
		int i = 0;
		int v = target;
		while (v != source) { // get path from target to source
			path[i] = v;
			v = parent[v];
			i++;
		}
		path[i] = source; // add source to path
		for (int j = i; j >= 0; j--) { // print path
			printf("%d ", path[j]+1);
		}
	}

	printf("\nDISTANCE FROM %d TO %d: ", source+1, target+1);
	if (distance[target] == 99999) { // if distance of target is 99999, there is no path to begin with
		printf("-1");
	} else {
		printf("%d", distance[target]); // print distance
	}
	printf("\n");
}

void printMatrix(GRAPH *G) {
	for(int j = 0; j<G->num_vertices; j++) { 
		for (int k = 0; k<G->num_vertices; k++) {
			printf("%d\t",G->matrix[j][k]); // print matrix
		}
		printf("\n");
	}
}

void freeMatrix(GRAPH *G) {
	for(int i = 0; i<G->num_vertices; i++) {
		free(G->matrix[i]); // free each row
	}
	free(G->matrix); // free matrix
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