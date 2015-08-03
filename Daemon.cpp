extern "C" {
    #include "utils.h"
    #include "LOGFILES.h"
}

#include <stdlib.h>
static char TMPFILE[] = "/tmp/SampleGameXXXXXX";
static char tmp[256]="\0";

#include "Daemon.h"
#include "DList.h"
#include "Dirwalker.h"
#include "SimpleGUI.h"
#define HOURS 4
#define SLEEP_TIME 3600 //3600 == 1 hour

#ifdef __gnu_linux__
    #include <signal.h>
    #include <sys/types.h>
    #include <sys/wait.h>

#define LINE50 "---------------------------------------------\n"
#define CHECK_VER1

static int tempFileDescriptor= -1;
static char tempFileName[256]="/tmp/SampleGame-XXXXXX";

static int Daemon_status=0;
static int dirWalk = 0;
static config CFG;
static DList* parentDirs = NULL;
static FILE* fileToWrite = NULL;
static FILE* fileToRead = NULL;
static char** ARGVS = NULL;
static int ARGC = 0;
static int isRunning = 0;
static QApplication* qapp = NULL;
pid_t child ;


static inline void signal_handler(int sig) {

    switch (sig)  {
    case SIGTERM:
        Utils.writeToFile("Recieved SIGTERM\n",
                          LOG_getLogName(OTHER), "a+");
        unlink(tempFileName);
        exit(0);

    case SIGKILL:
        Utils.writeToFile("Recieved SIGKILL\n",
                          LOG_getLogName(OTHER), "a+");
        unlink(tempFileName);
        exit(0);
    case SIGHUP:
        Utils.writeToFile("Recieved SIGHUP\n",
                          LOG_getLogName(OTHER), "a+");
        unlink(tempFileName);
        exit(0);
    default: break;
    }
}


/*----------------------------------------------------------------------*/

int getIsRunning() { return isRunning; }
void setIsRunning(int r) { isRunning = r; }

int pid;

void setDirwalk(int a) {
    dirWalk = a;
}

int getDirwalk() {
    return dirWalk;
}

int getARGC() {
    return ARGC;
}

char** getARGVS() {
    return ARGVS;
}

DList* getDaemonParentDirs() { return parentDirs; }

int readConfigFileAndReturnParameter(const char *filename) {
    FILE *fp = fopen(filename, "r");
    char buff[512]="";
    char c;
    int fnmres = 0;
    char* tested= NULL;
    while ( fgets(buff, 512, fp) ) {
        tested = Utils.strip(buff, ' ');
        tested = Utils.strip(tested, '\n');
        tested = Utils.strip(tested, '\t');
        if ( tested[0] == '/' && tested[strlen(tested)-1] == '/') {
            printf("#####%s\n", tested);
        }

    }
    fclose(fp);
}

int findFileInDir(char *basedir, char* pattern, int patlen, int recursive) {
    DIR* dir;
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
            sprintf(entpath, "%s%s\0", basedir, ent->d_name);
            if ( strncmp(entpath, pattern, patlen)== 0 ) {
                printf("### %s \n", entpath);
                return 1;
            }
            if ( isDir(entpath) ) {
                if ( recursive > 0) {
                  sprintf(entpath, "%s/\0", entpath);
                  findFileInDir(entpath, pattern, patlen, RECURSIVE);
                } else {/*none*/}
            } else {

            } //end if2
        } //end while
        closedir(dir);
        return 0;
    } else {
        return 0;
    }
}




#ifdef  __gnu_linux__
int init_daemon_main(int argc, char *argv[]) {

    /* UNIX system call to check for a temp file
     * poor man solution - optimize later
     * no lock to file also...
     * */

    /* test function passed -
     * TODO - move it to Utils. ...
     * */
/* BEGIN - Singleton code */

    if ( !findFileInDir("/tmp/", "/tmp/Sample", strlen("/tmp/Sample"), -1)) {
        tempFileDescriptor = mkstemp(tempFileName);
    } else {
        fprintf(stderr, "Only one instance is allowed.\n");
        exit(1);
    }

//    if ( system("ls -l /tmp/ | grep Sample") ) {
//        tempFileDescriptor = mkstemp(tempFileName);
//    } else {
//        fprintf(stderr, "Only one running instance is allowed\n");
//        exit(1);
//    }

/* END SINGLETON CODE */

    strncpy(tmp, TMPFILE, strlen(tmp));

    ARGVS = argv;
    ARGC = argc;
    LOG_setErr("/home/ilian/err_daemon");
    if ( argc < 1 || !argv[0]) {
        Utils.writeToFile("Error in init_daemon_main()\nNo parameters passed?\n",
                          LOG_getLogName(ERRORR), "w");
        return 1;
    }
    pid_t process_id = 0;
    pid_t sid;
    process_id = fork();
    if ( process_id < 0 ) {
        exit(0);
    }
    umask(0);
    if ( (sid = setsid()) < 0) exit(EXIT_FAILURE);
    chdir(argv[1]);
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    time_t startTime ;
    time_t endTime ;
    startTime =  endTime = time(NULL);
    setIsRunning(1);
    qapp = new QApplication(argc, argv);

    int counter = 0;

    int ftemp = mkstemp(tmp);

    Utils.writeToFile(tmp, LOG_getLogName(OTHER), "a+");


    do {
        /* add signal handler */
        signal(SIGTERM, signal_handler);
        signal(SIGHUP, signal_handler) ;
        signal(SIGKILL, signal_handler) ;

#ifdef DBG1

        while ( counter++ < (60) ) sleep(1);

#else
        while ( counter++ < (HOURS * SLEEP_TIME) ) {
            if ( counter % 300 == 0 ) {
                char buff[256]={0};
                sprintf(buff, "Daemon report: %d counter. OK\n", counter);
                FILE *fp = fopen(tempFileName, "a+");
                fprintf(fp, buff);
                fclose(fp);
            }
            sleep(1);
        }
#endif
        counter = 0;

        Daemon_status = initQtApp(NULL, argc, argv, 0);
        if ( Daemon_status != 0 )
            Utils.writeToFile("ERROR. Missing .so links? Please run \"ldd SampleGame\"",
                              LOG_getLogName(ERRORR), "a+");

   } while ( qapp->exec() == 0); //magic :S
   return 1;
}
#else
#endif

int initQtApp(SimpleGUI* sp, int argc, char* argv[], int flags) {

    SimpleGUI* spl = new SimpleGUI(qapp, argc, argv);
    if ( !spl) return 1;
    /* [OK] create function to get current date/time and use it
     * from Utils
     * */
    char buff[1024]="";
    strcat(buff,"App created on ");
    strcat(buff,Utils.getTimeString());
    Utils.writeToFile(buff, LOG_getLogName(OTHER), "a+");
    return 0;
}

void* threadApp(void*) {
    return 0x00;
}

int pthreadApp(SimpleGUI* spl, int argc, char** argv) {
    return 0;
}

pid_t forkApp(SimpleGUI *s, int argc, char **argv) {
    static int res ;
    res = fork();
    initQtApp(NULL, argc, argv, 0);
    return res;
}
#endif
