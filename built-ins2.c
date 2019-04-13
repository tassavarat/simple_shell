#include "simple_shell.h"

/**
 * listint_len - counts the number elements of a linked list
 * @h: a pointer to the head of a linked list
 * Return: The number of nodes
 */
size_t list_len(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		count++;
		h = h->next;
	}
	return (count);
}

/**
 * delete_nodeint_at_index - deletes nth element
 * @head: a pointer to the head
 * @index: index of a node to be removed
 * Return: Return 1 if succes or -1 when it fails
 */
int delete_node_at_index(list_t **head, size_t index)
{
	unsigned int i;
	list_t *current;
	list_t *forward;

	if (*head == NULL)
		return (-1);
	current = *head;
	if (index == 0)
	{
		*head = current->next;
		free(current->str);
		free(current);
		return (1);
	}
	for (i = 0; i < index - 1; i++)
	{
		if (current->next == NULL)
			return (-1);
		current = current->next;
	}
	forward = *head;
	if (forward->next == NULL)
		return (-1);
	forward = current->next;
	current->next = forward->next;
	free(forward->str);
	free(forward);
	return (1);
}

/**
 * free_list - frees given linked list
 * @head: first element of a linked list
 * Return: Nothing.
 */
void free_list(list_t *head)
{
	list_t *current_addr = head;
	list_t *next_addr;

	if (head == NULL)
		return;
	while (current_addr->next != NULL)
	{
		free(current_addr->str);
		next_addr = current_addr->next;
		free(current_addr);
		current_addr = next_addr;
	}

	free(current_addr->str);
	free(current_addr);
}

/**
 * print_list - Prints all elements of a list
 * @h: Pointer to a list
 *
 * Return: Number of nodes
 */
size_t print_list(const list_t *h)
{
	unsigned int i = 0;

	while (h)
	{
		if (!h->str)
			printf("(nil)\n");
		else
			printf("%s\n", h->str);
		h = h->next;
		++i;
	}
	return (i);
}

/**
 * add_node_end - Adds a node at the end of a list
 * @head: Pointer to address of a list
 * @str: Pointer to string
 *
 * Return: Address of new element
 * On error, NULL
 */
list_t *add_node_end(list_t **head, const char *str)
{
	list_t *new;
	list_t *old = *head;

	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	new->str = strdup(str);
	new->next = NULL;
	if (!*head)
	{
		*head = new;
		return (*head);
	}
	while (old->next)
		old = old->next;
	old->next = new;
	return (new);
}

list_t *arrtol(void)
{
	int i = 0;
	list_t *head = NULL;

	while(environ[i])
	{
		add_node_end(&head, environ[i]);
		++i;
	}
	return (head);
}

/**
 *
 */
char **ltoa(list_t *head)
{
	int i = 0, len = list_len(head);
	char **arr = NULL;

	if (!head)
		return (NULL);
	arr = malloc(sizeof(char *) *(len + 1));
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
 *
 */
int _unsetenv(arguments_t *args)
{
	list_t *tmp = args->head;
	size_t i = 0;

	while (tmp)
	{
		if (!(_strncmp(tmp->str, args->arr[1], _strlen(args->arr[1]))))
		{
			delete_node_at_index(&(args->head), i);
			break;
		}
		tmp = tmp->next;
		++i;
	}
	args->_environ = ltoa(args->head);
	return (1);
}

/*
void _unsetenv(void)
{
	list_t *head = NULL;
	char *name = "PATH";
	char **arr;
	unsigned int i = 0;

	head = arrtol();
	print_list(head);
	printf("############################################################\n");
	_unsetenv(name, &head);
	print_list(head);
	arr = ltoa(head);
	while (arr[i])
	{
		printf("\n", arr[i]);
		++i;
	}
	free_list(head);
	free(arr);  ltoa
	return (0);
}
*/
