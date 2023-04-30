#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include <stdlib.h>
#include "chown/chown.h"
#include "chmod/chmod.h"
#include "uname/uname.h"
#include "cat/cat.h"

int execute(int argc, char**);
char *parsecmd(int *argc, char**);
char *menu(int *argc, char**);

typedef struct command_t {const char* name; int (*fncptr)(int, char **);} command_t;
command_t commands[] = {
    {"chown", my_chown},
    {"chmod", my_chmod},
    {"uname", my_uname},
    {"cat", my_cat}
};

int main() {
    int argc;
    char **argv = malloc(100 * sizeof(char*));
    char *input = menu(&argc, argv);
    int ret = execute(argc, argv);
    free(argv);
    free(input);
    return ret;
}

int execute(int argc, char** argv) {
    char *command = argv[0];
    printf ("Running command [%s]\n", command);
    for (command_t *cmd = commands; cmd->name != NULL; cmd++) {
        if (strcmp(command, cmd->name) == 0) {
            return cmd->fncptr(argc, argv);
        }
    }
    printf("command not found: %s\n", command);
    return -1;
}

char *menu(int *argc, char** argv) {
    printf("You can use this program as an interpreter to call a command with all its arguments\n\n");
    printf("Available commands\n");
    printf("*chmod\n");
    printf("*uname\n");
    printf("*chown\n");
    printf("*cat\n");
    printf("\n");
    printf("command> ");
    return parsecmd(argc, argv);
}

char *parsecmd(int *argc, char** argv) {
    char *str = malloc(sizeof(char)*1024);
    fgets(str, 1024, stdin);
    const char s[3] = " \n";
    char *token;
    int i = 0;

    token = strtok(str, s);

    while( token != NULL) {
        argv[i] = token;
        i++;
        token = strtok(NULL, s);
    }

    *argc = i;

    return str;
}
