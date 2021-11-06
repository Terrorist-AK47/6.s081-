#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
        int pfd[2];
        int cfd[2];
        int pid;
        char buff[1];
        if (argc != 1){
                fprintf(2, "pingpong: usage: pingpong\n", 26);
                exit(1);
        }
        pipe(pfd); 
        pipe(cfd); 
        if ((pid = fork()) == 0){
                close(pfd[1]);
                close(cfd[0]);
                if (read(pfd[0], buff, 1) == 1){
                        printf("%d: received ping\n", getpid());
                        write(cfd[1], buff, 1);
                        close(pfd[0]);
                        close(cfd[1]);
                        exit(0);
                }
        }
        else{
                close(pfd[0]);
                close(cfd[1]);
                write(pfd[1], buff, 1);
                wait(0);
                if (read(cfd[0], buff, 1) == 1){
                        printf("%d: received pong\n", getpid());
                        close(pfd[1]);
                        close(cfd[0]);
                        exit(0);
                }
        }
        return 0;       
}
