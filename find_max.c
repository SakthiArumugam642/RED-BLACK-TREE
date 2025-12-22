#include "rbt.h"

tree_t * find_maximum(tree_t *node)
{
	while(node->right != NULL){
		node = node->right;
	}
	return node;
}

