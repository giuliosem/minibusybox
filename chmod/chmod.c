#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <sys/utsname.h>
#include <regex.h>

int my_chmod(int argc, char *argv[]){
    // Compile the regex
    regex_t regex;
    int status = regcomp(&regex, "[ugoa]*([-+=]([rwxXst]*|[ugo]))+|[-+=]*[0-7]", REG_EXTENDED);
    
    if (status != 0) {
        char error_message[100];
        regerror(status, &regex, error_message, sizeof(error_message));
        printf("Regex error: %s\n", error_message);
        return 1;
    }

    // Check if the permissions argument matches the regex
    status = regexec(&regex, argv[1], 0, NULL, 0);
    if (status != 0) {
        printf("Invalid permissions format. %s\n",argv[1]);
        return 1;
    }

    struct stat st;
    if (stat(argv[2], &st) != 0) {
        perror("stat");
        return 1;
    }
    // Set the default mode
    mode_t permissions = st.st_mode;

    // Parse the permissions string
    int i = 0;
    int isNumeric  = 0;

    while (i < strlen(argv[1])) {
        switch (argv[1][i]) {
            case 'u':
                i++;
                switch (argv[1][i]){
                    case '+':
                        i++;
                        while (i < strlen(argv[1])) {
                            switch (argv[1][i]) {
                                case 'r':
                                    permissions |= S_IRUSR;
                                    break;
                                case 'w':
                                    permissions |= S_IWUSR;
                                    break;
                                case 'x':
                                    permissions |= S_IXUSR;
                                    break;
                                case 'X':
                                    if (S_ISDIR(st.st_mode) || (st.st_mode & S_IXUSR)) {
                                        permissions |= S_IXUSR;
                                    }
                                    break;
                                case 's':
                                    permissions |= S_ISUID | S_ISGID;
                                    break;
                                case 't':
                                    permissions |= S_ISVTX;
                                    break;
                                default:
                                    fprintf(stderr, "Invalid permission: +%c\n", argv[1][i]);
                                    return 1;
                            }
                            i++;
                        }
                        break;
                    case '-':
                        i++;
                        while (i < strlen(argv[1])) {
                            switch (argv[1][i]) {
                                case 'r':
                                    permissions &= ~(S_IRUSR);
                                    break;
                                case 'w':
                                    permissions &= ~(S_IWUSR);
                                    break;
                                case 'x':
                                    permissions &= ~(S_IXUSR);
                                    break;
                                case 'X':
                                    if (S_ISDIR(st.st_mode) || (st.st_mode & S_IXUSR)) {
                                        permissions &= ~(S_IXUSR);
                                    }
                                    break;
                                case 's':
                                    permissions &= ~(S_ISUID | S_ISGID);
                                    break;
                                case 't':
                                    permissions &= ~S_ISVTX;
                                    break;
                                default:
                                    fprintf(stderr, "Invalid permission: -%c\n", argv[1][i]);
                                    return 1;
                            }
                            i++;
                        }
                        break;
                    case '=':
                        i++;
                        permissions = 0;
                        while (i < strlen(argv[1])) {
                            switch (argv[1][i]) {
                                case 'r':
                                    permissions |= S_IRUSR | S_IRGRP | S_IROTH;
                                    break;
                                case 'w':
                                    permissions |= S_IWUSR | S_IWGRP | S_IWOTH;
                                    break;
                                case 'x':
                                    permissions |= S_IXUSR | S_IXGRP | S_IXOTH;
                                    break;
                                case 'X':
                                    if (S_ISDIR(st.st_mode) || (st.st_mode & S_IXUSR)) {
                                        permissions |= S_IXUSR | S_IXGRP | S_IXOTH;
                                    }
                                    break;
                                case 's':
                                    permissions |= S_ISUID | S_ISGID;
                                    break;
                                case 't':
                                    permissions |= S_ISVTX;
                                    break;
                                default:
                                    fprintf(stderr, "Invalid permission: =%c\n", argv[1][i]);
                                    return 1;
                            }
                            i++;
                        }
                        break;
                    default:
                        fprintf(stderr, "Invalid permission specifier: %c\n", argv[1][i]);
                        return 1;
                }
                break;
            case 'g':
                i++;
                switch (argv[1][i]){
                    case '+':
                        i++;
                        while (i < strlen(argv[1])) {
                            switch (argv[1][i]) {
                                case 'r':
                                    permissions |= S_IRGRP;
                                    break;
                                case 'w':
                                    permissions |= S_IWGRP;
                                    break;
                                case 'x':
                                    permissions |= S_IXGRP;
                                    break;
                                case 'X':
                                    if (S_ISDIR(st.st_mode) || (st.st_mode & S_IXUSR)) {
                                        permissions |= S_IXGRP;
                                    }
                                    break;
                                case 's':
                                    permissions |= S_ISUID | S_ISGID;
                                    break;
                                case 't':
                                    permissions |= S_ISVTX;
                                    break;
                                default:
                                    fprintf(stderr, "Invalid permission: +%c\n", argv[1][i]);
                                    return 1;
                            }
                            i++;
                        }
                        break;
                    case '-':
                        i++;
                        while (i < strlen(argv[1])) {
                            switch (argv[1][i]) {
                                case 'r':
                                    permissions &= ~(S_IRGRP);
                                    break;
                                case 'w':
                                    permissions &= ~(S_IWGRP);
                                    break;
                                case 'x':
                                    permissions &= ~(S_IXGRP);
                                    break;
                                case 'X':
                                    if (S_ISDIR(st.st_mode) || (st.st_mode & S_IXUSR)) {
                                        permissions &= ~(S_IXGRP);
                                    }
                                    break;
                                case 's':
                                    permissions &= ~(S_ISUID | S_ISGID);
                                    break;
                                case 't':
                                    permissions &= ~S_ISVTX;
                                    break;
                                default:
                                    fprintf(stderr, "Invalid permission: -%c\n", argv[1][i]);
                                    return 1;
                            }
                            i++;
                        }
                        break;
                    case '=':
                        i++;
                        permissions = 0;
                        while (i < strlen(argv[1])) {
                            switch (argv[1][i]) {
                                case 'r':
                                    permissions |= S_IRUSR | S_IRGRP | S_IROTH;
                                    break;
                                case 'w':
                                    permissions |= S_IWUSR | S_IWGRP | S_IWOTH;
                                    break;
                                case 'x':
                                    permissions |= S_IXUSR | S_IXGRP | S_IXOTH;
                                    break;
                                case 'X':
                                    if (S_ISDIR(st.st_mode) || (st.st_mode & S_IXUSR)) {
                                        permissions |= S_IXUSR | S_IXGRP | S_IXOTH;
                                    }
                                    break;
                                case 's':
                                    permissions |= S_ISUID | S_ISGID;
                                    break;
                                case 't':
                                    permissions |= S_ISVTX;
                                    break;
                                default:
                                    fprintf(stderr, "Invalid permission: =%c\n", argv[1][i]);
                                    return 1;
                            }
                            i++;
                        }
                        break;
                    default:
                        fprintf(stderr, "Invalid permission specifier: %c\n", argv[1][i]);
                        return 1;
                }
                break;
            case 'o':
                i++;
                switch (argv[1][i]){
                    case '+':
                        i++;
                        while (i < strlen(argv[1])) {
                            switch (argv[1][i]) {
                                case 'r':
                                    permissions |= S_IROTH;
                                    break;
                                case 'w':
                                    permissions |=  S_IWOTH;
                                    break;
                                case 'x':
                                    permissions |=  S_IXOTH;
                                    break;
                                case 'X':
                                    if (S_ISDIR(st.st_mode) || (st.st_mode & S_IXUSR)) {
                                        permissions |= S_IXOTH;
                                    }
                                    break;
                                case 's':
                                    permissions |= S_ISUID | S_ISGID;
                                    break;
                                case 't':
                                    permissions |= S_ISVTX;
                                    break;
                                default:
                                    fprintf(stderr, "Invalid permission: +%c\n", argv[1][i]);
                                    return 1;
                            }
                            i++;
                        }
                        break;
                    case '-':
                        i++;
                        while (i < strlen(argv[1])) {
                            switch (argv[1][i]) {
                                case 'r':
                                    permissions &= ~(S_IROTH);
                                    break;
                                case 'w':
                                    permissions &= ~(S_IWOTH);
                                    break;
                                case 'x':
                                    permissions &= ~(S_IXOTH);
                                    break;
                                case 'X':
                                    if (S_ISDIR(st.st_mode) || (st.st_mode & S_IXUSR)) {
                                        permissions &= ~(S_IXOTH);
                                    }
                                    break;
                                case 's':
                                    permissions &= ~(S_ISUID | S_ISGID);
                                    break;
                                case 't':
                                    permissions &= ~S_ISVTX;
                                    break;
                                default:
                                    fprintf(stderr, "Invalid permission: -%c\n", argv[1][i]);
                                    return 1;
                            }
                            i++;
                        }
                        break;
                    case '=':
                        i++;
                        permissions = 0;
                        while (i < strlen(argv[1])) {
                            switch (argv[1][i]) {
                                case 'r':
                                    permissions |= S_IRUSR | S_IRGRP | S_IROTH;
                                    break;
                                case 'w':
                                    permissions |= S_IWUSR | S_IWGRP | S_IWOTH;
                                    break;
                                case 'x':
                                    permissions |= S_IXUSR | S_IXGRP | S_IXOTH;
                                    break;
                                case 'X':
                                    if (S_ISDIR(st.st_mode) || (st.st_mode & S_IXUSR)) {
                                        permissions |= S_IXUSR | S_IXGRP | S_IXOTH;
                                    }
                                    break;
                                case 's':
                                    permissions |= S_ISUID | S_ISGID;
                                    break;
                                case 't':
                                    permissions |= S_ISVTX;
                                    break;
                                default:
                                    fprintf(stderr, "Invalid permission: =%c\n", argv[1][i]);
                                    return 1;
                            }
                            i++;
                        }
                        break;
                    default:
                        fprintf(stderr, "Invalid permission specifier: %c\n", argv[1][i]);
                        return 1;
                }
                break;
            case 'a':
                i++;
                switch (argv[1][i]){
                    case '+':
                        i++;
                        while (i < strlen(argv[1])) {
                            switch (argv[1][i]) {
                                case 'r':
                                    permissions |= S_IRUSR | S_IRGRP | S_IROTH;
                                    break;
                                case 'w':
                                    permissions |= S_IWUSR | S_IWGRP | S_IWOTH;
                                    break;
                                case 'x':
                                    permissions |= S_IXUSR | S_IXGRP | S_IXOTH;
                                    break;
                                case 'X':
                                    if (S_ISDIR(st.st_mode) || (st.st_mode & S_IXUSR)) {
                                        permissions |= S_IXUSR | S_IXGRP | S_IXOTH;
                                    }
                                    break;
                                case 's':
                                    permissions |= S_ISUID | S_ISGID;
                                    break;
                                case 't':
                                    permissions |= S_ISVTX;
                                    break;
                                default:
                                    fprintf(stderr, "Invalid permission: +%c\n", argv[1][i]);
                                    return 1;
                            }
                            i++;
                        }
                        break;
                    case '-':
                        i++;
                        while (i < strlen(argv[1])) {
                            switch (argv[1][i]) {
                                case 'r':
                                    permissions &= ~(S_IRUSR | S_IRGRP | S_IROTH);
                                    break;
                                case 'w':
                                    permissions &= ~(S_IWUSR | S_IWGRP | S_IWOTH);
                                    break;
                                case 'x':
                                    permissions &= ~(S_IXUSR | S_IXGRP | S_IXOTH);
                                    break;
                                case 'X':
                                    if (S_ISDIR(st.st_mode) || (st.st_mode & S_IXUSR)) {
                                        permissions &= ~(S_IXUSR | S_IXGRP | S_IXOTH);
                                    }
                                    break;
                                case 's':
                                    permissions &= ~(S_ISUID | S_ISGID);
                                    break;
                                case 't':
                                    permissions &= ~S_ISVTX;
                                    break;
                                default:
                                    fprintf(stderr, "Invalid permission: -%c\n", argv[1][i]);
                                    return 1;
                            }
                            i++;
                        }
                        break;
                    case '=':
                        i++;
                        permissions = 0;
                        while (i < strlen(argv[1])) {
                            switch (argv[1][i]) {
                                case 'r':
                                    permissions |= S_IRUSR | S_IRGRP | S_IROTH;
                                    break;
                                case 'w':
                                    permissions |= S_IWUSR | S_IWGRP | S_IWOTH;
                                    break;
                                case 'x':
                                    permissions |= S_IXUSR | S_IXGRP | S_IXOTH;
                                    break;
                                case 'X':
                                    if (S_ISDIR(st.st_mode) || (st.st_mode & S_IXUSR)) {
                                        permissions |= S_IXUSR | S_IXGRP | S_IXOTH;
                                    }
                                    break;
                                case 's':
                                    permissions |= S_ISUID | S_ISGID;
                                    break;
                                case 't':
                                    permissions |= S_ISVTX;
                                    break;
                                default:
                                    fprintf(stderr, "Invalid permission: =%c\n", argv[1][i]);
                                    return 1;
                            }
                            i++;
                        }
                        break;
                    default:
                        fprintf(stderr, "Invalid permission specifier: %c\n", argv[1][i]);
                        return 1;
                }
                break;
            case '+':
                i++;
                while (i < strlen(argv[1])) {
                    switch (argv[1][i]) {
                        case 'r':
                            permissions |= S_IRUSR | S_IRGRP | S_IROTH;
                            break;
                        case 'w':
                            permissions |= S_IWUSR | S_IWGRP | S_IWOTH;
                            break;
                        case 'x':
                            permissions |= S_IXUSR | S_IXGRP | S_IXOTH;
                            break;
                        case 'X':
                            if (S_ISDIR(st.st_mode) || (st.st_mode & S_IXUSR)) {
                                permissions |= S_IXUSR | S_IXGRP | S_IXOTH;
                            }
                            break;
                        case 's':
                            permissions |= S_ISUID | S_ISGID;
                            break;
                        case 't':
                            permissions |= S_ISVTX;
                            break;
                        default:
                            fprintf(stderr, "Invalid permission: +%c\n", argv[1][i]);
                            return 1;
                    }
                    i++;
                }
                break;
            case '-':
                i++;
                while (i < strlen(argv[1])) {
                    switch (argv[1][i]) {
                        case 'r':
                            permissions &= ~(S_IRUSR | S_IRGRP | S_IROTH);
                            break;
                        case 'w':
                            permissions &= ~(S_IWUSR | S_IWGRP | S_IWOTH);
                            break;
                        case 'x':
                            permissions &= ~(S_IXUSR | S_IXGRP | S_IXOTH);
                            break;
                        case 'X':
                            if (S_ISDIR(st.st_mode) || (st.st_mode & S_IXUSR)) {
                                permissions &= ~(S_IXUSR | S_IXGRP | S_IXOTH);
                            }
                            break;
                        case 's':
                            permissions &= ~(S_ISUID | S_ISGID);
                            break;
                        case 't':
                            permissions &= ~S_ISVTX;
                            break;
                        default:
                            fprintf(stderr, "Invalid permission: -%c\n", argv[1][i]);
                            return 1;
                    }
                    i++;
                }
                break;
            case '=':
                i++;
                permissions = 0;
                while (i < strlen(argv[1])) {
                    switch (argv[1][i]) {
                        case 'r':
                            permissions |= S_IRUSR | S_IRGRP | S_IROTH;
                            break;
                        case 'w':
                            permissions |= S_IWUSR | S_IWGRP | S_IWOTH;
                            break;
                        case 'x':
                            permissions |= S_IXUSR | S_IXGRP | S_IXOTH;
                            break;
                        case 'X':
                            if (S_ISDIR(st.st_mode) || (st.st_mode & S_IXUSR)) {
                                permissions |= S_IXUSR | S_IXGRP | S_IXOTH;
                            }
                            break;
                        case 's':
                            permissions |= S_ISUID | S_ISGID;
                            break;
                        case 't':
                            permissions |= S_ISVTX;
                            break;
                        default:
                            fprintf(stderr, "Invalid permission: =%c\n", argv[1][i]);
                            return 1;
                    }
                    i++;
                }
                break;
            default:
                if (argv[1][i] >= '0' && argv[1][i] <= '7'){
                    isNumeric = 1;
                    break;  
                }
                fprintf(stderr, "Invalid permission specifier: %c\n", argv[1][i]);
                return 1;
        }
        i++;
    } 
    
    
    if(isNumeric){
        // Convert the permissions string to an integer
        permissions = strtol(argv[1], NULL, 8);
    }

    
    int result = chmod(argv[2], (permissions));
    if (result == -1) {
        perror("chmod");
        return 1;
    }

    printf("Mod changed.\n");

    // Free the memory used by the regex
    regfree(&regex);

    return 0;
}