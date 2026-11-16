#include "fylib.h"

char *fy_read_line(){
    char *buf;
    size_t buf_size;
    char cwd[KiB(1)];

    Getcwd(cwd, sizeof(cwd));
    buf = NULL;

    printf(C"%s\n"RESET, cwd);
    printf("󰣇 >>");

    if(getline(&buf, &buf_size, stdin) == -1){
        buf = NULL;
        if(feof(stdin)){
            printf(RED"[EOF]"RESET);
        }else{
            printf(RED"[ERROR]: GetLine failed"RESET);
        }
    }
    return buf;
}

int main(int argc, char **argv){
    //readline is better
    char *line;
    while(true){
        line = fy_read_line();
        printf("%s\n", line);
    }
    return EXIT_SUCCESS;
}
