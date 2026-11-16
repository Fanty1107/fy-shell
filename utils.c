#include "fylib.h"
#include <stdio.h>

void Getcwd(char *buf, size_t size){
    if(NULL == getcwd(buf, size))
        perror(RED"[ERROR]: getcwd"RESET);
}
