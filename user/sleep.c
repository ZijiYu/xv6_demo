#include "kernel/types.h"
#include "user/user.h"
int main(int argc, char *argv[]){
    if(argc<2){
        printf("[Empty Argument.\n]");
    }else if(argc>2){
        printf("[Excessive Arguement]\n");
    }else{
        int tag = 1;
        int *p = argv[1];
        while(*p){
            if(*p<'0' || *p>'9'){
                tag = 0;
                break;
            }
            p++;
        }
        if(tag){
            sleep(atoi(argv[1]));
        }else {
            printf("Illegal argument\n");
        }
    }
    exit(0);
}