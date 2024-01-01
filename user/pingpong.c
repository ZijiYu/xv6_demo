#include "kernel/types.h"
#include "user/user.h"

int main(){
    int p[2];
    pipe(p);
    if(fork()){
        // if(fork()) is equal to if(fork()>0)
        write(p[1],"ping\n",6);
        printf("[Successfully Write\n]");
    }else{
        // else is equal to else if(fork()==0)
         read(p[0],"pong\n",6);
         printf("[Successfully Read\n]");
    }

    exit(0);
    
}