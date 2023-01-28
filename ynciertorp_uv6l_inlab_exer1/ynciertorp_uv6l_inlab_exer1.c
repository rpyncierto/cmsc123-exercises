/*
Reymond P. Yncierto
CMSC 123 UV-6l

This program checks if the parentheses in an expression are balanced or not.
*/

#include "isBalanced.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void printStack(LIST *L) { // working finally
    if (isEmpty(L)) { // check if list/stack is empty
        printf("*empty*\n");
    } else { // list !empty
        NODE* temp = L->head;
        while (temp != NULL) { // iterate the list/stack
            printf("%c", temp->value);
            temp = temp->next; // move to next node
        }
        printf("\n");
    }
}


NODE* createNode(int data) { // create a new node // working finally
    NODE* temp = (NODE*)malloc(sizeof(NODE)); // allocate memory
    temp->value = data; // initialize node with value 'data'
    temp->next = NULL; // initialize node's next pointer to NULL
    return temp;
}


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


int pop(LIST *L) { // remove from head of stack // working finally
    NODE* temp = L->head; 
    L->head = L->head->next; // move head to next node
    int value = temp->value; // store value of node to be removed
    free(temp); // free memory
    return value;
}


int isBalanced(char *expr) { // working finally
    LIST* stack = createStack(); // create a new stack
    for (int i = 0; i < strlen(expr); i++) { // iterate through the stack/list
        if (expr[i] == '(') { // if char is '('
            push(stack, createNode(expr[i])); // push to stack
        } else if (expr[i] == ')') { // if char is ')'
            if (isEmpty(stack)) { // if stack is empty
                if (i==0) { // if index is 0, meaning this is the first character in the expression, i==0 since if a pair of () is popped, the stack will be empty therefore it will be read as the first character in the expression without this condition
                    printf("The parentheses are not well-formed.\n");
                    return 0;
                } else {
                    push(stack, createNode(expr[i])); // push to stack
                }
            } else {
                pop(stack); // pop from stack
            }
        }
    }
    printStack(stack); // print the stack
    if (isEmpty(stack)) { // if stack is empty or not
        return 1; 
    } else { 
        return 0; 
    }
}


int main() { // main
    char expr[100];
    printf("Enter an expression: ");
    scanf("%s", expr);
    if (isBalanced(expr)) {
        printf("The parentheses are balanced.\n");
    } else {
        printf("The parentheses are NOT balanced.\n");
    }
    return 0;
}