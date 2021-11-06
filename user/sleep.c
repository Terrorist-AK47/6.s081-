#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
        int i;
        const char *str = "sleep: usage: sleep [integer]\n";
        if (argc != 2){
                write(1, str, strlen(str));
                exit(0);
        }
        i = atoi(argv[1]);
        sleep(i);
        exit(0);
        return 0;
}
