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

/**
 * struct arguments - Values to be accessed by various functions
 * @buf: String
 * @arr: Array of strings
 * @count: Command count
 */
typedef struct arguments
{
	char *buf;
	char **arr;
	int count;
} arguments_t;

/**
 * struct built-ins - Struct for built-ins
 * @bi: Name of built-ins
 * @f: Function pointer
 */
typedef struct built_ins
{
	char *bi;
	void (*f)(arguments_t args);
} built_ins_t;

/* strings_functions.c */
char *_strtok(char *buffer, const char *delim);
int _strlen(char *str);
char **tokarr(char *buffer);
int _putchar(int c);
int _puts(char *str);

/* string_functions2.c */
char *_memset(char *s, char b, unsigned int n);
char *_strcat(char *dest, char *src);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/* built-ins.c */
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
