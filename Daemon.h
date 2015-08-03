#ifndef DAEMON_H
#define DAEMON_H
#include <stdio.h>
#include <stdlib.h>
#ifdef __gnu_linux__

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <string.h>
#include "DList.h"
//#include "SimpleGUI.h"
#include "utils.h"
class SimpleGUI;
typedef struct config {
    unsigned int sleepTime;
    char* dirFile;
} config;

void setDirwalk(int a);
int getDirwalk();
int getARGC();
char** getARGVS();
void* initQt(void*);

DList* getDaemonParentDirs();
int initQtApp(SimpleGUI* spl,int argc,char* argv[], int);
int init_daemon_main(int argc, char* argv[]);
int readConfigFileAndReturnParameter(const char* filename);
int pthreadApp(SimpleGUI*, int, char**);
pid_t forkApp(SimpleGUI*, int, char**);
/*new*/int findFileInDir(char *basedir, char* pattern, int patlen, int recursive);
void* threadApp(void*);

int getIsRunning();
void setIsRunning(int);
#endif
#endif // DAEMON_H

