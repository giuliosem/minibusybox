#include <stdio.h>
#include "cat.h"



int main(int argc, char *argv[]) {


    char *cmd = argv[1];

    if (strcmp (cmd, "chmod") == 0){  
    }
    
    else if (strcmp (cmd, "cat") == 0){  
    	int error = my_cat(argc, &argv[2]);
    	if(error) return 1;
    }
        
    else 
    	printf("Command no recognaized\n");
    
    return 0;
}



