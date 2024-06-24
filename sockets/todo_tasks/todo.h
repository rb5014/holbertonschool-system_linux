#ifndef TODO_H
#define TODO_H
#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * struct todo_node_s - struct holding todo node information
 * @id: unique id of todo node
 * @title: title of the todo node
 * @description: description of the todo node
 * @next: pointer to next node
*/
typedef struct todo_node_s
{
	int id;
	char *title;
	char *description;
	struct todo_node_s *next;
} todo_node_t;

todo_node_t *create_node(const char *title, const char *description);
void insert_at_tail(todo_node_t **head, todo_node_t *node_to_insert);
todo_node_t *find_node_with_title(const todo_node_t *head, char *title);
void remove_node(todo_node_t *head, char *title);
char *get_node_json_repr(todo_node_t *node);
#endif /* TODO_H */
