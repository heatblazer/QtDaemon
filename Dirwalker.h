#ifndef DIRWALKER_H
#define DIRWALKER_H
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include "DList.h"
#include "Daemon.h"
#define DIR_ONLY 1
#define RECURSIVE 1

#ifdef __gnu_linux__
#include <pthread.h>
#include <unistd.h>
pthread_t getPThreadFromDirwalker() ;
typedef struct ARGS {
    int* argc;
    char** argv;
} ARGS;
#endif


int isDir(const char *fname);
void walkDir(DList*, DList*, char *basedir, int recursive);
int init_dirWalk(SimpleGUI*, int, char** );
DList* getDirs();
DList* getFiles();

int getDirwalkerOptions();
void setDirwalkerOptions(int);
#endif // DIRWALKER_H
