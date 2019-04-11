#include "simple_shell.h"

/**
 * print_env - Prints environmental variables
 */
int print_env(void)
{
	size_t i = 0;

	while (environ[i])
		_puts(environ[i++]);
	return(1);
}


int call_exit(void)
{
	printf("EXIT\n");
	return (1);
}

int custom_cd(void)
{
	write(1,"CD\n", 3);
	return(1);
}


int (*builtins(arguments_t args))(void)
{
	built_ins_t func_array[] = {
		{"env", print_env},
		{"exit", call_exit},
		{"cd", custom_cd},
		{NULL, NULL}
	};
	int  i = 0, j;

	while (func_array[i].bi)
	{
		printf("%s\n", func_array[i].bi);
		if (!_strcmp(args.arr[0], func_array[i].bi))
		{
			printf("%s    %s\n", func_array[i].bi, args.arr[0]);
			return (func_array[i].f);
		}
		i++;
	}
	return (0);
}
