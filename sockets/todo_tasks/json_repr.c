#include "todo.h"

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

/**
 * get_list_json_repr - get the json representation of a todo list
 * @head: head of the list to get the json representation of
 * Return: the json reprensation of the node
*/
char *get_list_json_repr(todo_node_t *head)
{

	todo_node_t *tmp = head;
	char *list_json = strdup("[");
	int first_done = 0;

	while (tmp != NULL)
	{
		char *node_json_repr = get_node_json_repr(tmp);

		if (first_done == 0)
		{
			list_json = realloc(list_json,
									 strlen(list_json) + strlen(node_json_repr) + 1);
			first_done++;
		}
		else
		{
			list_json = realloc(list_json,
									 strlen(list_json) + strlen(",") + strlen(node_json_repr) + 1);
			strcat(list_json, ",");
		}
		strcat(list_json, node_json_repr);
		free(node_json_repr);
		tmp = tmp->next;
	}
	list_json = realloc(list_json, strlen(list_json) + strlen("]"));
	strcat(list_json, "]");

	return (list_json);
}
