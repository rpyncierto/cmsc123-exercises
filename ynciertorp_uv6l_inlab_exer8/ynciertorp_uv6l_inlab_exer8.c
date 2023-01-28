/*
	Name:
	Section:
	Description: 
*/

#include "hashtable.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void destroy(HASH_TABLE * H) {
	for (int i = 0; i <= H->tableSize; i++) {
		if (H->list[i] != NULL) {
			free(H->list[i]);
		}
		H->list[i] = NULL;
		// printf("%s", H->list[i]);
	}
	H->size = 0;
}

HASH_TABLE * createHashTable(uint tableSize) {
	HASH_TABLE * H = (HASH_TABLE*)malloc(sizeof(HASH_TABLE));
	H->size = 0;
	H->tableSize = tableSize;
	H->list = (char**)malloc(sizeof(char*)*tableSize);
	for (int i = 0; i <= H->tableSize; i++) {
		H->list[i] = NULL;
		// printf("%s", H->list[i]);
	}
	return H;
}

uint isEmpty(HASH_TABLE * H) {
	if (H->size == 0) {
		return 1;
	}
	return 0;
}

uint isFull(HASH_TABLE * H) {
	if (H->size == H->tableSize) {
		return 1;
	}
	return 0;
}

int h1 (STRING key) {
	// printf("%ld", strlen(key));
	int sum = 0;
	for(int i=0; i<strlen(key); i++) {
		// printf("%c", key[i]);
		sum = sum + (int)key[i];
	}
	// printf("%d", sum);
	return sum;
}
	
int h2 (int sum, STRING key, HASH_TABLE * H) {
	int index = 23 - sum % strlen(key);
	return index;
}

void put(HASH_TABLE * H, STRING key, STRING data) {
	int i = 0;
	int index = (h1(key) + h2(h1(key), key, H) * i) % H->tableSize;
	while (H->list[index] != NULL) {
		i++;
		index = (h1(key) + h2(h1(key), key, H) * i) % H->tableSize;
	}
	H->list[index] = (char*) malloc(sizeof(char) * strlen(data));
	strcpy(H->list[index], data);
	H->size++;
}

STRING find(HASH_TABLE * H, STRING key, STRING data) {
	int i = 0;
	int index = (h1(key) + h2(h1(key), key, H) * i) % H->tableSize;
	// if (strcmp(h1(H->list[index]), h1(key)) == 0) {
	//	return H->list[index]
	// }
	while (H->list[index] != NULL) {
		if(strcmp(H->list[index], data) == 0) {
			return H->list[index];
		}
		i++;
		index = (h1(key) + h2(h1(key), key, H) * i) % H->tableSize;
	}
	return NULL;
}

STRING erase(HASH_TABLE * H, STRING key, STRING data) {
	int i = 0;
	int index = (h1(key) + h2(h1(key), key, H) * i) % H->tableSize;
	while (H->list[index] != NULL) {
		if(strcmp(H->list[index], data) == 0) {
			free(H->list[index]);
			H->list[index] = NULL;
			return data;
		}
		i++;
		index = (h1(key) + h2(h1(key), key, H) * i) % H->tableSize;
	}
	return NULL;
}


//Function that prints the data of the hash table
void printTable(HASH_TABLE * H){
	if(isEmpty(H)) {
		printf("*empty\n");
		return;
	}

	for(int index=0; index<H->tableSize; index++){
		printf("Cell#%d: ", index);
		if(H->list[index]){
			printf("%s\n", H->list[index]);
		}else{
			printf("*empty*\n");
		}
	}
}


int main(){

	char command;
	STRING key;
	STRING data;
	STRING result;

	uint tsize;
	HASH_TABLE * H;
	
	// get table size then maxsize
	scanf("%d\n", &tsize); 
	H = createHashTable(tsize);
	// assume max key size is 20
	key = (STRING)malloc(sizeof(char)*20);
	key[0] = '\0';
	// assume max data size is 100
	data = (STRING)malloc(sizeof(char)*100);
	data[0] = '\0';

	while(1){
		scanf(" %c", &command);

		switch(command){
			case '+':
				scanf(" k:%s d:%s", key, data);
				printf("Inserting data %s with key %s\n", data, key);
				put(H, key, data);
				break;
			case '-':
				scanf(" k:%s d:%s", key, data);
				printf("Deleting data with key %s\n", key);
				result = erase(H, key, data); 
				// result is unused. print if u want
				break;
			case '?':
				scanf(" k:%s d:%s", key, data);
				printf("Searching data with key: %s. Location: %p\n", key, find(H, key, data));
				// (nil) means NULL pointer
				break;
			case 'p':
				printf("Hash Table: \n");
				printTable(H);
				printf("\n");
				break;
			case 'E':
				printf("Hash table %s empty.\n", isEmpty(H)?"is":"is not");
				break;
			case 'F':
				printf("Hash table %s full.\n", isFull(H)?"is":"is not");
				break;
			case 'C':
				printf("Deleting all contents.\n");
				destroy(H);
				break;
			case 'Q':
				free(key); free(data);
				destroy(H); // ensure deletion
				free(H->list);
				free(H);
				return 0;
			default:
				printf("Unknown command: %c\n", command);
		}
	}
	
	return 0;
}
