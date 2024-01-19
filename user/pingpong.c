#include "kernel/types.h"
#include "user/user.h"

int main(){
    int p[2];
    pipe(p);
    int pid = fork();
    if(pid){
        // if(fork()) is equal to if(fork()>0)
        write(p[1],"ping\n",6);
        wait(0);
        printf("[received: %s pid:%d]\n",p[0], getpid());
    }else{
        // else is equal to else if(fork()==0)
         read(p[0],"pong\n",6);
         wait(0);
         printf("[received: %s pid: %d]\n"p[1],pid);
    }

    exit(0);
    
}