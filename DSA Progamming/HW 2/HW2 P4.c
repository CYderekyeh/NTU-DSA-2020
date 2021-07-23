#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Strange_TreeNode{
    int p;
    int l;
    int r;
    int key;
    bool upper_bounded;
    int ubound;
    bool lower_bounded;
    int lbound;
    bool valid;
};
typedef struct Strange_TreeNode TreeNode;

void savedata(TreeNode *node[], int index, int key, int left, int right){
    node[index]->upper_bounded = false;
    node[index]->lower_bounded = false;
    node[index]->key = key;
    node[index]->l = left;
    node[index]->r = right;
    if (left != -1)
        node[left]->p = index;
    if (right != -1)
        node[right]->p = index;
    return;
}
bool leftchild(TreeNode *parent, int c_index){
    return (parent->l == c_index);
}
bool rightchild(TreeNode *parent, int c_index){
    return (parent->r == c_index);
}
bool upperbounded(TreeNode *node){
    return node->upper_bounded;
}
bool lowerbounded(TreeNode *node){
    return node->lower_bounded;
}
bool valid(TreeNode *node){
    return node->valid;
}
void verify(TreeNode *node[], int c_index, int *count){
    TreeNode *child = node[c_index];
    /* initialize if node is root */
    if (c_index == 1){
        child->valid = true;
        (*count)++;
        return;
    }
    /* other case */
    int p_index = node[c_index]->p;
    TreeNode *parent = node[p_index];
    /* pass down the bounded value */
    child->upper_bounded = parent->upper_bounded;
    if (upperbounded(child))
        child->ubound = parent->ubound;
    child->lower_bounded = parent->lower_bounded;
    if (lowerbounded(child))
        child->lbound = parent->lbound;
    /* update the bounded value */
    if ((leftchild(parent, c_index)) && 
        ((parent->key < child->ubound) || !upperbounded(child))){
        child->ubound = parent->key;
        child->upper_bounded = true;
    }else if ((rightchild(parent, c_index)) && 
        ((parent->key > child->lbound) || !lowerbounded(child))){
        child->lbound = parent->key;
        child->lower_bounded = true;
    }
    /* verify the bounded ancestor key */
    if (upperbounded(child) && (child->key >= child->ubound)){
        child->valid = false;
        return;
    }else if (lowerbounded(child) && (child->key <= child->lbound)){
        child->valid = false;
        return;
    }else{
        child->valid = true;
        (*count)++;
        return;
    }

}
int main(){
    int node_number;
    scanf("%d", &node_number);
    /* indexing from 1 to N*/
    TreeNode *node[node_number + 1];
    for (int i = 1; i <= node_number; i++){
        node[i] = (TreeNode *)malloc(sizeof(TreeNode));
    }
    int valid_count = 0;
    for (int i = 1; i <= node_number; i++){
        int key, left, right;
        scanf("%d%d%d", &key, &left, &right);
        savedata(node, i, key, left, right);
        verify(node, i, &valid_count);
    }
    printf("%d", valid_count);

    system("pause");
    return 0;
}
