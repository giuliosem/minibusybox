#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void usage() {
    printf("Wrong usage\n");
    printf("chown changes the user and/or group ownership of a file\n");
    printf("Usage: chown uid gid FILE\n");
    printf("Example: chown 1000 1000 /usr/bin/code\n");
}

int my_chown(int argc, char **argv) {
    if (argc != 4) {
        usage();
        return -1;
    }
    uid_t uid = atoi(argv[1]);
    if (uid == 0 && strcmp(argv[0], "0") != 0) {
        printf("UID not valid\n");
        return -1;
    }
    gid_t gid = atoi(argv[2]);
    if (gid == 0 && strcmp(argv[0], "0") != 0) {
        printf("GID not valid\n");
        return -1;
    }
    char *path = argv[3];
    if (chown(path, uid, gid) == -1) {
        char message[200];
        sprintf(message, "Error while trying to change owner of file [%s]", path);
        perror(message);
        return -1;
    } 
    printf("Success\n");
    
    return 0;
}