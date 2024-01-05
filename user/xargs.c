#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

# define MSGSIZE 16

int main(int argc, char* argv[]){
    char buf[MSGSIZE];
    read(0, buf, MSGSIZE);
    printf("进程读取到的内容：%s",buf);

    for(int i = 0; i < argc, i++){
        printf("argv[%d]: %s",i,argv[i]);
    }
    exit(0);
}