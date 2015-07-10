#ifndef SIMPLEGUI_H
#define SIMPLEGUI_H
#ifdef __gnu_linux__
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#endif
#include "Dirwalker.h"
#include <QPushButton>
#include <QApplication>
#include <QObject>
#include <QString>
#include <QTextBlock>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QDir>
#include <QThread>
#include <QProgressBar>
#include <stdio.h> //fro FILE/fprintf

#ifdef __gnu_linux__
typedef void* (*doIt)(void*);

#endif

void* doSomething2(void*);

class SimpleGUI : QObject {
    Q_OBJECT

public:
    SimpleGUI(QApplication* , int, char**);
    ~SimpleGUI();
    bool isActive;
    QWidget* getWindow();
private:
    void callDirwalk(void);
    void fillBar(int);
signals:
    void showWindow();
    void hideWindow();

private slots:
    void doSomething(void);
    void activate();
    void deactivate();
    void printDiagnostics();
private slots:
    /* new slots for dirWalker() */
    void printFiles();
    void deleteFiles();
    void xorFiles();
private:
    FILE* fp;
    SimpleGUI();
    SimpleGUI* self ;

    QApplication* qapp;
    QWidget* window;
    QPushButton *yes;
    QPushButton* crypt;
    QPushButton* deleteF;
    QPushButton *no;
    QTextEdit *text;
    QString textToAdd;
    QString fname;
    QProgressBar* progressBar;
public:
    static int argc;
    static char** argv;
    static SimpleGUI* emulatedGlobal;

private:
    int w;
    int h;
    unsigned long timeSleep;
    QHBoxLayout* align;
    QVBoxLayout* textLay ;
    QVBoxLayout *buttonsLay;
    QVBoxLayout* progressLay;
    QVBoxLayout* qvb;
    void* doSth(void*);

public:
    QProgressBar* getProgressBar();
    void showApp();
    void hideApp();
    void initTimeCounter(unsigned int);
};

#endif // SIMPLEGUI_H



