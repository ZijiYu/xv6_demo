#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

# define MSGSIZE 16

int main(int argc, char* argv[]){
    // 如何获取前一个命令的标准化输出（即此命令标准化输入）
    char buf[MSGSIZE];
    read(0, buf, MSGSIZE);

    // 如何获取此命令的命令行参数？
    char *xargv[argc];
    int xargc = 0;
    for(int i = 1; i < argc; i++){
        xargv[xargc] = argv[i];
        xargc++;
    }

    char *p = buf; // 给命令标准化输入增加一个指针
    for(int i = 0; i < MSGSIZE; i++){
        if(buf[i] == '\n'){// pipe 前会有一个换行符
            int pid = fork();
            if(!pid){// 父进程
            p = &buf[i+1]; // 指针进一位
            wait(0);
            }else{
                buf[i] = 0; // 抹除\n
                xargv[xargc] = p;
                xargc++;
                xargv[xargc] = 0;// 结尾用0结尾

                exec(xargv[0],xargv);
                exit(0);
            }
        }
    }
    wait(0);
    exit(0);


}