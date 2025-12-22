#include "rbt.h"


// Transplant - replacing subtree rooted at u with subtree rooted at v
void transplant(tree_t **root, tree_t *u, tree_t *v)
{
	if(u->parent == NULL){
		*root = v;
	}else if(u == u->parent->left){
		u->parent->left = v;
	}else{
		u->parent->right = v;
	}
	
	if(v != NULL){
		v->parent = u->parent;
	}
}

// Fixing Red-Black Tree properties after deletion
void delete_fixup(tree_t **root, tree_t *x, tree_t *x_parent)
{
	tree_t *sibling;
	
	while(x != *root && (x == NULL || x->color == 0))
	{
		// Determine parent if x is NULL
		tree_t *parent = (x != NULL) ? x->parent : x_parent;
		
		// Case A: x is left child
		if(x == parent->left)
		{
			sibling = parent->right;
			
			// Case 1: Sibling is red
			if(sibling != NULL && sibling->color == 1)
			{
				sibling->color = 0;
				parent->color = 1;
				left_rotate(root, parent);
				sibling = parent->right;
			}
			
			// Case 2: Sibling is black with two black children
			if((sibling->left == NULL || sibling->left->color == 0) &&
			   (sibling->right == NULL || sibling->right->color == 0))
			{
				if(sibling != NULL){
					sibling->color = 1;
				}
				x = parent;
				x_parent = x->parent;
			}
			else
			{
				// Case 3: Sibling is black, sibling's right child is black
				if(sibling->right == NULL || sibling->right->color == 0)
				{
					if(sibling->left != NULL){
						sibling->left->color = 0;
					}
					sibling->color = 1;
					right_rotate(root, sibling);
					sibling = parent->right;
				}
				
				// Case 4: Sibling is black, sibling's right child is red
				sibling->color = parent->color;
				parent->color = 0;
				if(sibling->right != NULL){
					sibling->right->color = 0;
				}
				left_rotate(root, parent);
				x = *root; // Exit loop
			}
		}
		// Case B: x is right child (mirror of Case A)
		else
		{
			sibling = parent->left;
			
			// Case 1: Sibling is red
			if(sibling != NULL && sibling->color == 1)
			{
				sibling->color = 0;
				parent->color = 1;
				right_rotate(root, parent);
				sibling = parent->left;
			}
			
			// Case 2: Sibling is black with two black children
			if((sibling->left == NULL || sibling->left->color == 0) &&
			   (sibling->right == NULL || sibling->right->color == 0))
			{
				if(sibling != NULL){
					sibling->color = 1;
				}
				x = parent;
				x_parent = x->parent;
			}
			else
			{
				// Case 3: Sibling is black, sibling's left child is black
				if(sibling->left == NULL || sibling->left->color == 0)
				{
					if(sibling->right != NULL){
						sibling->right->color = 0;
					}
					sibling->color = 1;
					left_rotate(root, sibling);
					sibling = parent->left;
				}
				
				// Case 4: Sibling is black, sibling's left child is red
				sibling->color = parent->color;
				parent->color = 0;
				if(sibling->left != NULL){
					sibling->left->color = 0;
				}
				right_rotate(root, parent);
				x = *root; // Exit loop
			}
		}
	}
	
	if(x != NULL){
		x->color = 0;
	}
}


int delete(tree_t **root, data_t item)
{
	// Step 1: Find the node to delete
	tree_t *z = *root;
	while(z != NULL)
	{
		if(item < z->data){
			z = z->left;
		}else if(item > z->data){
			z = z->right;
		}else{
			break; // Found the node
		}
	}
	
	// Node not found
	if(z == NULL){
		return FAILURE;
	}
	
	tree_t *y = z;
	tree_t *x;
	tree_t *x_parent;
	int y_original_color = y->color;
	
	// Case 1: Node has no left child
	if(z->left == NULL)
	{
		x = z->right;
		x_parent = z->parent;
		transplant(root, z, z->right);
	}
	// Case 2: Node has no right child
	else if(z->right == NULL)
	{
		x = z->left;
		x_parent = z->parent;
		transplant(root, z, z->left);
	}
	// Case 3: Node has two children
	else
	{
		y = find_minimum(z->right); // Find successor
		y_original_color = y->color;
		x = y->right;
		
		if(y->parent == z){
			x_parent = y;
		}else{
			x_parent = y->parent;
			transplant(root, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		
		transplant(root, z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	
	// Free the deleted node
	free(z);
	
	// Fixing Red-Black Tree properties if a black node was deleted
	if(y_original_color == 0){
		delete_fixup(root, x, x_parent);
	}
	
	return SUCCESS;
}