#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define N 100000
struct ListNode {
    int value;
    struct ListNode *next;
};
typedef struct ListNode node;
struct List {
    node *head;
    node *tail;
};
typedef struct List list;

list L[N + 1];
int ans[4 * N][2];
int ans_id = 0;

void push(int i, int x){
    node *newNode = (node *)malloc(sizeof(node));
    newNode->value = x;
    if (L[i].head == NULL){
        L[i].head = L[i].tail = newNode;
        newNode->next = NULL;
    }else{
        L[i].tail->next = newNode;
        L[i].tail = newNode;
        newNode->next = NULL;
    }
}
int pop(int i){
    node *tmp = L[i].head;
    if (L[i].head->next == NULL)
        L[i].head = L[i].tail = NULL;
    else
        L[i].head = L[i].head->next;   
    int temp = tmp->value;
    free(tmp);
    return temp;
}
bool popable(int i){
    if (L[i].head == NULL)
        return false;
    int k = L[i].head->value;
    return L[k].head->value == i;
}
void find(int i){
    if (!popable(i))
        return;
    int j = L[i].head->value;
    ans[ans_id][0] = pop(i);
    ans[ans_id][1] = pop(j);
    ans_id++;
    find(i);
    find(j);
}

int main(){
    int n;
    scanf("%d", &n);
    int numTotal = 0;
    /* data to list */
    for (int i = 1; i <= n; i++){
        L[i].head = NULL;
        L[i].tail = NULL;
        int num;
        scanf("%d", &num);
        numTotal += num;
        for (int j = 0; j < num; j++){
            int x;
            scanf("%d", &x);
            push(i, x);
        }
    }
    /*  iterate to find pair can be popped */
    for (int i = 1; i <= n; i++){
        if (popable(i)){
            int j = L[i].head->value;
            ans[ans_id][0] = pop(i);
            ans[ans_id][1] = pop(j);
            ans_id++;
            find(i);
            find(j);
        }
    }
    if (ans_id != numTotal / 2)
        printf("No\n");
    else{
        printf("Yes\n");
        for (int i = 0; i < ans_id; i++)
            printf("%d %d\n", ans[i][0], ans[i][1]);
    }

    system("pause");
    return 0;
}