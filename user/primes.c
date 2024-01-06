#include "kernel/types.h"
#include "user/user.h"


# define MSGSIZE 4
#define RANGE 35

void get_prime(int receive, int send){// this two api become a pipe
    
    close(send);// no need for write 
    int n;
    int tag = read(receive,&n,MSGSIZE);// receive the first number from pipe
    if(tag == 0){// no number in the pipe
        close(receive);
        exit(0);
    }
    printf("prime %d\n",n);//read the first number from pipe and print it


    int p2[2];
    pipe(p2);
    int pid = fork();

    if(pid>0){
        int m;
        while(read(receive,&m,MSGSIZE)){
            if(m%n){
                write(p2[1],&m,MSGSIZE);
            }
        }
        close(receive);
        wait(0);
    }else if(pid == 0){
        get_prime(p2[0],p2[1]);
        close(p2[0]);
        close(p2[1]);
    }else{
        printf("[Fork Error]: %d/d\n",pid);
        exit(pid);
    }
    exit(0);
}

int main(){ 
    int p[2];
    pipe(p);
    int i;
    for(i =2; i <= RANGE; i++){
        write(p[1],&i,MSGSIZE); // the second argument is for location of the input number
    }
    get_prime(p[0],p[1]);
    exit(0);
}
