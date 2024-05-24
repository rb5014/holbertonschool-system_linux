#include "multithreading.h"

#include "multithreading.h"
#include <stdlib.h>

#include "multithreading.h"
#include <stdlib.h>

/**
 * create_task - Creates a task
 * @entry: Pointer to the entry function of the task
 * @param: Parameter that will later be passed to the entry function
 *
 * Return: Pointer to the created task structure, or NULL on failure
 */
task_t *create_task(task_entry_t entry, void *param)
{
	task_t *task;

	/* Allocate memory for the task structure */
	task = malloc(sizeof(*task));
	if (!task)
		return (NULL);

	/* Initialize task fields */
	task->entry = entry;	/* Set the entry function */
	task->param = param;	/* Set the param to be passed to the entry function */
	task->status = PENDING; /* Set the initial status to PENDING */
	task->result = NULL;	/* Initialize the result to NULL */

	/* Initialize the mutex for the task */
	if (pthread_mutex_init(&task->lock, NULL) != 0)
	{
		free(task); /* If mutex initialization fails, free the task memory */
		return (NULL);
	}

	return (task); /* Return the created task */
}

#include "multithreading.h"
#include <stdlib.h>

/**
 * destroy_task - Destroys a task
 * @task: Pointer to the task to destroy
 */
void destroy_task(task_t *task)
{
	/* Destroy the mutex for the task */
	pthread_mutex_destroy(&task->lock);

	/* Destroy the list of results, freeing each element's memory */
	list_destroy(task->result, free);

	/* Free the memory allocated for the result list itself */
	free(task->result);

	/* Free the memory allocated for the task */
	free(task);
}

/**
 * exec_tasks - executes tasks
 * @tasks: tasks to execute
 * This function serves as a thread entry
 * This function can safely return NULL as its
 * return value will not be retrieved
 * This function must go through the list of tasks and execute them,
 * but there’s a challenge:
 * Multiple thread will be going through the list of tasks,
 * and a task must only be executed once
 * We must use tprintf to print when a task is started, and completed
 * Return: NULL
 */
void *exec_tasks(list_t const *tasks)
{
	node_t *node;

	for (node = tasks->head; node; node = node->next)
	{
		task_t *task = (task_t *)node->content;

		/* Lock the task to safely check and update its status */
		pthread_mutex_lock(&task->lock);

		/* Check if the task is still pending */
		if (task->status == PENDING)
		{
			/* Mark the task as started */
			task->status = STARTED;

			/* Unlock the task before executing it to allow other threads to proceed */
			pthread_mutex_unlock(&task->lock);

			/* Log that the task has started */
			tprintf("[%lu] [%02d] Started\n", pthread_self(),
					(int)(node - tasks->head));

			/* Execute the task entry function and store the result */
			task->result = task->entry(task->param);

			/* Log that the task has completed successfully */
			tprintf("[%lu] [%02d] Success\n", pthread_self(),
					(int)(node - tasks->head));

			/* Lock the task again to update its status */
			pthread_mutex_lock(&task->lock);
			task->status = SUCCESS;
		}

		/* Unlock the task after checking/updating its status */
		pthread_mutex_unlock(&task->lock);
	}
	return NULL;
}
