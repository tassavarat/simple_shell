#include "simple_shell.h"

/**
 * _atoi - converts string to an integer
 * @s: takes string
 *
 * Return: returns an integer
 */
int _atoi(char *s)
{
	int i, minus, flag;
	unsigned int n;

	i = 0;
	flag = 0;
	minus = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			n = n * 10 + (s[i] - '0');
			flag++;
		}
		else if (s[i] == '-')
		{
			minus++;
		}
		else if (flag && !(s[i] >= '0' && s[i] <= '9'))
		{
			break;
		}
		i++;
	}
	if (minus % 2 == 0)
		return (n);
	else
		return (-n);
}

/**
 * print_env - Prints environmental variables
 * @args: Arguments struct
 *
 * Return: 1 on success
 */
int print_env(arguments_t *args)
{
	list_t *head = args->head;

	while (head)
	{
		_puts(head->str);
		_puts("\n");
		head = head->next;
	}
	return (1);
}

/**
 * call_exit - Exits shell and free's allocated memory
 * @args: Arguments structure
 *
 * Return: Nothing
 */
int call_exit(arguments_t *args)
{
	int number = 0;

	if (args->arr[1])
		number = _atoi(args->arr[1]) % 256;
	free(args->arr);
	free(args->buf);
	free_list(args->head);
	args->exit = number;
	return (-1);
}

/**
 * custom_cd - Changes directory
 * @args: Arguments structure
 *
 * Return: 1 on success
 */
int custom_cd(arguments_t *args)
{
	char *home = _getenv("HOME", args);
	char *cwd = NULL;
	char *cwd1 = NULL;
	char *oldwd = NULL;
	char *arg = args->arr[1];

	oldwd = _getenv("OLDPWD", args);
	args->arr[1] = "OLDPWD", args->arr[2] = cwd = getcwd(cwd, 0);
	_setenv(args);
	if (!arg || *arg == '~')
	{
		chdir(home);
	}
	else if (*arg == '-')
	{
		chdir(oldwd);
		oldwd = NULL;
	}
	else
	{
		chdir(arg);
	}
	args->arr[1] = "PWD", args->arr[2] = cwd1 = getcwd(cwd1, 0);
	_setenv(args);
	free(cwd1);
	free(cwd);
	return (1);
}

/**
 * builtins - Function that determines which built in to call
 * @args: Arguments structure
 *
 * Return: 1 on success
 * 0 on error
 */
int builtins(arguments_t *args)
{
	built_ins_t func_array[] = {
		{"env", print_env},
		{"exit", call_exit},
		{"cd", custom_cd},
		{"unsetenv", _unsetenv},
		{"setenv", _setenv},
		{"help", _help},
		{NULL, NULL}
	};
	int  i = 0;
	static int flag = 0;
	char *cwd = NULL;

	while (func_array[i].bi)
	{
		if (!_strcmp(args->arr[0], func_array[i].bi))
		{
			if (i == 2 && flag)
			{
				args->arr[1] = "OLDPWD", args->arr[2] = cwd = getcwd(cwd, 0);
				_setenv(args);
				flag = 0;
				free(cwd);
			}
			func_array[i].f(args);
			return (1);
		}
		i++;
	}
	return (0);
}
