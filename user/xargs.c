#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

# define MSGSIZE 64

int main(int argc, char* argv[]){
    //获取前一个命令的标准化输出（即此命令标准化输入）
    char *buf[MSGSIZE];
    read(0, buf, MSGSIZE);

    // 获取此命令的命令行参数？
    char *xargv[argc];
    int xargc = 0;
    for(int i = 1; i < argc; i++){
        xargv[xargc] = argv[i];
        xargc++;
    }// xargc 的长度是argc-2


    int j = 0;

    for(int i = 0; i < MSGSIZE; i++){
        if(buf[i] == '\n'){
            xargv[xargc] = buf;
            xargc++;
            xargv[xargc] = 0;
            if(fork()){
                wait(0);
            }else{
                exec(argv[1],xargv);
            }
        }
    }
    exit(0);


}