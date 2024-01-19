#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

void main(){
    int pid = fork();
    if (pid > 0) {
        // 父进程
        printf("parent: I have a child=%d\n", pid);
        // 父进程先执行所需操作
        // ... 父进程的代码 ...

        // 等待子进程结束
        wait(0);
        printf("child %d is done\n", pid);
    } else if (pid == 0) {
        // 子进程
        // ... 子进程的代码 ...
        printf("this is child\n");
    } else {
        // fork失败
        printf("fork error\n");
    }
    exit(0);
}