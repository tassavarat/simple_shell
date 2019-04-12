#include "simple_shell.h"

/**
 * print_env - Prints environmental variables
 */
int print_env(arguments_t args __attribute__((unused)))
{
	size_t i = 0;

	while (environ[i])
	{
		_puts(environ[i++]);
		_puts("\n");
	}
	free(args.arr);
	return(1);
}

int call_exit(arguments_t args)
{
	free(args.arr);
	free(args.buf);
	exit(1);
	return (1);
}

int custom_cd(arguments_t args __attribute__((unused)))
{
	write(1,"CD\n", 3);
	return(1);
}


int builtins(arguments_t args)
{
	built_ins_t func_array[] = {
		{"env", print_env},
		{"exit", call_exit},
		{"cd", custom_cd},
		{NULL, NULL}
	};
	int  i = 0;

	while (func_array[i].bi)
	{
		if (!_strcmp(args.arr[0], func_array[i].bi))
		{
			func_array[i].f(args);
			return (1);
		}
		i++;
	}
	return (0);
}
