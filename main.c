#include "simple_shell.h"

int main(void)
{
	char *buffer = NULL;
	size_t len = 0, i = 0;
	int get, pid;
	char **arr = NULL;
	//print_env();
	while(18)
	{
		i++;
		//_puts("($) ");
		printf("($) ");
		get = getline(&buffer, &len, stdin);
		buffer[get - 1] = '\0';
		arr = tokarr(buffer);
		if (!arr[0])
		{
			free(arr);
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
		if (get == EOF)
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
			arr[0] = get_path(arr[0]);
			if (execve(arr[0], arr, NULL) == -1)
			{
				perror(NULL);
				free(arr);
				free(buffer);
				return (-1);
			}
		}
		else
		{
			wait(NULL);
		}
		free(arr);
	}
	free(buffer);
	return (0);
}
