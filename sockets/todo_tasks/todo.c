#include "todo.h"

/**
 * create_node - create a todo node, add it to the list
 * @title: title of the new todo task
 * @description: description of the new todo task
 * Return: pointer to the created node, of NULL on failure
*/
todo_node_t *create_node(const char *title, const char *description)
{
	static int id;
	todo_node_t *new_node = malloc(sizeof(todo_node_t));

	if (!new_node)
		return (NULL);
	new_node->id = id++;
	new_node->title = strdup(title);
	new_node->description = strdup(description);
	new_node->next = NULL;

	return (new_node);
}

/**
 * insert_at_tail - insert node at tail
 * @head: adress of pointer to current head of the list
 * @node_to_insert: pointer node to insert at head
*/
void insert_at_tail(todo_node_t **head, todo_node_t *node_to_insert)
{
	if (*head == NULL)
	{
		node_to_insert->next = *head;
		*head = node_to_insert;
	}
	else
	{
		todo_node_t *tmp = *head;

		while (tmp != NULL)
		{
			if (tmp->next == NULL)
			{
				tmp->next = node_to_insert;
				break;
			}
			tmp = tmp->next;
		}
	}
}

/**
 * find_node_with_title - find node with title
 * @head: pointer to head of list
 * @title: title of the node to find
 * Return: pointer to the found node
*/
todo_node_t *find_node_with_title(const todo_node_t *head, char *title)
{
	const todo_node_t *tmp = head;

	while (tmp != NULL)
	{
		if (strcmp(tmp->title, title) == 0)
			return ((todo_node_t *) tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

/**
 * remove_node - remove node with title
 * @head: pointer to head of list
 * @title: title of the node to remove
*/
void remove_node(todo_node_t *head, char *title)
{
	todo_node_t *tmp = head, *prev_tmp = NULL;

	if ((title == NULL) || (strlen(title) == 0))
	{
		printf("No title provided\n");
		return;
	}

	while (tmp != NULL)
	{
		if (strcmp(tmp->title, title) == 0) /* found node to remove */
		{
			if (prev_tmp != NULL) /* update link */
				prev_tmp->next = tmp->next;
			free(tmp);
			return;
		}
		prev_tmp = tmp;
		tmp = tmp->next;
	}
	/* After loop, node not found */
	printf("Todo item named \"%s\" not found\n", title);
}

/**
 * get_node_json_repr - get the json representation of a todo node
 * @node: node to get the json representation of
 * Return: the json reprensation of the node
*/
char *get_node_json_repr(todo_node_t *node)
{
	char *json_repr;

	asprintf(&json_repr, "{\"id\":%i,\"title\":\"%s\",\"description\":\"%s\"}",
			node->id, node->title, node->description);

	return (json_repr);
}
