extern "C" {
    #include "utils.h"
    #include "LOGFILES.h"
}
#include "Dirwalker.h"
#include "Daemon.h"
#include "DList.h"
#include "XOR.h"
#include "xmltest.h"

#define DEBUG 1
#define LINE_BIG "-----------------------------------------------------------------------------------\n"
typedef void (*_univDo)(DList*, char*, int);
 /*[0] - print to
 * [1] - delete files/dirs
 * [2] - XOR crypt
 * */

static int __options= 0;
int getDirwalkerOptions() { return __options; }
void setDirwalkerOptions(int o) { __options = o; }

//comment here before real program
// This will go as separate foo in
// the qt class from DirWalker program
//[]
////////////////////////////////////////////////////////////////////////////////////
/* I M P O R T A N T ----- C O D E */
int init_dirWalk(SimpleGUI* spl, int argc, char** argv) {
    Utils.writeToFile("Started init_dirWalk()\n",
                     LOG_getLogName(OTHER), "a+");

    DList* dirs = createList("Directories");
    DList* files = createList("Files");
    //BUG sprintf(); sprintf causes a bug with memory here! Never call it!
 //   DList *xmlref = main_xml(argc, argv);
 //   forEach(xmlref, printFileFromList);
 //   freeList(xmlref);
/*********************************************************************/
    int i=1;
    while ( i < argc ) {
        walkDir(dirs, files, argv[i++], RECURSIVE);
    }
    /* [1] printFileFromList - pritns files to a file in home dir
     * [2] unlinkFile - deletes from top to bottom files, then dirs - now works with Win32
     * [3] cryptFileAndWriteBack - works for unix os - in utils.h
     * */
  //  copyOverwriteFileWithCryptOption(argv[1], "abc123", 1);
    switch ( __options ) {
    case 0: printList(dirs); printList(files); break;
    case 1: forEach(files, unlinkFile); forEach(dirs, unlinkFile); break;
        /*[1] important test of forEachVer2 */
    case 2: forEach(files, cryptFileAndWriteBack); break;
//[not working]    case 2: forEach(files, cryptFileAndWriteBack); break;
    default: break;
    }
    freeList(files); //empty lists
    freeList(dirs);
    free(files); free(dirs);
  //  setDirwalk(0); //[1] comunnicate with Daemon

}

////////////////////////////////////////////////////////////////////////////////////////

int isDir(const char *fname) {
    struct stat s;
    stat(fname, &s);
    return S_ISDIR(s.st_mode);
}

void walkDir(DList *dlist, DList* flist, char *basedir, int recursive) {
    DIR* dir;
    //char buff[512];
    struct dirent* ent;
    dir = opendir(basedir);
/* K&R - Приложение за  UNIX - обхождане на директории */
    if ( dir != NULL ) {
        //fprintf(filename, "\n\t Walking %s \t\n", basedir);
        while ( ent = readdir(dir ) ) {
            if ( (strcmp(ent->d_name, ".") == 0)
                 ||
                 (strcmp(ent->d_name, ".."))==0 ) {
                continue;
            } //endif 1
            char entpath[1024] = "";
           // strcat(entpath, basedir);
           // strcat(entpath, ent->d_name);
            sprintf(entpath, "%s%s\0", basedir, ent->d_name);
           /* will try using a list */
            if ( isDir(entpath) ) {
              //added recursive option
                if ( recursive > 0) {
                //  strcat(entpath, "/");
                  sprintf(entpath, "%s/\0", entpath);
                  addFront(entpath, dlist);
                  setListIndex(getListIndex()+1);
                  walkDir(dlist, flist, entpath, RECURSIVE);
                }
            } else {
                addFront(entpath, flist);
            } //end if2
        } //end while
        closedir(dir);
    } else {
        fprintf(stderr, "\nFailed to walk directory \%s \n", basedir);
        if ( DEBUG ) {
            perror("opendir()");
        }
    } //eindif0
}
