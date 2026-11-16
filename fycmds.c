#include "fylib.h"

#include "fyshell.h"
i32 fy_exit(char **args){
    (void) args;
    cool_exit();
    exit(EXIT_SUCCESS);
}
i32 fy_env(char **args){
    extern char **environ;
    (void)args;
    if(!environ)
        return EXIT_FAILURE;
    for(int i = 0; environ[i]; i++){
        printf("%s\n", environ[i]);
    }
    return EXIT_SUCCESS;
}
i32 fy_echo(char **args){
    int start = 1;
    b32 new_line = true;
    
    if(!args || !args[0])
        return EXIT_FAILURE;
    if(args[1] && !strcmp(args[1], "-n")){
        new_line = false;
        start = 2;
    }
    for(int i = start; args[i]; i++){
        printf("%s", args[i]);
        if(args[i+1])
            printf(" ");
    }
    if(new_line)
        printf("\n");

    return EXIT_SUCCESS;
}
