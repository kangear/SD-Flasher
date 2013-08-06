#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include "datastruct.h"

void get_num(UPAN* upan)
{
    int size = usb_num;
    char* s = buffer;
    char* d = NULL;
	int i = 0;
    for(i=0; i<size; i++)
    {
    	d = upan[i].num;
    	while('\n' != *s) //第
    	{
    		*d++ = *s++;
    	}
    	*d = '\0';
    	s++;	
    	printf("size=%d\n", size);
    } 
    debug("%s\n", upan[0].num);
    debug("%s\n", upan[1].num);
}


void get_dev_nod(UPAN* upan)
{
	char command[512] = {0};
	FILE *pf = NULL;
	
	int size = 0;
	  
	sprintf(command, "ls /sys/class/scsi_device/%s:0:0:0/device/block/", upan->num);
	
	debug("%s\n", command);
	
    pf = popen(command, "r");
    
    size = fread(upan->nod_name, 1, sizeof(upan->nod_name), pf);
    
	debug("size = %u\n", size);
	
	upan->nod_name[size-1] = '\0';
	
	debug("nod_name = %s\n", upan->nod_name);
	
    sprintf(upan->dev_node, "/dev/%s", upan->nod_name);
    
    debug("dev_nod=%s\n", upan->dev_node);
 
    pclose(pf);

}

int scan(UPAN* upan)
{
	int i = 0;
    choose_num = -1;
    if(check_usb())
    {
        //upan = (UPAN*)realloc(upan, sizeof(UPAN)*usb_num);
        sleep(1);
        if (usb_num == 1)
            choose_num = 0;
    }
    else
        return 0;
	get_num(upan);
	for(i=0; i<usb_num; i++)
        get_dev_nod(upan+i);
    return 1;
}

