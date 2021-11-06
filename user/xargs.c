#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char **argv)
{
        if (argc < 2){
                fprintf(1, "xargs: usage: somecommand |xargs command\n");
                exit(0);
        }
        char *params[MAXARG];
        char buf[512];
        int index = 0;
        int n;

        for (int i = 1; i != argc; ++i){
                params[i-1] = argv[i];
        }
        while(1){
                index = 0;
                while((n = read(0, &buf[index], 1)) != 0){
                        if (buf[index] == '\n'){
                                buf[index] = 0;
                                break;
                        }
                        ++index;
                }
                if (n == 0)
                        break;
                params[argc - 1] = buf;
                if (fork() == 0){
                        exec(argv[1], params);
                }
                else{
                        wait(0);
                }
        }
        exit(0);
        return 0;
}
