#include "simple_shell.h"

/**
 * _append - Appends strings together
 * @args->arr[0]: User command to append
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
char *_getenv(const char *name) /* Deprecated function */
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
 * @args->arr[0]: String being evaluated
 *
 * Return: Command location
 * String on fail
 */
char *get_path(arguments_t *args)
{
	char *str = _getenv2("PATH", args), *token, *strr;
	static char buff[256];
	struct stat st;
	int i = 0, word = 0, count = 0;

	if (!str)
		return (args->arr[0]);
	if (str[0] == ':' && !stat(args->arr[0], &st))
		return (args->arr[0]);
	while (str && str[i])
	{
		if (!word && str[i] != ':')
		{
			word = 1;
			++count;
		}
		else if (word && str[i] == ':')
			word = 0;
		i++;
	}
	token = _strtok(str, ":");
	while (token && args->arr[0])
	{
		strr = _append(args->arr[0], token, buff);
		if (!stat(buff, &st))
			return (strr);
		if (count-- > 1 && *(token + _strlen(token) + 1) == ':')
		{
			if (!stat(args->arr[0], &st))
				return (args->arr[0]);
		}
		token = _strtok(NULL, ":");
		_memset(buff, 0, 256);
	}
	return (args->arr[0]);
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
