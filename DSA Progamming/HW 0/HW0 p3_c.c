#include <stdio.h>
#include <stdlib.h> // malloc / free
#include <memory.h> // memset
// Use typedef to define "struct node" as "node".
typedef struct node{
    int data;
    struct node *nxt;
} node;


node *alloc(int data , node *nxt ){
    node *tmp = (node *) malloc(sizeof(node));
    tmp ->data = data;
    tmp ->nxt = nxt;
    return tmp;
}
    

void destory(node *head){
    if (head != NULL){
        destory(head->nxt);
        // clean sensitive data.
        memset(head, 0, sizeof(node));
        free(head);
    }
}


int main(void){
    // create nodes [0, 1, 2, 4]
    node *head = alloc (0, alloc (1, alloc (2, alloc (4, NULL))));
    node *tmp = head;
    // print the nodes subsequently
    while (tmp != NULL ){
        printf("%d -> ", tmp->data ); // print the data in the node
        tmp = tmp->nxt;
    }
    printf("NULL");
    // free the nodes subsequently to avoid memory leak
    destory(head);

    system("pause");
    return 0;
}