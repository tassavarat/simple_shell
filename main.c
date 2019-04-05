#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


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
		++i;
		letter = 1;
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

void tokarr(char *str)
{
	char *token;
	char **arr;
	unsigned int i = 0, count = 1;
	char *pure = d_space(str);

	while (pure && pure[i])
	{
		if (pure[i] == ' ')
			count++;
		i++;
	}
	printf("%d", count);
}

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

	if (str)
		sp = str;
	p = sp;
	while (sp && *sp)
	{
		if (*sp == *delim)
		{
			*sp++ = '\0';
			break;
		}
		sp++;
	}
	if (!p || *p == '\0')
		return (NULL);
	return (p);
}

int main(int argc, char *argv[], char *envp[])
{
	char *buffer, *pure;
	size_t len = 0;
	int get, pid;
	char *argv1[] = {"", NULL};
	char str[] = "  Hello World Hi";
	tokarr(str);
	/*while(18)
		  {
		  printf("($) ");
		  get = getline(&buffer, &len, stdin);
		  buffer[get - 1] = '\0';
		  pure = d_space(buffer);
		  //	printf("%s", pure);
		  if (!strcmp(pure, "exit"))
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
		  if (execve(pure, argv1, NULL) == -1)
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
		  free(buffer);*/
	return (0);
}
