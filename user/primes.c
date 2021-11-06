#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void prime(int fd[]){
        int i, j;
        int pid;
        int cfd[2];
        close(fd[1]);
        if (read(fd[0], &i, 4) == 0){
                close(fd[0]);
                exit(0);
        }
        printf("prime %d\n", i);
        pipe(cfd);
        if ((pid = fork()) == 0){
                close(fd[0]);
                prime(cfd);
        }
        else {
                close(cfd[0]);
                while (read(fd[0], &j, 4) != 0){
                        if (j % i != 0)
                                write(cfd[1], &j, 4);
                }
                close(fd[0]);
                close(cfd[1]);
                wait(0);
        }
        exit(0);
}

int main(int argc, char **argv)
{
        if (argc != 1){
                fprintf(2, "primes: usage: primes\n");
                exit(1);
        }

        int fd[2];
        int pid;
        pipe(fd);

        if((pid = fork()) == 0)
                prime(fd);
        else{
                close(fd[0]);
                for (int i = 2; i <= 35; i++){
                        write(fd[1], &i, 4);
                }
                close(fd[1]);
                wait(0);
        }
        exit(0);
        return 0;
}
