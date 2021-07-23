#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

struct StackNode{
	char data; 
	struct StackNode *next;  
};
typedef struct StackNode Stack_node;

bool stackEmpty(Stack_node *top){
    return (top == NULL);
}

void pushStack(Stack_node **topPtr, char c){
    Stack_node *new_node;
    new_node = (Stack_node *)malloc(sizeof(Stack_node));
    new_node->data = c;
    new_node->next = *topPtr;
    *topPtr = new_node;
}

char popStack(Stack_node **topPtr){
    assert(*topPtr != NULL);
    
    Stack_node *ptr = *topPtr;
    char pop_data = ptr->data;
    *topPtr = (*topPtr)->next;
    free(ptr);
    return (pop_data);
}

char topStack(Stack_node *top){
    return (top->data);
}

bool precendece(char topStack, char token){
    return (((topStack == '*') || (topStack == '/')) &&
            ((token == '+') || (token == '-')));
}

Stack_node *genNode(){
    Stack_node *node = (Stack_node *)malloc(sizeof(Stack_node));
    node->next = NULL;
    return (node);
}

void output(char token, Stack_node **rpn){
    Stack_node *new_node = genNode();
    (*rpn)->next = new_node;
    new_node->data = token;
    *rpn = new_node;
    return;
}

void printList(Stack_node *node){
    if (node == NULL){
        printf("\n");
        return;
    }
    printf("%c", node->data);
    printList(node->next);
}

int main(){
    /* turning input string into RPN string*/ 
    char token;
    Stack_node *head = genNode();
    head->data = '_';  /* initialize the linked list */
    Stack_node *rpn = head;
    Stack_node *top = NULL;
    while (scanf("%c", &token) != EOF){
        if (isdigit(token)){  /* if token is a number (or using ASCII) */
            output(token, &rpn);  /* output token */ 
        }else if (token == '(')  /* if token is a left parenthese */
            pushStack(&top, token);  /* push token */
        else if (token == ')'){  /* if token is a right parenthese */
            while (topStack(top) != '('){
                output(popStack(&top), &rpn);  /* pop and output token */
            }
            popStack(&top);  /* remove left parenthese */
        }
        else{  /* if token is an operator */
            if(!stackEmpty(top)){
                while (precendece(topStack(top), token)){
                    output(popStack(&top), &rpn);  /* pop and output stack.top */
                }
            }
            output('_', &rpn);  /* split the number and operator */
            pushStack(&top, token);  /* push token to stack */
        }
    }
    /* output left operator in stack */
    while(!stackEmpty(top)){
        output(popStack(&top), &rpn);
    }

    printList(head);

    system("pause");
    return 0;
}

