#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#define LINE 100000

struct LinkNode{
    char operation[5];
    int target;
    int target_line;
    struct LinkNode *next;
};
typedef struct LinkNode Linknode;
struct Node{
    int value;
    int line;
    struct Node *next;
    struct Node *prev;
};
typedef struct Node Node;
struct Queue{
    Node *head;
    Node *last;
    int *heap;
    int size;
    int esize;
};
typedef struct Queue Queue;
/* function of heap */
int parent(int index){
    index = index + 1;
    return (index / 2) - 1;
}
int left(int index){
    index = index + 1;
    return (2 * index) - 1;
}
int right(int index){
    index = index + 1;
    return (2 * index + 1) - 1;
}
void maxHeapify(Queue *line, int index){
    int l = left(index);
    int r = right(index);
    int largest;
    int heapSize = line->size;
    if ((l < heapSize) && ((line)->heap[l] >= (line)->heap[index]))
        largest = l;
    else
        largest = index;
    if ((r < heapSize) && ((line)->heap[r] >= (line)->heap[largest]))
        largest = r;
    if (largest != index){
        int temp = (line)->heap[index];
        (line)->heap[index] = (line)->heap[largest];
        (line)->heap[largest] = temp;
        maxHeapify(line, largest);
    }
    return;
}
/* function of queue */
void HeapInsert(Queue *line, int key){
    line->size++;
    line->heap = (int *)realloc(line->heap, line->size * sizeof(int));
    assert(line->heap != NULL);
    int index = line->size - 1;
    line->heap[index] = key;
    while ((index > 0) && (line->heap[parent(index)] < line->heap[index])){
        int temp = line->heap[parent(index)];
        line->heap[parent(index)] = line->heap[index];
        line->heap[index] = temp;
        index = parent(index);
    }
    return;
}
int extractMax(Queue *line){
    assert(line->size != 0);
    int max = line->heap[0];
    line->heap[0] = line->heap[line->size - 1];
    line->size--;
    maxHeapify(line, 0);
    return max;
}
int Max(Queue *line, bool enqueued[]){
    while ((line->size > 1) && (!enqueued[line->heap[0]]))
        extractMax(line);
    return line->heap[0];
}
void init(Queue *line){
    line->head = NULL;
    line->last = NULL;
    line->size = 0;
    line->esize = 0;
    line->heap = (int *)malloc(line->size * sizeof(int));
    return;
}
void push(Queue *line, int line_id, int n, Node *address[]){
    Node *last = line->last;
    Node *newnode = (Node *)malloc(sizeof(Node));
    address[n] = newnode;
    newnode->line = line_id;
    line->esize++;
    if (line->head  == NULL){
        newnode->prev = last;
        newnode->next = NULL;
        line->head = newnode;
        line->last = newnode;
        newnode->value = n;
    }else{
        last->next = newnode;
        newnode->prev = last;
        newnode->next = NULL;
        line->last = newnode;
        newnode->value = n;
    }
    HeapInsert(line, n);
    return;
}
void merge(int b, int a, Node *address[], Queue *lines[], bool enqueued[]){
    /* swap close and open line address if open is smaller */
    Queue *close = lines[a];
    Queue *open = lines[b];
    if (open->esize >= close->esize){
        if (close->head == NULL)  // close->esize = 0
            return;      
        else{
            Node *tail = open->last;
            Node *start = close->head;
            tail->next = start;
            start->prev = tail;
            open->last = close->last;
            close->head = close->last = NULL;
        }
    }else{
        if (open->head == NULL){  // open->esize = 0
            lines[b] = close;
            return;
        }else{
            Node *tail = open->last;
            Node *start = close->head;
            tail->next = start;
            start->prev = tail;
            Queue *temp = close;
            close = open;
            open = temp;
            open->head = close->head;
            int tem = a;
            a = b;
            b = tem;
            lines[a] = open;
        }
    }
    open->esize += close->esize;
    /* merge heap */
    for (int i = 0; i < close->size; i++){
        if (enqueued[close->heap[i]]){
            HeapInsert(open, close->heap[i]);
            Node *temp = address[close->heap[i]];
            temp->line = b;
        }
    }
    free(close->heap);
    return;
}
bool Verify(Queue *line, Node *node, int key, bool enqueued[]){
    if ((node->prev == NULL) || (node->next == NULL)){
        enqueued[key] = false;
        return true;
    }else if (node->value == Max(line, enqueued)){
        extractMax(line);
        return true;
    }else
        return false;
}
void Pop(Queue *line, Node *node){
    if ((node->prev != NULL) && (node->next != NULL)){
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }else if (node->prev != NULL){
        line->last = node->prev;
        node->prev->next = NULL;
    }else if (node->next != NULL){
        line->head = node->next;
        node->next->prev = NULL;
    }else
        line->last = line->head = NULL;
    free(node);
    line->esize--;
    return;
}

int main(){
    int t;
    scanf("%d", &t);
    /* create nodes */
    Linknode *head = (Linknode *)malloc(sizeof(Linknode));
    Linknode *ptr = head;
    for (int i = 0; i < 2 * LINE; i++){
        Linknode *newnode = (Linknode *)malloc(sizeof(Linknode));
        ptr->next = newnode;
        ptr = ptr->next;
    }
    /* test case */
    for (int i = 0; i < t; i++){
        int n, o, l;  /* number, operation, line */
        scanf("%d%d%d", &n, &o, &l);
        ptr = head;
        for (int i = 0; i < o; i ++){
            scanf("%s", ptr->operation);
            scanf("%d%d", &ptr->target, &ptr->target_line);
            ptr = ptr->next;
        }
        /* create lines */
        Queue *lines[l];
        for (int i = 0; i < l; i++){
            lines[i] = (Queue *)malloc(sizeof(Queue));
            init(lines[i]);
        }
        /* chcek the order of key */
        bool enqueued[n + 1];
        for (int i = 1; i < n + 1; i++)
            enqueued[i] = false;
        ptr = head;
        Node *address[n + 1];
        bool possible = true;
        for (int i = 0; i < n; i++){
            int key;
            scanf("%d", &key);
            if (!possible)
                continue;
            while (!enqueued[key]){
                if (ptr->operation[0] == 'p'){
                    Queue *line = lines[ptr->target_line];
                    int value = ptr->target;
                    push(line, ptr->target_line, value, address);
                    enqueued[value] = true;
                }else{
                    merge(ptr->target_line, ptr->target, address, lines, enqueued);
                }
                ptr = ptr->next;
            }
            Queue *line = lines[address[key]->line];
            possible = Verify(line, address[key], key, enqueued);
            if (possible)
                Pop(line, address[key]);
        }
        if (possible){
            char toprint[9] = "possible";
            printf("%s\n", toprint);
        }else{
            char toprint[11] = "impossible";
            printf("%s\n", toprint);
        }
    }
    return 0;
}