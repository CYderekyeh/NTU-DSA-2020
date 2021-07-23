#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
typedef struct DisjointSet{
    int p;
    int rank;
} disjoint_set;
disjoint_set ds[1 << 24];
bool set[1 << 24] = {};
int c2i(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    else if ('a' <= c && c <= 'z') return c - 'a' + 10;
    else if ('A' <= c && c <= 'Z') return c - 'A' + 36;
    return -1;
}
int hash(const char* s) {
    int ret = 0;
    for (int i = 0; i < 4; ++i)
    ret = (ret << 6) | c2i(s[i]);
    return ret;
}
void makeset(const char* s){
    int i = hash(s);
    disjoint_set *x = &ds[i];
    x->p = i;
    x->rank = 0;
}
inline void static init(const char* s) {
    int i = hash(s);
    if (!set[i]) {
        makeset(s);
        set[i] = 1;
    }
}
int find_root(int i){
    disjoint_set *x = &ds[i];
    if (i != x->p)
        x->p = find_root(x->p);
    return x->p;
}
int find_set(const char* s) {
    init(s);
    int i = hash(s);
    disjoint_set *x = &ds[i];
    if (i != x->p)
        x->p = find_root(x->p);
    return x->p;
}
void link(const char *ra, const char *rb) {
    int a = find_set(ra), b = find_set(rb);
    disjoint_set *x = &ds[a];
    disjoint_set *y = &ds[b];
    if (x->rank > y->rank)
        y->p = a;
    else{
        x->p = b;
        if (x->rank == y->rank)
            y->rank++;
    }
}
bool same_set(const char *a, const char *b) {
    return (find_set(a) == find_set(b));
}
bool stringcompare(const char *a, const char *b) {
    int num = strlen(a) / 4;
    bool same = true;
    for (int i = 0; i < num; i++){
        int index = 4 * i;
        char ai[5] = {0};
        strncpy(ai, a + index, 4);
        char bi[5] = {0};
        strncpy(bi, b + index, 4);
        same = same_set(ai, bi);
        if (!same)
            break;
    }
    return same;
}
int main() {
    int n;
    scanf("%d", &n);
    char cmd[16], a[512], b[512];
    for (int i = 0; i < n; ++i) {
        scanf("%s %s %s", cmd, a, b);
        if (!strcmp(cmd, "union")) {
            init(a);
            init(b);
            link(a, b);
        }else{
            bool same = stringcompare(a, b);
            if(same) puts("True");
            else puts("False");
        }
    }
    system("pause");
    return 0;
}