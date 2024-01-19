#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

void main(){
int pid = fork();
if (pid > 0) {
    printf("parent: child=%d\n", pid);\
    wait(0);
    pid = wait((int *) 0);
    printf("child %d is done\n", pid);
} else if (pid == 0) {
    printf("child: exiting\n");
    wait(0);
} else {
    printf("fork error\n");
}
exit(0);
}