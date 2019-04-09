#include "simple_shell.h"

/**
 * main - Simple shell
 *
 * Return: 0;
 */
int main(void)
{
	/*	signal(SIGINT, signal_handler);  still not working */
	_shell();
	return (0);
}
