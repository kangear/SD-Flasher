//sudo dd iflag=dsync oflag=dsync if=./BL1/BL1.bin of=/dev/sdb seek=1
#include "datastruct.h"
#include <malloc.h>
#include <stdlib.h>
#include <dirent.h>

char buffer[4096] = {0};
char usb_num = 0;
int choose_num = -1;
unsigned int sc[5] = {0};
UPAN* upan = NULL;

int check_usb(void)
{
	DIR *dir = NULL;
	FILE *pf = NULL;
	int ret = 0;
	int size = 0;
	char *p = buffer;
	usb_num = 0;
	if((dir = opendir("/proc/scsi/usb-storage")) != NULL)  //存储设备是插上了
	{	
		ret = 1;		
	    pf = popen("ls /proc/scsi/usb-storage/", "r");
	    size = fread(buffer, 1, sizeof(buffer), pf);	
	    while(size--)
	    {
	    	if(*p++ == '\n')
	    		usb_num ++;
	    }
	    printf("usb_num = %d\n", usb_num);
		closedir(dir);
	}
	else
	{
		ret = 0;
		printf("ERROR: Can't found SD Card!\n");	
	}
	return ret;	
}

int init(void)
{
    upan = (UPAN*)malloc(sizeof(UPAN)*5);
	return 0;	
}

