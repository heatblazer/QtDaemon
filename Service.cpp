#ifdef _WIN32
#include "Service.h"
#include <stdio.h>
#include <windows.h>
SERVICE_STATUS ServiceStatus;
SERVICE_STATUS_HANDLE  hStatus;

int InitService() {
    int result = WriteToLog("Monitoring started.");
    return result;
}
int initQtAppWin32(SimpleGUI* spl, int argc, char* argv[]) {
    QApplication* app = new QApplication(argc, argv);
    spl = new SimpleGUI(app);
    return app->exec();
}
int WriteToLog(char *str) {
    FILE* fp;
    fp = fopen(LOG_FILE, "a");
    if ( ! fp) return -1;
    fprintf(fp, "%s\n", str);
    fclose(fp);
    return 0;
}


int ServiceMain(int argc, char *argv[])  {
    int error ;
    error = InitService();

    if ( error ) {
        ServiceStatus.dwCurrentState = SERVICE_STOPPED;
        ServiceStatus.dwWin32ExitCode = -1;
        SetServiceStatus(hStatus, &ServiceStatus);
        return 1;
    }
    ServiceStatus.dwCurrentState = SERVICE_RUNNING;
    SetServiceStatus(hStatus, &ServiceStatus);
    return 0;
}
int mainO(int argc, char** argv) {
    SERVICE_TABLE_ENTRY  ServiceTable[2];

    ServiceTable[0].lpServiceName = (wchar_t*) "SampleGame" ;
    ServiceTable[0].lpServiceProc = (LPSERVICE_MAIN_FUNCTION) ServiceMain ;
    ServiceTable[1].lpServiceName = NULL;
    ServiceTable[1].lpServiceProc = NULL;
    printf("%d is status LOG %s \n", StartServiceCtrlDispatcher(ServiceTable), LOG_FILE);
}
#endif
