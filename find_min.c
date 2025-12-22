#include "rbt.h"

tree_t* find_minimum(tree_t *node)
{

	while(node->left != NULL){
		node = node->left;
	}
	return node;
}
