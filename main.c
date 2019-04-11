#include "simple_shell.h"

/**
 * main - Simple shell
 *
 * Return: 0;
 */
int main(int ac, char *av[])
{
	arguments_t arguments;
	arguments.buf = NULL;
	arguments.arr = NULL;
	arguments.count = 0;
	arguments.av = av;
	arguments.ac = ac;

	//initialize_struct(arguments);
	signal(SIGINT, signal_handler);
	_shell(arguments);
	return (0);
}

/**
 * initialize_struct - Simple shell
 * @arguments: args
 */
/*void initialize_struct(arguments_t arguments)
  {
  arguments.buf = NULL;
  arguments.arr = NULL;
  arguments.count = 0;
  }*/
