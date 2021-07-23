#include <stdio.h>
#include <stdlib.h>


struct StackNode{
    int data;
    struct StackNode *next;
    struct StackNode *prev;
};
typedef struct StackNode StackNode;

void initialize(StackNode **head, StackNode **last){
    *head = NULL;
    *last = NULL;
    return;
}

int isempty(StackNode *head){
    return head==NULL;
}
void push(StackNode **head, StackNode **last, int value){
    StackNode *new_node = (StackNode *)malloc(sizeof(StackNode));
    if (isempty(*head))
        *last = new_node;
    else
        (*head)->prev = new_node;
    new_node->data = value;
    new_node->next = *head;
    new_node->prev = NULL;
    *head = new_node;
    return;
}

int pop(StackNode **head, StackNode **last){
    StackNode *tmp = *head;
    if ((*head)->next == NULL)
        *last = NULL;
    else
        (*head)->next->prev = NULL;
    int n = tmp->data;
    *head = (*head)->next;
    free(tmp);
    return n;
}

void pushReverse(StackNode **top, StackNode **bottom, int value){
    StackNode *new_node = (StackNode *)malloc(sizeof(StackNode));
    if (isempty(*top))
        *bottom = new_node;
    else
        (*top)->next = new_node;
    new_node->data = value;
    new_node->prev = *top;
    new_node->next = NULL;
    *top = new_node;
}

int popReverse(StackNode **top, StackNode **bottom){
    StackNode *tmp = *top;
    if ((*top)->prev == NULL)
        *bottom = NULL;
    else
        (*top)->prev->next = NULL;
    int n = tmp->data;
    *top = (*top)->prev;
    free(tmp);
    return n;
}

void display(StackNode *last){
    while (last != NULL){
        if (last->prev != NULL)
            printf("%d ", last->data);
        else
            printf("%d", last->data);
        last = last->prev;
    }
    printf("\n");
    return;
}

void enter(StackNode **head, StackNode **last, int l){
    push(head, last, l);
    return;
}

void enterReverse(StackNode **top, StackNode **bottom, int l){
    pushReverse(top, bottom, l);
    return;
}

void leave(StackNode **head, StackNode **last){
    if (!isempty(*head))
        pop(head, last);
    return;
}

void leaveReverse(StackNode **top, StackNode **bottom){
    if (!isempty(*top))
        popReverse(top, bottom);
    return;
}

void swap(StackNode **a, StackNode **b){
    StackNode *tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}


void migrate(StackNode **head_a, StackNode **head_b, 
            StackNode **last_a, StackNode **last_b,
            StackNode **top_a, StackNode **top_b,    
            StackNode **bottom_a, StackNode **bottom_b){
    if (isempty(*head_a))
        return;
    else if (isempty(*head_b)){
        swap(head_a, bottom_b);
        swap(last_a,top_b);
        swap(top_a, last_b);
        swap(bottom_a, head_b);
        return;
    }
    /* migrate normal stacks from a to b */
    (*top_a)->next = *head_b;
    (*head_b)->prev = *top_a;
    *head_b = *bottom_a;
    /* migrate from reversed stacks from a to b */
    (*top_b)->next = *head_a;
    (*head_a)->prev = *top_b;
    *top_b = *last_a;
    initialize(head_a, last_a);
    initialize(top_a, bottom_a);
    return;
}

int main(){
    int k, n;
    scanf("%d%d", &k, &n);
    /*create k stacks by doubly linked list to stimulate rails */
    StackNode *head[k];
    StackNode *last[k];
    StackNode *top[k];
    StackNode *bottom[k];
    for (int i = 0; i < k; i++){
        initialize(&(head[i]), &(last[i]));
        initialize(&(top[i]), &(bottom[i]));
    }
    /*input of n line of logs */
    int a, b;
    for (int i = 0; i < n; i++){
        char operation[7];
        scanf("%s", operation);
        if (operation[0] == 'e'){
            scanf("%d%d", &a, &b);  /* r, l */
            enter(&(head[a]), &(last[a]), b);
            enterReverse(&(top[a]), &(bottom[a]), b);
        }else if (operation[0] == 'l'){
            scanf("%d", &a);  /* r */
            leave(&(head[a]), &(last[a]));
            leaveReverse(&(top[a]), &(bottom[a]));
        }else{
            scanf("%d%d", &a, &b);
            migrate(&(head[a]), &(head[b]), &(last[a]), &(last[b]),
                    &(top[a]), &(top[b]), &(bottom[a]), &(bottom[b]));
        }
    }
    for (int index = 0; index < k; index++)
        display(last[index]);
    
    return 0;
}