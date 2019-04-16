#include "simple_shell.h"

/**
 * main - Simple shell
 *
 * Return: 0;
 */
int main(void)
{
	arguments_t arguments;

	initialize_struct(&arguments);
       	signal(SIGINT, signal_handler);
	_shell(&arguments);
	return (0);
}

/**
 * initialize_struct - Simple shell
 * @arguments: args
 */
void initialize_struct(arguments_t *arguments __attribute__((unused)))
{
	char buf[PATH_MAX] = {0};
	char *cwd = getcwd(cwd = NULL, 0);

	arguments->buf = NULL;
	arguments->arr = NULL;
	arguments->count = 0;
	arguments->head = arrtol();
	_strcat(buf, "OLDPWD=");
	_strcat(buf, cwd);
	add_node_end(&arguments->head, buf);
	free(cwd);
}
