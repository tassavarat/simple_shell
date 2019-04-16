#include "simple_shell.h"

/**
 * ltoa - Converts linked list to array
 * @head: Pointer to first node
 *
 * Return: Converted array
 */
char **ltoa(list_t *head)
{
	int i = 0, len = list_len(head);
	char **arr = NULL;

	if (!head)
		return (NULL);
	arr = malloc(sizeof(char *) * (len + 1));
	if (!arr)
		return (NULL);

	while (head)
	{
		arr[i] = head->str;
		head = head->next;
		++i;
	}
	arr[i] = NULL;
	return (arr);
}

/**
 * _unsetenv - Unsets the specified environment variable
 * @args: Arugements structure
 * Return: 1 on success
 */
int _unsetenv(arguments_t *args)
{
	list_t *tmp = args->head;
	size_t i = 0, flag = 0;
	(void) flag;

	if (args->arr[1])
	{
		while (tmp)
		{
			if (!(_strncmp(tmp->str, args->arr[1], _strlen(args->arr[1]))))
			{
				delete_node_at_index(&(args->head), i);
				flag = 1;
				break;
			}
			tmp = tmp->next;
			++i;
		}
		return (1);
	}
	error(args, 1);
	return (1);
}

/**
 * _setenv - Sets specified enviroment variable
 * @args: Arguments structure
 *
 * Return: 1 on success
 */
int _setenv(arguments_t *args)
{
	char *variable = NULL;
	char *value = NULL;
	char temp[256] = {0};

	if (args->arr[1] && args->arr[2])
	{
		variable = args->arr[1];
		value = args->arr[2];
		_unsetenv(args);
		_strcat(temp, variable);
		_strcat(temp, "=");
		_strcat(temp, value);
		_strcat(temp, "\0");
		add_node_end(&(args->head), temp);
		return (1);
	}
	error(args, 1);
	return (1);
}
