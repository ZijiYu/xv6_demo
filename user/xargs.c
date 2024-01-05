#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

# define MSGSIZE 16

int main(int argc, char* argv[]){
    char *buf[MSGSIZE];
    int bytes_read = read(0, buf, MSGSIZE);

    printf("收到：%s\n",buf);
    if(bytes_read < 0){
        printf("读取错误\n");
        exit(1);
    }

    if(argc > 2){
        char *args[argc]; // 创建一个新的参数数组
        args[0] = argv[1]; // 第一个参数是命令
        for(int i = 2; i < argc; i++){
            args[i - 1] = argv[i]; // 拷贝其他参数
        }

        for(int i = 0; i < argc; i++){
            printf("args[%d]: %s",i,agrs[i]);
        }
        exec("echo", args);

        // 执行命令
        int tag = exec(argv[1], args);
        if(tag == -1){
            printf("执行错误\n");
            exit(1);
        }
    } else {
        printf("参数不足，无法执行命令。\n");
    }

    exec(argv[1],buf);
    exit(0);
}