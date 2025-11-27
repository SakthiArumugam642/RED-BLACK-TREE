#include "rbt.h"

tree_t * create_node(data_t item)
{
	tree_t *new_node = (tree_t *)malloc(sizeof(tree_t));
	if(new_node == NULL){
		return NULL;
	}
	new_node->data = item;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->parent = NULL;
	new_node->color = 1; // New node is always red (1 = RED, 0 = BLACK)
	return new_node;
}

// Left rotation
void left_rotate(tree_t **root, tree_t *x)
{
	tree_t *y = x->right;
	x->right = y->left;
	
	if(y->left != NULL){
		y->left->parent = x;
	}
	
	y->parent = x->parent;
	
	if(x->parent == NULL){
		*root = y;
	}else if(x == x->parent->left){
		x->parent->left = y;
	}else{
		x->parent->right = y;
	}
	
	y->left = x;
	x->parent = y;
}

// Right rotation
void right_rotate(tree_t **root, tree_t *y)
{
	tree_t *x = y->left;
	y->left = x->right;
	
	if(x->right != NULL){
		x->right->parent = y;
	}
	
	x->parent = y->parent;
	
	if(y->parent == NULL){
		*root = x;
	}else if(y == y->parent->left){
		y->parent->left = x;
	}else{
		y->parent->right = x;
	}
	
	x->right = y;
	y->parent = x;
}

//  Red-Black Tree properties after insertion
void insert_fix(tree_t **root, tree_t *new_node)
{
	tree_t *parent = NULL;
	tree_t *grandparent = NULL;
	
	while(new_node != *root && new_node->color == 1 && new_node->parent->color == 1)
	{
		parent = new_node->parent;
		grandparent = parent->parent;
		
		// Case A: Parent is left child of grandparent
		if(parent == grandparent->left)
		{
			tree_t *uncle = grandparent->right;
			
			// Case 1: Uncle is red - only recoloring needed
			if(uncle != NULL && uncle->color == 1)
			{
				grandparent->color = 1;
				parent->color = 0;
				uncle->color = 0;
				new_node = grandparent;
			}
			else
			{
				// Case 2: Node is right child - left rotation needed
				if(new_node == parent->right)
				{
					left_rotate(root, parent);
					new_node = parent;
					parent = new_node->parent;
				}
				
				// Case 3: Node is left child - right rotation needed
				right_rotate(root, grandparent);
				int temp = parent->color;
				parent->color = grandparent->color;
				grandparent->color = temp;
				new_node = parent;
			}
		}
		// Case B: Parent is right child of grandparent
		else
		{
			tree_t *uncle = grandparent->left;
			
			// Case 1: Uncle is red - only recoloring needed
			if(uncle != NULL && uncle->color == 1)
			{
				grandparent->color = 1;
				parent->color = 0;
				uncle->color = 0;
				new_node = grandparent;
			}
			else
			{
				// Case 2: Node is left child - right rotation needed
				if(new_node == parent->left)
				{
					right_rotate(root, parent);
					new_node = parent;
					parent = new_node->parent;
				}
				
				// Case 3: Node is right child - left rotation needed
				left_rotate(root, grandparent);
				int temp = parent->color;
				parent->color = grandparent->color;
				grandparent->color = temp;
				new_node = parent;
			}
		}
	}
	
	(*root)->color = 0; // Root must always be black
}

int insert(tree_t **root, data_t item)
{
	tree_t *new_node = create_node(item);
	if(new_node == NULL){
		return FAILURE;
	}
	
	// If tree is empty
	if(*root == NULL){
		*root = new_node;
		(*root)->color = 0; // Root is always black
		return SUCCESS;
	}
	
	// BST insertion
	tree_t *current = *root;
	tree_t *parent = NULL;
	
	while(current != NULL){
		parent = current;
		if(item < current->data){
			current = current->left;
		}else if(item > current->data){
			current = current->right;
		}else{
			// Duplicate data not allowed
			free(new_node);
			return FAILURE;
		}
	}
	
	// Set parent pointer
	new_node->parent = parent;
	
	// Link parent to new node
	if(item < parent->data){
		parent->left = new_node;
	}else{
		parent->right = new_node;
	}
	
	// Fix Red-Black Tree properties
	insert_fix(root, new_node);
	
	return SUCCESS;
}