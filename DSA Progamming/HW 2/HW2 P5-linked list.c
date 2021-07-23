#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "generator.h"

struct Node{
    int p;
    int l;  /* larger */
    int s;  /* smaller */
    struct Node *next;
};
typedef struct Node node;

void push(node **head, int p, int large, int small){
    node *new_node = (node *)malloc(sizeof(node));
    new_node->p = p;
    new_node->l = large;
    new_node->s = small;
    new_node->next = *head;
    (*head) = new_node;
    return;
}
void pushS(node **last, int small, int p){
	node *new_node = (node *)malloc(sizeof(node));
	new_node->s = small;
	new_node->p = p;
	(*last)->next = new_node;
	new_node->next = NULL;
	(*last) = new_node;
	return;
}

node *MergeSortedbyP(node *list1, node *list2){ 
	node* result = NULL; 
	if (list1 == NULL) 
		return (list2); 
	else if (list2 == NULL) 
		return (list1); 
	if (list1->p < list2->p) { 
		result = list1; 
		result->next = MergeSortedbyP(list1->next, list2); 
	}else if (list1->p > list2->p){ 
		result = list2; 
		result->next = MergeSortedbyP(list1, list2->next); 
	}else if (list1->l > list2->l){
		result = list1; 
		result->next = MergeSortedbyP(list1->next, list2); 
	}else{
		result = list2; 
		result->next = MergeSortedbyP(list1, list2->next); 
	}
	return result; 
}
node *MergeSortedbyS(node *list1, node *list2){ 
	node* result = NULL; 
	if (list1 == NULL) 
		return (list2); 
	else if (list2 == NULL) 
		return (list1); 
	if (list1->s < list2->s) { 
		result = list1; 
		result->next = MergeSortedbyS(list1->next, list2); 
	}else{ 
		result = list2; 
		result->next = MergeSortedbyS(list1, list2->next); 
	} 
	return result; 
}
node *MergeSortedbyL(node *list1, node *list2){ 
	node* result = NULL; 
	if (list1 == NULL) 
		return (list2); 
	else if (list2 == NULL) 
		return (list1); 
	if (list1->l < list2->l) { 
		result = list1; 
		result->next = MergeSortedbyL(list1->next, list2); 
	}else{ 
		result = list2; 
		result->next = MergeSortedbyL(list1, list2->next); 
	} 
	return result; 
}
void SplitList(node *source, node **front, node **back) { 
	node *ptr1; 
	node *ptr2; 
	ptr2 = source; 
	ptr1 = source->next; 
	while (ptr1 != NULL) { 
		ptr1 = ptr1->next; 
		if (ptr1 != NULL) { 
			ptr2 = ptr2->next; 
			ptr1 = ptr1->next; 
		} 
	}
	*front = source; 
	*back = ptr2->next; 
	ptr2->next = NULL;
    return;
} 
void MergeSortbyP(node **thead) { 
	node *head = *thead; 
	if ((head == NULL) || (head->next == NULL)) 
		return; 
    node *ptr1;
	node *ptr2;
	SplitList(head, &ptr1, &ptr2); 
	MergeSortbyP(&ptr1); 
	MergeSortbyP(&ptr2); 
	*thead = MergeSortedbyP(ptr1, ptr2);
    return;
}
long long ans;
long long c;

void counting(node *list1, node *list2){
	if (list1 == NULL)
		return;
	if ((list2 == NULL) || (list1->l < list2->s)){
		ans += c;
		counting(list1->next, list2);
	}else{
		c++;
		counting(list1, list2->next);
	}
	return;
}

void Mergecount(node **thead_l, node **thead_s) { 
	node *head_l = *thead_l;
	node *head_s = *thead_s;
	if ((head_l == NULL) || (head_l->next == NULL)) 
		return; 
    node *l_1;
	node *l_2;
	SplitList(head_l, &l_1, &l_2);
    node *s_1;
	node *s_2;	
	SplitList(head_s, &s_1, &s_2);
	Mergecount(&l_1, &s_1); 
	Mergecount(&l_2, &s_2);
	c = 0;
	counting(l_1, s_2);
	*thead_l = MergeSortedbyL(l_1, l_2);
	*thead_s = MergeSortedbyS(s_1, s_2);
    return;
}

int main(){
    generator.init();
    int t = generator.getT();
    while (t--) {
        int n, *p, *q, *r;
        generator.getData(&n, &p, &q, &r);
        node *list_p = NULL;
		for (int i = 0; i < n; i++){
            int large = r[i];
            int small = q[i];
            if (q[i] > r[i]){
                large = q[i];
                small = r[i];
            }
            push(&list_p ,p[i], large, small);
		}
        MergeSortbyP(&list_p);
		node *ptr = list_p;
		node *new_node = (node *)malloc(sizeof(node));
		new_node->p = ptr->p;
		new_node->s = ptr->s;
		new_node->next = NULL;
		ptr = ptr->next;
		node *list_s = new_node;
		node *last = list_s;
		while (ptr != NULL){
			pushS(&last, ptr->s, ptr->p);
			ptr = ptr->next;
		}
		node *list_l = list_p;
		ans = 0;
		Mergecount(&list_l, &list_s);
		printf("%lld\n", ans);
	}
    system("pause");
    return 0;
}