#include "simple_shell.h"

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(int c)
{
	static int i;
	static char buf[BUFSIZ];

	if (c == F_FLUSH || i >= BUFSIZ)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != F_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _strtok - Splits a string
 * @str: String being evaluated
 * @delim: Delimiter
 *
 * Return: An array of each word of the string
 * Null on error
 */
char *_strtok(char *str, const char *delim)
{
	static char *sp;
	char *p;
	int letter = 0;

	if (str)
		sp = str;
	p = sp;
	while (sp && *sp)
	{
		if (*sp == *delim && letter == 0)
		{
			++p;
			++sp;
			continue;
		}
		if (*sp == *delim && letter == 1)
		{
			*sp++ = '\0';
			break;
		}
		letter = 1;
		++sp;
	}
	if (!p || *p == '\0')
		return (NULL);
	return (p);
}

/**
 * d_space - Removes leading and trailing spaces
 * @str: String being evaluated
 *
 * Return: Pointer to the string
 */
char *d_space(char *str)
{
	size_t i = 0;
	int letter = 0;

	while (str && str[i])
	{
		if (str[i] == ' ' && letter == 0)
		{
			++str;
			continue;
		}
		if (str[i] == ' ' && letter == 1)
		{
			str[i] = '\0';
		}
		letter = 1;
		++i;
	}
	return (str);
}

/**
 * tokarr - Creates a double array from tokens
 * @str: String being evaluated
 *
 * Return: Double array
 * Null on failure
 */
char **tokarr(char *str)
{
	char *token;
	char **arr;
	unsigned int i = 0, count = 1, isword = 0, t = 0;
	char *pure = str;

	while (pure && pure[i])
	{
		if (pure[i] != ' ')
		{
			isword = 1;
		}
		if (isword && pure[i] == ' ')
			count++;
		i++;
	}
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	token = _strtok(str, " ");
	while (token)
	{
		arr[t] = token;
		t++;
		token = _strtok(NULL, " ");
	}
	arr[t] = NULL;
	return (arr);
}

/**
 * _puts - prints a string with newline
 * @str: the string to print
 *
 * Return: void
 */
int _puts(char *str)
{
	size_t i = 0;

	while (str[i])
		i++;
	write(1, str, i);
	return (i);
}
