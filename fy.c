#define FYLIB_ARENA_IMPLEMENTATION
#include "fylib.h"
#include "fyshell.h"
#include <sys/wait.h>

static t_builtin builtin[] ={
    {.builtin_name="echo", .foo=fy_echo},
    {.builtin_name="env", .foo=fy_env},
    {.builtin_name="exit", .foo=fy_exit},
    {.builtin_name="builtin", .foo=fy_builtin},
    {.builtin_name=NULL},
};
b32 status = 0;

i32 fy_builtin(char **args){
    (void)args;
    for(i32 i = 0; builtin[i].builtin_name ; i++){
        printf("%s\n", builtin[i].builtin_name);
    }
    return EXIT_SUCCESS;
}

void fy_launch(char **args){
   if(fork() == FY_PROC)
       execvp(args[0], args);
   else{
        wait(&status);
        if(WIFEXITED(status))
            status = WEXITSTATUS(status);
   }
}

char *fy_read_line(){
    char *buf;
    size_t buf_size;
    char cwd[KiB(1)];

    Getcwd(cwd, sizeof(cwd));
    buf = NULL;

    printf(C"%s\n"RESET, cwd);
    printf("󰣇 ❯");

    if(getline(&buf, &buf_size, stdin) == -1){ //getline do malloc by himself
        free(buf);
        buf = NULL;
        if(feof(stdin)){
            printf(RED"[EXIT]"RESET);
        }else{
            printf(RED"[ERROR]: GetLine failed"RESET);
        }
    }
    return buf;
}
#define DEL "\n\t \v\f\r"
char **fy_split_line(char *line, mem_arena *arena){
    char **tokens;
    tokens = arena_push(arena, sizeof(*tokens), false);
    i32 position = 0;

    for(char *token = strtok(line, DEL); token; token = strtok(NULL, DEL)){
        tokens[position++] = token;
        if(position == INT32_MAX){
           tokens = realloc(tokens, KiB(4) * sizeof(*tokens)); 
        }
    }

    tokens[position] = NULL;
    return tokens;
}
void fy_exec(char **args){
    int i = 0;
    const char *curr;
    while((curr = builtin[i].builtin_name)){
        if(!strcmp(curr, args[0])){
            builtin[i].foo(args);
            return;
        }
        i++;
    }
   fy_launch(args);
}

int main(void){
    mem_arena *arena = arena_create(KiB(4));
    char *line;
    char **args;
    Print_logo();
    while((line = fy_read_line())){
        args = fy_split_line(line, arena);

        fy_exec(args);
        free(line);
        arena_clear(arena);
    }
    arena_destroy(arena);
    return EXIT_SUCCESS;
}
