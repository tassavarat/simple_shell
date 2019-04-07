#include "simple_shell.h"

/**
 * _getenv - Searches for files in the PATH
 * @name: String being searched
 *
 * Return: Path of corresponding name value
 * NULL on error
 */
char *_getenv(const char *name)
{
	char *token;
	size_t i = 0;

	while (environ[i] && name)
	{
		token = _strtok(environ[i], "=");
		if (!strcmp(token, name))
			return (_strtok(NULL, "="));
		i++;
	}
	return (NULL);
}
