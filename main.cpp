extern "C" {
#include "utils.h"
#include "LOGFILES.h"
}

#include "Dirwalker.h"
#include "SimpleGUI.h"
#include "xmltest.h"

#ifdef __gnu_linux__
    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include "Daemon.h"
    #define HASH_TEST(STR) printf("%d = hash(%s)\n", hash(STR), STR);

/*adding single instance for linux 03.07.2015 */

int fdlock;
static int get_lock(void) ;



int main(int argc, char *argv[])
{
//   init_daemon_main(argc, argv);
   //readConfigFileAndReturnParameter("/home/ilian/ToBeFucked/testconf.txt");
   // printf("%s\n",strip("/home/user/ilian/", '/'));
   // printf("%s\n",unstrip("/home/user/ilian/", '/'));
    //copyOverwriteFile(argv[1], "abc123", 1); //ok on UNIX [1] do different on Win32
    //[1] 25.09.2014 - working test
  //  init_daemon_main(argc, argv);
    //[2] some gui testings
    //TODO - android deployment and test! Failed as for now...


    /* tests for toString() and elementsAsStrings() */
   /* [PASSED]
   DList* testXml = createList("test toString()");

   addFront("1234567890", testXml);
   addFront("1234567890", testXml);
   addFront("1234567890", testXml);

   addFront("1234567890", testXml);
   addFront("1234567890", testXml);
   addFront("1234567890", testXml);
   toString(testXml);
   elementsAsStrings(testXml);
   freeList(testXml);
   */

    if ( findFileInDir("/tmp/", "/tmp/Sample", strlen("/tmp/Sample"), -1)) {
        fprintf(stderr,"Error! Only one instance is allowed!\n");
        exit(1);
    }
    /* ELSE */
    LOG_setErr("/home/ilian/err");
    LOG_setNorm("/home/ilian/norm");
    LOG_setOther("/home/ilian/other");
    char* dirs[2] = {0,"/home/ilian/.directories.xml"};
    DList* xmlList = 0x00;

    if ( argc < 2 )  {
        xmlList =main_xml(1, dirs);
    } else  {
        xmlList = main_xml(argc, argv);
    }

    if ( !xmlList ) {
        Utils.writeToFile("ERROR. Format of XML file unsupported!\nRefer to <DirectoryEntry><directory /></DirectoryEntry>\n",
                          LOG_getLogName(ERRORR), "w");
        return 1;
    }
    printf("[toString()]: %s\n", toString(xmlList));
    char** passToDaemonArgvs = elementsAsStrings(xmlList);
    int passToDaemonArgc = getElementsInList(xmlList);
    if ( init_daemon_main(passToDaemonArgc, passToDaemonArgvs) != 0 ) {
        LOG_setErr("/home/ilian/main_err");
        Utils.writeToFile("Daemon main.cpp failed\n",
                          LOG_getLogName(ERRORR), "w");

        /* TODO - test to free the memory ]
        while ( *passToDaemonArgc++ ) {
            free(*passToDaemonArgc);
        }
        [*/
        return 1;
    } else {
        Utils.writeToFile("init_daemon_main() started\n",
                          LOG_getLogName(OTHER), "a+");
    }

}


static int get_lock(void) {
    struct flock fl;
    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 1;

    if ( (fdlock = open("SampleGame.proc",
                        O_WRONLY | O_CREAT, 0666)) < 0 ) {
      return 0;
    }
    if ( fcntl(fdlock, F_SETLK, &fl) < 0 ) {
        return 0;
    }
    /* else  */
    return 1;
}


#else
    #include "Service.h"

    int main(int argc, char *argv[]) {
        printf("Not on UNIX OS\n");
        //return mainO(argc, argv);
    }

#endif



