#include "simple_shell.h"

/**
 * _strdup - duplicates a string
 * @str: string
 *
 * Return: a pointer to the string
 */
char *_strdup(const char *str)
{
	char *s;
	int i = 0;

	if (str == NULL)
		return (NULL);
	while (str[i])
		i++;
	s = malloc(sizeof(char) * i + 1);
	if (s == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		s[i] = str[i];
		i++;
	}
	s[i++] = '\0';
	return (s);
}

/**
 * _isalpha - checks if the c is alpha
 * @c: takes character in ASCII
 *
 * Return: 0 or 1
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || ((c >= 'A' && c <= 'Z')) || c == '_')
		return (1);
	else
		return (0);
}
