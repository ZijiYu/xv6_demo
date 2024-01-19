#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

void main(){
int pid = fork();
if (pid > 0) {
    printf("parent: I have a child=%d\n", pid);
    pid = wait((int *) 0);
    printf("child %d is done\n", pid);
} else if (pid == 0) {
    wait(0);
    printf("this is child\n");
} else {
    printf("fork error\n");
}
exit(0);
}