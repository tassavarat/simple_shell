#include "simple_shell.h"

/**
 * main - Simple shell
 *
 * Return: 0;
 */
int main(void)
{
	char *buffer = NULL;
	size_t len = 0;
	int get;

	while (18)
	{
		if (isatty(STDIN_FILENO))
		{
			write(STDERR_FILENO, "TYPEIT:$ ", 9);
		}
		get = getline(&buffer, &len, stdin);
		if (get == EOF)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}
		buffer[get - 1] = '\0';
	}
	free(buffer);
	return (0);
}
