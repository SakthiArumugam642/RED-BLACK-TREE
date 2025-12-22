#include "rbt.h"

int delete_minimum(tree_t **root)
{
	if(*root == NULL){
		return FAILURE;
	}
	delete(root, find_minimum(*root)->data);
	return SUCCESS;
}
