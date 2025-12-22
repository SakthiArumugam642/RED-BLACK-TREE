#include "rbt.h"

void print_tree(tree_t *root)
{
     if(root == NULL) return;
    
    print_tree(root->left);
    printf("%d(%c) ", root->data, root->color ? 'R' : 'B');
    print_tree(root->right);
}