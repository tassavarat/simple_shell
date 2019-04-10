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
#include <errno.h>

/* Symbolic constants */
#define F_FLUSH -1

/* environmental variables */
extern char **environ;

/* strings_functions.c file */
char *_strtok(char *buffer, const char *delim);
int _strlen(char *str);
char **tokarr(char *buffer);
int _putchar(int c);
int _puts(char *str);

/* built-ins.c file */
void print_env(void);

/* environment.c */
char *_getenv(const char *name);
char *_append(char *s, char *token, char *buff);
char *get_path(char *s);
void evaluate_var(char **arr);

/* shell.c */
void _fork(char *buffer, char **arr, size_t count);
void _shell(void);
char *convert(unsigned int num, int base);
void signal_handler(int signum);

#endif /*_SIMPLE_SHELL_H_*/
