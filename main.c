#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
 * _strtok - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: returns the differences of ASCII characters
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
 * d_space - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: returns the differences of ASCII characters
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
 * tokarr - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: returns the differences of ASCII characters
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
	/*char *argv1[] = {"", NULL};
	char str[] = "   Hello   World Hi   ";
	char **tim = tokarr(str);
	while (tim[len])
	{
		printf("%s\n", tim[len]);
		len++;
	}*/
	while(18)
	{
		 printf("($) ");
		 get = getline(&buffer, &len, stdin);
		 buffer[get - 1] = '\0';
		 arr = tokarr(buffer);
		 /* pure = d_space(buffer); */
		 //	printf("%s", pure);
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
