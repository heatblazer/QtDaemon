#ifndef SERVICE_H
#define SERVICE_H
#ifdef _WIN32
#include <windows.h>
#include <stdio.h>
#include "SimpleGUI.h"
#define SLEEP_TIME 1
#define LOG_FILE "Z:\\home\\ilian\\memtest.txt"
int WriteToLog(char* str);
void ControlHandler(DWORD request);
int ServiceMain(int argc, char** argv);
int InitService();
int mainO(int, char**);
int initQtAppWin32(SimpleGUI*, int, char**);
#endif
#endif // SERVICE_H
