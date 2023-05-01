#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <sys/stat.h>
#include "cat.h"
#define BUFFER_SIZE 1024

//////////////////////CAT///////////////////////////////////

int my_cat(int argc_s, char *argv_s[]){

	int flagError = 0;
	int file_desc, n;
	char buffer[BUFFER_SIZE];
	
	if (argc_s < 2) {			
	        printf("Error: please insert a PATH o file name\n");
		return(1);
	}
	    
	else if (argc_s > 2){
	    	printf("Warning: Only the first PATH will be printed\n\n"); 
	    	flagError = 1;    	
	}    
	file_desc = open(argv_s[0], O_RDONLY);
	if (file_desc < 0) {
		printf("Error opening file"); /////////// importante
		return(1);
	}
	while ((n = read(file_desc, buffer, BUFFER_SIZE)) > 0) {   	 

		if (write(STDOUT_FILENO, buffer, n) != n) {
			printf("Error writing to stdout");
		    	return(1);
		}      
	}
	if (n < 0) {
		//perror("Error reading file"); /////////// importante
		printf("Error "); /////////// importante
		return(1);
	}
	if(flagError == 1){
	    	printf("\n Warning: Only the first PATH was printed\n\n");
	}
	close(file_desc);
	return 0;
}
