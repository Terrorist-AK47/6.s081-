#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"


void find(const char *path, const char *fname){
        int fd;
        char buf[512], *p;
        struct dirent de;
        struct stat st;

        if ((fd = open(path, 0)) < 0){
                fprintf(2, "find: cannot open %s\n", path);
                return;
        }
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';
        while(read(fd, &de, sizeof(de)) == sizeof(de)){
                if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
                        continue;
                if (de.inum == 0)       //??
                        continue;
                memmove(p, de.name, DIRSIZ);
                p[DIRSIZ] = 0;
                if (stat(buf, &st) < 0){
                        fprintf(2, "find: cannot stat %s\n", buf);
                        return;
                }
                switch(st.type){
                case T_FILE:
                        if (strcmp(de.name, fname) == 0)
                                printf("%s\n", buf);
                        break;
                case T_DIR:
                        find(buf, fname);
                        break;
                }
        }
        close(fd);
        return;
}

int main(int argc, char **argv)
{
        if (argc != 3){
                fprintf(2, "find: usage: find [path] [file name]\n");
                exit(1);
        }
        find(argv[1], argv[2]);
        exit(0);
        return 0;
}
