#include "rbt.h"

int delete_maximum(tree_t **root)
{
	if(*root == NULL){
		return FAILURE;
	}
	delete(root, find_maximum(*root)->data);
	return SUCCESS;
}
