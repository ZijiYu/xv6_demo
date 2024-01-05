#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

# define MSGSIZE 32

int main(int argc, char* argv[]){
    //获取前一个命令的标准化输出（即此命令标准化输入）
    char buf[MSGSIZE];
    read(0, buf, MSGSIZE);

    // 获取此命令的命令行参数？
    char *xargv[argc];
    int xargc = 0;
    for(int i = 1; i < argc; i++){
        xargv[xargc] = argv[i];
        xargc++;
    }// xargc 的长度是argc-2

    xargv[xargc-1] = malloc(512);

    int j = 0;

    for(int i = 0; i < MSGSIZE; i++){
        if(buf[i] == '\n'){
            xargc[argc] = 0; 
        }else{
            xargv[xargc][j] = buf[i];
            j++;
        }
    }

    exec(argv[1],xargv);

    
    wait(0);
    exit(0);


}