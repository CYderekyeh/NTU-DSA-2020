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
    struct Queue *firstline;
    Node *head;
    Node *last;
    int *heap;
    int size;
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
void Mergeheap(Queue *close, Queue *open){
    if (open->size < close->size){
        int *temp = open->heap;
        open->heap = close->heap;
        close->heap = temp;
        int tem = open->size;
        open->size = close->size;
        close->size = tem;
    }
    for (int i = 0; i < close->size; i++)
        HeapInsert(open, close->heap[i]);
    free(close->heap);
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
    line->firstline = line;
    line->head = NULL;
    line->last = NULL;
    line->size = 0;
    line->heap = (int *)malloc(line->size * sizeof(int));
    return;
}
void push(Queue *line, int line_id, int n, Node *address[]){
    Node *last = line->last;
    Node *newnode = (Node *)malloc(sizeof(Node));
    address[n] = newnode;
    newnode->line = line_id;
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
void merge(Queue *close, Queue *open){
    if (close->head == NULL)
        return;
    else if (open->head == NULL){
        open->head = close->head;
        open->last = close->last;
        close->head = close->last = NULL;
        close->firstline = open;
    }else{
        Node *tail = open->last;
        Node *start = close->head;
        tail->next = start;
        start->prev = tail;
        open->last = close->last;
        close->head = close->last = NULL;
        close->firstline = open;
    }
    Mergeheap(close, open);
    return;
}
Queue *getLine(Queue *line){
    if (line->firstline == line)
        return line;
    else{
        line = getLine(line->firstline);
        return line;
    }
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
    return;
}

int main(){
    int t;
    scanf("%d", &t);
    /* create lines */
    Queue *lines[LINE];
    for (int i = 0; i < LINE; i++)
        lines[i] = (Queue *)malloc(sizeof(Queue));
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
        /* initailize queue lines */
        for (int i = 0; i < l; i++)
            init(lines[i]);
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
                Queue *line = lines[ptr->target_line];
                if (ptr->operation[0] == 'p'){
                    int value = ptr->target;
                    push(line, ptr->target_line, value, address);
                    enqueued[value] = true;
                }else{
                    Queue *close_line = lines[ptr->target];
                    merge(close_line, line);
                }
                ptr = ptr->next;
            }
            Queue *line = getLine(lines[address[key]->line]);
            possible = Verify(line, address[key], key, enqueued);
            if (possible){
                Pop(line, address[key]);
            }
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
