#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

# define MSGSIZE 16

int main(int argc, char* argv[]){
    char buf[MSGSIZE];
    read(0, buf, MSGSIZE);
    
    // printf("进程读取到的内容：%s",buf);

    // for(int i = 0; i < argc; i++){
    //     printf("argv[%d]: %s \n",i,argv[i]);
    // }

    // echo bye | echo hello to


    for(int i = 2; i < argc; i++){
        exec(argv[1],*argv[i]);
    }
    exec(argv[1], *buf);
    exit(0);
}