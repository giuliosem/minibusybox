#include <stdio.h>
#include <sys/utsname.h>
#include <string.h>


int uname_cmd(const char * str)
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
		if(strcmp(str, "uname") == 0)
		{
			printf("system name: %s\n", buffer.sysname);
			printf("node name: %s\n", buffer.nodename);
			printf("release: %s\n", buffer.release);
			printf("version: %s\n", buffer.version);
			printf("machine: %s\n", buffer.machine);
		}
		else if(strcmp(str, "uname -s") == 0)
		{
			printf("system name: %s\n", buffer.sysname);
		}
		else if(strcmp(str, "uname -n") == 0)
		{
			printf("system name: %s\n", buffer.nodename);
		}
		else if(strcmp(str, "uname -m") == 0)
		{
			printf("system name: %s\n", buffer.machine);
		}
		else
		{
			printf("command not supported or invalid \n");
		}
	}

	return err; 
}

