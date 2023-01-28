/*
Reymond P. Yncierto
CMSC 123 UV-6l

This program is a queue implementation.
*/

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

void printQueue(LIST *L) { // working finally, 
    printf("Queue: ");
    if (isEmpty(L)) { // queue is empty
        printf("*empty*\n");
    } else { // otherwise, print the queue
        NODE *present = L->head;
        while (present != NULL) { // iterate the queue
            printf("%d ", present->value);
            present = present->next;
        } printf("\n");
    } printf("\n");
}

NODE* createNode(int data) { 
    NODE *newN = (NODE*)malloc(sizeof(NODE)); // allocate memory
    newN->value = data; // initialize node with value 'data'
    newN->next = NULL; // initialize node's next pointer to NULL
    return newN;
}

LIST* createQueue() {
    LIST *newL = (LIST*)malloc(sizeof(LIST)); // allocate memory
    newL->head = NULL; // initialize head and tail to NULL
    newL->tail = NULL;
    return newL;
}

int isEmpty(LIST *L) { 
    if (L->head == NULL) { // queue is empty
        return 1;
    } else {
        return 0;
    }
}

void enqueue(LIST *L, NODE *node) {
    if (isEmpty(L)) { 
        L->head = node; // if queue is empty, add node to head and tail
        L->tail = node; 
    } else {
        L->tail->next = node; // otherwise, add node to tail
        L->tail = node; 
    }
}

int dequeue(LIST *L) {
    if (isEmpty(L)) {
        return -1; // if queue is empty, return -1
    } else { 
        NODE *temp = L->head; // store head node
        int value = temp->value; // store value of head node
        L->head = L->head->next; // move head to next node
        free(temp); // free memory
        return value;
    }
}

int main() {
    LIST *L = createQueue(); // create a queue
    int choice;
    do {
        printf("Queue Implementation\n");
        printf("[1] Enqueue\n");
        printf("[2] Dequeue\n");
        printf("[3] Print\n");
        printf("[4] Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice) {
            case 1: { // enqueue
                int value;
                printf("Enter value: ");
                scanf("%d", &value);
                NODE *newNode = createNode(value); // create a node
                enqueue(L, newNode); // add node to queue
                printf("\n");
                break;
            }
            case 2: { // dequeue
                int value = dequeue(L);
                if (value == -1) { //underflow
                    printf("Queue is empty\n\n");
            } else {
                    printf("Dequeued value: %d\n", value);
                    printQueue(L);
            }
                break;
            }
            case 3: {
                printQueue(L); // print queue
                break;
            }
            case 4: {
                printf("Thank you for using the program!\n");
                return 0;
            }
            default: {
                printf("Invalid choice\n\n");
                continue;
            }
        }
    } while (choice != 4);
}