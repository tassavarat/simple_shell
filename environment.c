#include "simple_shell.h"

/**
 * _append - Appends strings together
 * @s: User command to append
 * @token: PATH string to be appended
 * @buff: String to be returned
 *
 * Return: Appended string
 */
char *_append(char *s, char *token, char *buff)
{
	strcat(buff, token);
	strcat(buff, "/");
	strcat(buff, s);
	return (buff);
}

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

	while (name && environ[i])
	{
		token = strtok(environ[i], "=");
		if (!strcmp(token, name))
			return (strtok(NULL, "="));
		++i;
	}
	return (NULL);
}

/**
 * get_path - Looks for files in the current path
 * @s: String being evaluated
 *
 * Return: Command location
 * String on fail
 */
char *get_path(char *s)
{
	char *str = _getenv("PATH"), *token, *strr;
	static char buff[100];
	struct stat st;

	if (!str)
		return (s);
	if (str[0] == ':')
	{
		if (!stat(s, &st))
			return (s);
	}
	token = strtok(str, ":");
	while (token && *s)
	{
		strr = _append(s, token, buff);
		token = strtok(NULL, ":");
		if (!stat(buff, &st))
			return (strr);
		memset(buff, 0, 100);
	}
	return (s);
}
