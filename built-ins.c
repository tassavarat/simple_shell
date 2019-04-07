#include "simple_shell.h"

/**
 * print_env - Prints environmental variables
 */
void print_env(void)
{
	size_t i = 0;

	while (environ[i])
		printf("%s\n", environ[i++]);
}
