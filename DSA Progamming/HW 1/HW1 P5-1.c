#include <stdio.h>
#include <stdlib.h>


struct StackNode{
    int data;
    struct StackNode *next;
};
typedef struct StackNode StackNode;

void initialize(StackNode **topPtr){
    *topPtr = NULL;
    return;
}

void push(StackNode **topPtr, int value){
    StackNode *tmp;
    tmp = (StackNode*)malloc(sizeof(StackNode));
    tmp -> data = value;
    tmp -> next = *topPtr;
    *topPtr = tmp;
    return;
}

int pop(StackNode **topPtr){
    StackNode *tmp;
    int n;
    tmp = *topPtr;
    n = tmp->data;
    *topPtr = (*topPtr)->next;
    free(tmp);
    return n;
}

int isempty(StackNode *top){
    return top==NULL;
}

void display(StackNode *head){
    while (head != NULL){
        if (head->next != NULL)
            printf("%d ", head->data);
        else
            printf("%d", head->data);
        head = head->next;
    }
    printf("\n");
    return;
}

void enter(StackNode **stack_r, int l, int *size){
    push(stack_r, l);
    *size += 1;
    return;
}

void leave(StackNode **stack_r, int *size){
    if (!isempty(*stack_r)){
        pop(stack_r);
        *size -= 1;
    }
    return;
}

void migrate(StackNode **stack_a, StackNode **stack_b, int *size_a, int *size_b){
    /* migrate from less to more */
    if (size_b == 0){
        StackNode *temp = *stack_a;
        *stack_b = *stack_b;
        *stack_b = temp;
    }else{
        while (!isempty(*stack_a))
            push(stack_b, pop(stack_a));
    }
    *size_b += *size_a;
    *size_a = 0;
}

int main(){
    int k, n;
    scanf("%d%d", &k, &n);
    /*create k stacks to stimulate rails */
    StackNode *stacks[k];
    int size[k];
    for (int i = 0; i < k; i++){
        initialize(&(stacks[i]));
        size[i] = 0;
    }
    /*input of n line of logs */
    int a, b;
    for (int i = 0; i < n; i++){
        char operation[7];
        scanf("%s", operation);
        if (operation[0] == 'e'){
            scanf("%d%d", &a, &b);  /* r, l */
            enter(&(stacks[a]), b, &(size[a]));
        }else if (operation[0] == 'l'){
            scanf("%d", &a);  /* r */
            leave(&(stacks[a]), &(size[a]));
        }else{
            scanf("%d%d", &a, &b);
            migrate(&(stacks[a]), &(stacks[b]), &(size[a]), &(size[b]));
        }
    }
    /* print the data in the stacks by another stack */
    StackNode *output;
    int index = 0;
    do {
        initialize(&output);
        while (!isempty(stacks[index]))
            push(&(output), pop(&(stacks[index])));
        display(output);
        index++;
    } while (index < k);

    system("pause");
    return 0;
}