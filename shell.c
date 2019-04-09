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
	static const char rep[] = "0123456789ABCDEF";
	static char buffer[50];
	char *ptr;

	ptr = &buffer[49];
	*ptr = '\0';
	do {
		*--ptr = rep[num % base];
		num /= base;
	} while (num != 0);
	return (ptr);
}

/**
 * error - Displays an error
 * @i: Command counter
 * @cmd: Command from user
 */
void error(int i, char *cmd)
{
	char *number = convert(i, 10);

	if (errno == ENOTDIR || errno == ENOENT)
	{
		_puts("sh: "), _puts(number), _puts(": "), _puts(cmd);
		write(STDERR_FILENO, ": not found\n", 12);
	}
	else
	{
		_puts("sh: "), _puts(number), _puts(": "), _puts(cmd), _puts(": ");
		perror(NULL);
	}
}

/**
 * _shell - Creates a buffer, forks, executes, free's if necessary
 */

void _shell(void)
{
	char *buffer = NULL;
	size_t len = 0;
	int get;
	static size_t count;
	char **arr = NULL;
	signal(SIGINT, signal_handler);
	while (18)
	{
		++count;
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
		arr = tokarr(buffer);
		_fork(buffer, arr, count);
	}
	free(buffer);
}
/**
 * _fork - Creates a buffer, forks, executes, free's if necessary
 * @buffer: String storing user input
 * @arr: array of tokens
 * @count: number of commands entered
 */
void _fork(char *buffer, char **arr, size_t count)
{
	pid_t pid;

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

void signal_handler(int signum)
{
	(void) signum;
	signal(SIGINT, signal_handler);
	puts("\n");
	_shell();
	fflush(stdout);
}
