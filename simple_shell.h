#ifndef _SIMPLE_SHELL_H_
#define _SIMPLE_SHELL_H_

#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>

/* Symbolic constants */
#define F_FLUSH -1

/* environmental variables */
extern char **environ;

/* strings_functions.c file */
char *_strtok(char *str, const char *delim);
char *d_space(char *str);
char **tokarr(char *str);
int _putchar(int c);
int _puts(char *str);

/* built-ins.c file */
void print_env(void);

/* environment.c */
char *_getenv(const char *name);

#endif /*_SIMPLE_SHELL_H_*/
