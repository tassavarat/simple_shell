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
	_strcat(buff, token);
	_strcat(buff, "/");
	_strcat(buff, s);
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
		token = _strtok(environ[i], "=");
		if (!_strcmp(token, name))
			return (_strtok(NULL, "="));
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
	if (str[0] == ':' && !stat(s, &st))
		return (s);
	token = _strtok(str, ":");
	while (token && *s)
	{
		strr = _append(s, token, buff);
		if (!stat(buff, &st))
			return (strr);
		if (*(token + _strlen(token) + 1) == ':')
		{
			if (!stat(s, &st))
				return (s);
		}
		token = _strtok(NULL, ":");
		_memset(buff, 0, 100);
	}
	return (s);
}

/**
 * evaluate_var - Looks for variables in the current environmental  * variables
 * @arguments: An array of tokenized commands
 */
void evaluate_var(arguments_t *arguments)
{
	int i = 0, j = 0, flag = 0, len = 0;
	static char *number;

	while ((arguments->arr)[i])
	{

		if (*((arguments->arr))[i] == '$')
		{
			flag = 1;
			break;
		}
		i++;
	}

	if (flag)
	{
		((arguments->arr))[i]++;
		len = _strlen(((arguments->arr))[i]);
		while (environ[j])
		{
			if (!strncmp(((arguments->arr))[i], environ[j], len))
			{
				((arguments->arr))[i] = environ[j] + len + 1;
				break;
			}
			j++;
		}
	}
	else if (flag && !_strcmp(arguments->arr[i], "?") && WIFEXITED(arguments->status))
	{
		arguments->arr[i] = number = convert(WEXITSTATUS(arguments->status), 10);
	}
}
