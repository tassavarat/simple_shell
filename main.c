#include "simple_shell.h"

int main(int argc, char *argv[], char *envp[])
{
	char *buffer;
	(void)argc;
	(void)argv;
	size_t len = 0, i = 0;
	int get, pid;
	char **arr;
	//print_env();
	while(18)
	{
		i++;
		_puts("($) "); //printf("($) ");
		get = getline(&buffer, &len, stdin);
		buffer[get - 1] = '\0';
		arr = tokarr(buffer);
		if (!arr[0])
		{
			continue;
		}
		if (!strcmp(arr[0], "exit"))
		{
			free(arr);
			free(buffer);
			exit(98);
		}
		/* if (!strcmp(arr[0], "clear")) */
		/* { */
		/* 	printf("\033[2J"); */
		/* 	continue; */
		/* } */
		if (get == -1)
		{
			printf("\n");
			free(arr);
			free(buffer);
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
			if (execve(arr[0], arr, envp) == -1)
			{
				dprintf(2, "Hey %ld\n", i);
				//perror(NULL);
				free(arr);
				free(buffer);
				return (-1);
			}
		}
		else
		{
			wait(NULL);
			continue;
		}
<<<<<<< HEAD
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
=======
		free(arr);
		free(buffer);
>>>>>>> farrukh
	}
	return (0);
}
