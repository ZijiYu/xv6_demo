#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"
#include <stddef.h>

void main(){
int pid = fork();
if (!pid) {
    printf("this is child\n"); // this line
} else{
    printf("parent: I have a child=%d\n", pid);// this line
    wait(NULL);
    printf("child status: %d \n", pid);
}
exit(0);
}