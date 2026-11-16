#ifndef SHELL_H
#define SHELL_H

#include "fylib.h"
#define FY_PROC 0

typedef struct t_builtin t_builtin;

struct t_builtin{
    const char *builtin_name;
    i32 (*foo)(char **);
};

void Getcwd(char *b, size_t size);
void Print_logo();
i32 fy_exit(char **);
i32 fy_env(char **);
i32 fy_echo(char **);
i32 fy_builtin(char **);
void cool_exit();
#endif//SHELL_H
