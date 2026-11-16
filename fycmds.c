#include "fylib.h"

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
