#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef RBT_H
#define RBT_H
#define SUCCESS 0
#define FAILURE -1

typedef int data_t;

typedef struct node
{
	struct node * parent;
	struct node *left;
	data_t data;
	struct node *right;
	int color;
}tree_t;

int insert(tree_t **root, data_t item);
int delete(tree_t **root, data_t item);
tree_t * find_minimum(tree_t *root);
int delete_minimum(tree_t **root);
tree_t * find_maximum(tree_t *root);
int delete_maximum(tree_t **root);
tree_t *create_node(data_t item);
void left_rotate(tree_t **root, tree_t *x);
void right_rotate(tree_t **root, tree_t *y);
void insert_fix(tree_t **root, tree_t *new_node);
void print_tree(tree_t *root);

#endif
