#include "simple_shell.h"

void progress_bar(void);

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
	printf("%d\n", arguments.exit);
	return (arguments.exit);
}

/**
 * initialize_struct - Simple shell
 * @arguments: args
 */
void initialize_struct(arguments_t *arguments __attribute__((unused)))
{
	arguments->buf = NULL;
	arguments->arr = NULL;
	arguments->count = 0;
	arguments->head = arrtol();
	arguments->exit = 0;
}
