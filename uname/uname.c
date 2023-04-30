#include <stdio.h>
#include <sys/utsname.h>
#include <string.h>


int my_uname(int argc, char **argv)
{
	struct utsname buffer;
	char err = 0; 
    err = (char)uname(&buffer);
	if(err < 0)
	{
		return 1;
	}
	else 
	{
		switch(argc){
			case 1:
				printf("system name: %s\n", buffer.sysname);
				printf("node name: %s\n", buffer.nodename);
				printf("release: %s\n", buffer.release);
				printf("version: %s\n", buffer.version);
				printf("machine: %s\n", buffer.machine);
				break;
			case 2:
				if(strcmp(argv[1], "-s") == 0)
				{
					printf("system name: %s\n", buffer.sysname);
				}
				else if(strcmp(argv[1], "-n") == 0)
				{
					printf("system name: %s\n", buffer.nodename);
				}
				else if(strcmp(argv[1], "-m") == 0)
				{
					printf("system name: %s\n", buffer.machine);
				}
				else
				{
					printf("command not supported or invalid \n");
				}
				break; 
			default: 
				printf("command not supported or invalid \n");
		}
	}
	return err; 
}