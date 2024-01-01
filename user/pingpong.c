#include "kernel/types.h"
#include "user/user.h"

int main(){
    int p[2];
    pipe(p);
    pid = fork();
    if(pid){
        // if(fork()) is equal to if(fork()>0)
        write(p[1],"ping\n",6);
        wait(0);
        printf("[Successfully Write]\n",getpid());
    }else{
        // else is equal to else if(fork()==0)
         read(p[0],"pong\n",6);
         wait(0);
         printf("[Successfully Read]\n",pid);
    }

    exit(0);
    
}