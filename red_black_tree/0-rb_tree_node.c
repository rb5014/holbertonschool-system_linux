#include "rb_trees.h"
#include <stdlib.h>

/**
 * rb_tree_node - Creates a Red-Black Tree node
 * @parent: pointer to the parent node of the node to create
 * @value: value to put in the node to create
 * @color: color of the node
 * Return: pointer to the new node, or NULL on failure
*/
rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{
	rb_tree_t *new_node = malloc(sizeof(rb_tree_t));

	if (new_node == NULL)
		return (NULL);

	new_node->parent = parent;
	new_node->n = value;
	new_node->color = color;

	return (new_node);
}
