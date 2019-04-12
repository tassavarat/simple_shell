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
	static char buffer[11];
	char *ptr;

	ptr = &buffer[10];
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
 * @args.arr[0]: Command from user
 */
void error(arguments_t args)
{
	char *number = convert(args.count, 10);

	if (errno == ENOTDIR || errno == ENOENT)
	{
		_puts("sh: "), _puts(number), _puts(": "), _puts(args.arr[0]);
		write(STDERR_FILENO, ": not found\n", 12);
	}
	else
	{
		_puts("sh: "), _puts(number), _puts(": "), _puts(args.arr[0]), _puts(": ");
		perror(NULL);
	}
}

/**
 * _shell - Creates a buffer, forks, executes, free's if necessary
 * @args: args
 */
void _shell(arguments_t args)
{
	int get;
	size_t len = 0;

	signal(SIGINT, signal_handler);
	while (18)
	{
		args.count++;
		if (isatty(STDIN_FILENO))
			write(STDERR_FILENO, "(╯°□°)╯︵ ┻━┻ ", 29);
		get = getline(&(args.buf), &len, stdin);
		if (get == EOF)
		{
			if (isatty(STDIN_FILENO))
				_puts("\n");
			break;
		}
		args.buf[get - 1] = '\0';
		printf("get is %d\n", get);
		args.arr = tokarr(_strtok(args.buf, "#"));
		if (!builtins(args))
			_fork(args);
	}
	free(args.buf);
}

/**
 * _fork - Creates a buffer, forks, executes, free's if necessary
 * @args.arr: array of tokens
 */
void _fork(arguments_t args)
{
	pid_t pid;
	char *env[] = {"TERM=xterm", NULL};

	if (!args.arr[0])
	{
		free(args.arr);
		return;
	}
	/*
	if (!_strcmp(args.arr[0], "exit"))
	{
		free(args.arr);
		free(args.buf);
		exit(98);
	}
	*/
	pid = fork();
	if (pid < 0)
	{
		_puts("Continue");
		return;
	}
	if (pid == 0)
	{
		evaluate_var(args.arr);
		args.arr[0] = get_path(args.arr[0]);
		if (execve(args.arr[0], args.arr, env) == -1)
		{
			error(args);
			free(args.arr);
			free(args.buf);
			exit(1);
		}
	}
	else
	{
		wait(NULL);
	}
	free(args.arr);
}

/**
 * signal_handler - Handles Ctrl + C signal
 * @signum: number of the signal
 */
void signal_handler(int signum)
{
	(void) signum;
	signal(SIGINT, signal_handler);
	_puts("\n");
	write(STDERR_FILENO, "(╯°□°)╯︵ ┻━┻ ", 29);
	fflush(stdout);
}
