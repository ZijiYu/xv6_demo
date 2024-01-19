#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

void main(){
int pid = fork();
if (!pid) {
    printf("this is child\n");
} else{
    printf("parent: I have a child=%d\n", pid);
    pid = wait((int *) 0);
    printf("child %d is done\n", pid);
}
exit(0);
}