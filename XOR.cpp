extern "C"{
#include "utils.h"
}
#include "XOR.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//static FILE* _fp;
//static FILE* _fileToWrite;
//static char* _pattern;

static int _filesize;
static char* _tempFileStream;


static FILE** _filesToCrypt ; /* the files array
                                FILE** is not FILE* []
                                */

void testWrite() {
    int f = Utils.getFileSize("C:\\Documents and Settings\\hmd.lk\\My Documents\\QT_PRO\\build-XOR-Desktop_Qt_5_3_0_MinGW_32bit-Debug\\debug\\testfile.txt", "rb");
    _tempFileStream = (char*) malloc(sizeof(char) * f);

    FILE* ftr = fopen("C:\\Documents and Settings\\hmd.lk\\My Documents\\QT_PRO\\build-XOR-Desktop_Qt_5_3_0_MinGW_32bit-Debug\\debug\\testfile.txt", "rb");
    char* bgn = _tempFileStream;
    while ( 1 ) {
        if ( feof(ftr) ) break;
        //writeToTMPFileStream(_tempFileStream, fgetc(ftr));
        *_tempFileStream++ = fgetc(ftr);
    }
    while ( *bgn ) {
        printf("%c", *bgn++);
    }
}
/*deprecated*/
void writeToTMPFileStream(char *fs, char c) {
    *fs++ = c;
}


void encrypt(const char* fname, const char *mode, char *pattern) {
    char* _pattern = pattern; //strdup(pattern);

    int len = strlen(_pattern);
    int i=0;
    char line[1024];
    char c;
    FILE* _fp = NULL;
    FILE* _fileToWrite= NULL;
    _fp =           fopen(fname, "rb");
    _fileToWrite =  fopen(mode, "wb");

    if ( ! _fp ) return ;
    if ( ! _fileToWrite ) return;

    while ( 1 ) {
        c = fgetc(_fp);
        if ( !feof(_fp)) {
            char crypt = c ^ _pattern[i%len];
            char decrypt = crypt ^ _pattern[i%len];
            fputc(crypt, _fileToWrite);
        } else {

            break;
        }
        i++;
    }
    fclose(_fp);
    fclose(_fileToWrite);
}


