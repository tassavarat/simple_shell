#include "simple_shell.h"

void progress_bar(void);

/**
 * main - Simple shell
 *
 * Return: 0;
 */
int main()
{
	arguments_t arguments;

	//progress_bar();
	initialize_struct(&arguments);
	signal(SIGINT, signal_handler);
	_shell(&arguments);
	return (0);
}

/**
 * initialize_struct - Simple shell
 * @arguments: args
 */
void initialize_struct(arguments_t *arguments __attribute__((unused)))
{
	arguments->buf = NULL;
	arguments->arr = NULL;
	arguments->count = 0;
	arguments->head = arrtol();
	//	arguments->_environ = ltoa(arguments->head);
}

/**
 * progress_bar - Simple shell progress bar
 */
void progress_bar(void)
{
	const int n = 10;

// Initialize two arrays longer than the number of character to output
	char s1[] = "###################";
	char s2[] = "                    ";

	for (int i = 0; i <= n; i++)
	{
		// Only output the first i characters of s1
		// And the first (n-i) characters of s2
		fprintf(stderr, "Progress: |%.*s%.*s| %02d\r", i, s1, n-i, s2, i);
		fflush(stderr);  //< Flush the output (just in case)
		usleep(10000);
	}

	fprintf(stderr, "\n");
}
