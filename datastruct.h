#ifndef _DATASTRUCT_H_
#define _DATASTRUCT_H_
#include <string.h>
#include <qdebug.h>
#define DEBUG
#ifdef	DEBUG
#define debug(fmt,args...)	qDebug (fmt ,##args)
#define debugX(level,fmt,args...) if (DEBUG>=level) printf(fmt,##args);
#else
#define debug(fmt,args...)
#define debugX(level,fmt,args...)
#endif	/* DEBUG */
typedef struct _tag_UPAN
{
    char num[5];        //"19"
    char nod_name[4];   //"sdb"
    char dev_node[512];  //"/dev/sdb"

}UPAN;

extern char buffer[4096];
extern char usb_num;
extern int choose_num;
extern unsigned int sc[5];
extern int scan(UPAN* upan);
extern int init(void);
extern void fuse(UPAN* upan, const char *in_file, char *buf);
extern int check_usb(void);


extern UPAN* upan;





#endif
