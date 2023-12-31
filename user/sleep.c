#include "kernel/types.h"
#include "user/user.h" //该头文件对kernel/types.h头文件有类型依赖，故要放在kernel/types.h之后。

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("no argument\n");
    } else if (argc > 2) {
        printf("Excessive argument\n");
    } else {
        int tag = 1;
        char *p = argv[1];
        while (*p) {
            if (*p < '0' || *p > '9') {
                tag = 0;
                break;
            }
            p++;
        }
        if (tag) {
            sleep(atoi(argv[1]));
        } else {
            printf("Illegal argument\n");
        }
    }
    exit(0);
}
