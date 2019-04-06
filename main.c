#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

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
char  **tokarr(char *str)
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


int main(int argc, char *argv[], char *envp[])
{
	char *buffer, *pure;
	size_t len = 0, i = 0;
	int get, pid;
	char **arr;

	while(18)
	{
		printf("($) ");
		get = getline(&buffer, &len, stdin);
		buffer[get - 1] = '\0';
		arr = tokarr(buffer);
		while (arr[i])
		{
			d_space(arr[i]);
			i++;
		}
		if (!strcmp(arr[0], "exit"))
		{
			exit(98);
		}
		if (get == -1)
		{
			printf("\n");
			break;
		}
		pid = fork();
		if (pid < 0)
		{
			printf("Continue");
			continue;
		}
		if (pid == 0)
		{
			if (execve(arr[0], arr, NULL) == -1)
			{
				perror("Error:");
				return (-1);
			}
		}
		else
		{
			wait(NULL);
			continue;
		}
	}
	free(buffer);
	return (0);
}
