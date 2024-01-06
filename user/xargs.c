#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

# define MSGSIZE 32

int main(int argc, char* argv[]){
    //获取前一个命令的标准化输出（即此命令标准化输入）

    sleep(10);
    char buf[MSGSIZE];
    read(0, buf, MSGSIZE);

    // 获取此命令的命令行参数？
    char *xargv[argc];
    int xargc = 0;
    for(int i = 1; i < argc; i++){
        xargv[xargc] = argv[i];
        xargc++;
    }// xargc 的长度是argc-2

    char *p = buf;

    for(int i = 0; i < MSGSIZE; i++){
        if(buf[i] == '\n'){
            if(fork()){
                p = &buf[i+1];
                wait(0);
            }else{
                buf[i] = 0;
                xargv[xargc] = p;
                xargc++;
                xargv[xargc] = 0;
                exec(argv[1],xargv);
                exit(0);
            }
        }
    }
    exit(0);
}