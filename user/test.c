#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

void main(){
int pid = fork();
int status
if (!pid) {
    printf("this is child\n");
} else{
    printf("parent: I have a child=%d\n", pid);
    wait(&status);
    printf("child status: %d \n", status);
}
exit(0);
}