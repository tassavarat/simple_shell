#include "simple_shell.h"

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
	free(args->arr);
	free(args->buf);
	free_list(args->head);
	exit(0);
}

/**
 * custom_cd - Changes directory
 * @args: Arguments structure
 *
 * Return: 1 on success
 */
int custom_cd(arguments_t *args)
{
	char *home = _getenv2("HOME", args);
	char *cwd = NULL;
	char *cwd1 = NULL;
	char *oldwd = NULL;
	char *arg = args->arr[1];

	oldwd = _getenv2("OLDPWD", args);
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
int builtins(arguments_t *args)
{
	built_ins_t func_array[] = {
		{"env", print_env},
		{"exit", call_exit},
		{"cd", custom_cd},
		{"unsetenv", _unsetenv},
		{"setenv", _setenv},
		{NULL, NULL}
	};
	int  i = 0;
	static int flag = 1;
	char *cwd = NULL;

	while (func_array[i].bi)
	{
		if (!_strcmp(args->arr[0], func_array[i].bi))
		{
			if (flag)
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
