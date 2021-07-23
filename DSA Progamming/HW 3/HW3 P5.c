// reference https://www.youtube.com/watch?v=6x0UlIBLRsc&t=1438s
// reference https://cp-algorithms.com/data_structures/treap.html
// reference https://amoshyc.github.io/CPsolution/template/ds/treap_implicit_key.html
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#define FOR(i,a,b) for(int i=(a);i<(b);++i)  
#define REP(i,n) FOR(i,0,n) 
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define max(a,b) ((a>b)?a:b)
typedef long long ll;
struct treap { 
    int pri, count, val;
    int inc, max; bool rev;
    struct treap *l, *r;
};
typedef struct treap treap;
int count(treap *t) {
    return (t ? t->count : 0);
}
void swap(treap **a, treap **b){
    treap *temp = *a;
    *a = *b;
    *b = temp;
}
void push(treap *t) {
    if (t->rev) {
        if (t->l) {
            swap(&(t->l->l), &(t->l->r));
            t->l->rev = !t->l->rev;
        }
        if (t->r) {
            swap(&(t->r->l), &(t->r->r));
            t->r->rev = !t->r->rev;
        }
        t->rev = false;
    }
    if (t->inc) {
        int inc = t->inc;
        if (t->l) {
            t->l->val += inc;
            t->l->inc += inc;
            t->l->max += inc;
        }
        if (t->r) {
            t->r->val += inc;
            t->r->inc += inc;
            t->r->max += inc;
        }
        t->inc = 0;
    }
}
void pull(treap *t) {
    t->count = 1 + count(t->l) + count(t->r);
    t->max = t->val;
    if (t->l) t->max = max(t->max, t->l->max);
    if (t->r) t->max = max(t->max, t->r->max);
}
treap *new_treap(int val) {
    treap *new_t = (treap *)malloc(sizeof(treap));
    new_t->val = val;
    new_t->pri = rand();
    new_t->count = 1;
    new_t->inc = 0;
    new_t->max = val;
    new_t->rev = false;
    new_t->l = new_t->r = NULL;
    return new_t;
}
treap *merge(treap *a, treap *b) { 
    if (!a || !b) return (a ? a : b);
    if (a->pri > b->pri) {
        push(a);
        a->r = merge(a->r, b);
        pull(a);
        return a;
    }else{
        push(b);
        b->l = merge(a, b->l);
        pull(b);
        return b;
    }
}
void split(treap *t, treap **a, treap **b, int k) {
    if (!t) {
        *a = *b = NULL; 
        return; 
    }
    push(t);
    int left_size = count(t->l);
    if (k > left_size) {
        *a = t;
        split(t->r, &(t->r), b, k - left_size - 1);
        pull(t);
    }else{
        *b = t;
        split(t->l, a, &(t->l), k);
        pull(t);
    }
}
int find_max_node_index(treap *t, int ind){
    push(t);
    if (t->l && t->l->max >= t->max){ // find leftmost max index
        ind = find_max_node_index(t->l, ind);
        pull(t);
        return ind;
    }else if (t->r && t->r->max >= t->max && t->val != t->max){
        ind = find_max_node_index(t->r, ind + count(t->l)+ 1);
        pull(t);
        return ind;
    }
    ind += count(t->l);
    pull(t);
    return ind;
}
void Insert(treap **t, int val, int k) {
    treap *a, *b;
    split(*t, &a, &b, k);
    *t = merge(merge(a, new_treap(val)), b);
}
void Delete(treap **t, int k) {
    treap *a, *b, *c, *d;
    split(*t, &a, &b, k - 1); 
    split(b, &c, &d, 1); //  c is k_th node
    *t = merge(a, d);
}
void Increase(treap **t, int l, int r, int inc) {
    treap *a, *b, *c, *d;
    split(*t, &a, &b, r); 
    split(a, &c, &d, l - 1); 
    d->inc += inc;
    d->val += inc;
    d->max += inc;
    *t = merge(merge(c, d), b);
}
int Query(treap **t, int l, int r) {
    treap *a, *b, *c, *d;
    split(*t, &a, &b, r); 
    split(a, &c, &d, l - 1); 
    int ans = d->max;
    *t = merge(merge(c, d), b);
    return ans;
}
void Reverse(treap **t, int l, int r) {
    treap *a, *b, *c, *d;
    split(*t, &a, &b, r); 
    split(a, &c, &d, l - 1); 
    swap(&(d->l), &(d->r));
    d->rev = !d->rev;
    *t = merge(merge(c, d), b);
}
void RemoveLargest(treap **t){
    assert(*t);
    int max_ind = find_max_node_index(*t, 1);
    Delete(t, max_ind);
}
void print(treap *t) {
    if (!t) 
        return;
    push(t);
    print(t->l);
    printf("%d ", t->val);
    print(t->r); 
}
int main(){
    int N, Q;
    scanf("%d%d", &N, &Q);
    treap *t = NULL;
    REP(i, N){
        int x;
        scanf("%d", &x);
        Insert(&t, x, i);
    }
    REP(i, Q){
        int id;
        scanf("%d", &id);
        switch(id){
            case(1):{  //insert p, k
                int p, k;
                scanf("%d%d", &p, &k);
                Insert(&t, p, k);
                break;
            }case(2):{  // delete k
                int k;
                scanf("%d", &k);
                Delete(&t, k);
                break;
            }case(3):{  // increase l, r, k
                int l, r, p;
                scanf("%d%d%d", &l, &r, &p);
                Increase(&t, l, r, p);
                break;
            }case(4):{  // query l, r
                int l, r;
                scanf("%d%d", &l, &r);
                int ans = Query(&t, l, r);
                printf("%d\n", ans);
                break;
            }case(5):{  // reverse l, r
                int l, r;
                scanf("%d%d", &l, &r);
                Reverse(&t, l, r);
                break;
            }case(6):{  // remove largest
                RemoveLargest(&t);
                break;
            }default:{
                assert(0);
            }
        }
    }

    return 0;
}