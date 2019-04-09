#include "simple_shell.h"

/**
 * convert - Function that converts our int to hex, octal, or binary
 * @num: Number passed into the function
 * @base: Base to convert to
 *
 * Return: Converted number of a certain base
 */
char *convert(unsigned int num, int base)
{
	static const char Representation[] = "0123456789ABCDEF";
	static char buffer[50];
	char *ptr;

	ptr = &buffer[49];
	*ptr = '\0';
	do {
		*--ptr = Representation[num % base];
		num /= base;
	} while (num != 0);
	return (ptr);
}

/**
 * error - Displays an error
 * @i:
 * @cmd:
 */
void error(int i, char *cmd)
{
	char *number = convert(i, 10);

	if (errno == ENOTDIR || errno == ENOENT)
	{
		_puts("sh: ");
		_puts(number);
		_puts(": ");
		_puts(cmd);
		write(STDERR_FILENO, ": not found\n", 12);
	}
	else
	{
		_puts("sh: ");
		_puts(number);
		_puts(": ");
		_puts(cmd);
		perror(NULL);
	}
}

/**
 * _fork - Creates a buffer, forks, executes, free's if necessary
 * @buffer - String storing user input
 */
void _fork(char *buffer)
{
	char **arr = NULL;
	static int count;
	pid_t pid;

	++count;
	arr = tokarr(buffer);
	if (!arr[0])
	{
		free(arr);
		return;
	}
	if (!strcmp(arr[0], "exit"))
	{
		free(arr);
		free(buffer);
		exit(98);
	}
	pid = fork();
	if (pid < 0)
	{
		printf("Continue");
		return;
	}
	if (pid == 0)
	{
		arr[0] = get_path(arr[0]);
		if (execve(arr[0], arr, NULL) == -1)
		{
			error(count, arr[0]);
			free(arr);
			free(buffer);
			exit(1);
		}
	}
	else
	{
		wait(NULL);
	}
	free(arr);
}
