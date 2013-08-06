#include <stdio.h>
#include "datastruct.h"
#include "ui_dialog.h"
#include "dialog.h"

void fuse(UPAN* upan, const char* in_file, char *buf)
{
	char command[512] = {0};
	FILE *pf = NULL;
	int size = 0;
    if (choose_num >= 0)
    {
        sprintf(command, "export LANG=C ; sudo dd iflag=dsync oflag=dsync if=%s of=%s seek=1 2>&1", in_file, upan[choose_num].dev_node);

        debug("%s\n", command);

        pf = popen(command, "r");
    
        size = fread(buf, 1, 512, pf);

        qDebug("%d", size);

        pclose(pf);
    }
    else
    {
        sprintf(buf, "Please choose SD Card!");
    }
}
