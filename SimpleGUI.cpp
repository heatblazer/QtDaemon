extern "C"{
    #include "utils.h"
    #include "LOGFILES.h"
}

#include "SimpleGUI.h"
#include <stdio.h>
/* if in unix send the proc to separaet thread */
#ifdef __gnu_linux__
    #include <signal.h>
#elif _WIN32
    #include <windows.h>
#endif

SimpleGUI* SimpleGUI::emulatedGlobal=NULL;
int SimpleGUI::argc = 0;
char** SimpleGUI::argv = NULL;
SimpleGUI::~SimpleGUI() {

    Utils.writeToFile("App terminated\n", LOG_getLogName(OTHER), "a+");
    delete text;
    delete yes;
    delete deleteF;
    delete crypt;
    delete no;
    delete window;
}
SimpleGUI::SimpleGUI() { }

SimpleGUI::SimpleGUI(QApplication* app, int args, char** argvs)
    : qapp(app)
{
    isActive = true;
    window = new QWidget;
    yes = new QPushButton("Print files"); /*TODO - rename buttons yes/no */
    crypt = new QPushButton("Crypt files in dir");
    crypt->setEnabled(false);
    deleteF = new QPushButton("Delete files"); /* will be usable by default */
    no = new QPushButton("Cancel");
    progressBar =  new QProgressBar;
    progressBar->setRange(0, 10); //elements in list

    progressLay = new QVBoxLayout;
    progressLay->setAlignment(Qt::AlignCenter);
    buttonsLay = new QVBoxLayout;
    buttonsLay->setAlignment(Qt::AlignCenter);
    textLay = new QVBoxLayout;
    qvb =  new QVBoxLayout;
    align = new QHBoxLayout;
    int i=0;
    textToAdd.append("<p><b>The following dirs are selected:</b></p>");

    while ( i < args ) {
        textToAdd.append("<p>");
        textToAdd.append(argvs[i++]);
        textToAdd.append("</p>");
    }
    textToAdd.append("<p><b>Perform which operation?</b></p>");
    textToAdd.append("<p><b><font color='red'>Warning! Deleting files is ireversable!!!</font></b></p>");
    text = new QTextEdit(textToAdd);
    text->setReadOnly(true);
 //   text->setEnabled(false);
/*
    text->setMaximumHeight(200);
    text->setMaximumWidth(200);
    text->setMinimumHeight(200);
    text->setMinimumWidth(200);
*/
    window->setMinimumHeight(320);
    window->setMaximumHeight(320);
    window->setMinimumWidth(320);
    window->setMaximumWidth(320);

    yes->setMinimumWidth(200);
    yes->setMaximumWidth(200);
    no->setMinimumWidth(200);
    no->setMaximumWidth(200);

   // progressLay->addWidget(progressBar);
    textLay->addWidget(text);
    buttonsLay->addWidget(yes);
    buttonsLay->addWidget(deleteF);
    buttonsLay->addWidget(crypt);
    buttonsLay->addWidget(no);
    qvb->addLayout(textLay);
    //qvb->addLayout(progressLay);
    qvb->addLayout(buttonsLay);

    align->addLayout(qvb);
    window->setLayout(align);

    SimpleGUI::argc = args;
    SimpleGUI::argv = argvs;

  //  QObject::connect(yes, SIGNAL(clicked()),
  //                   window, SLOT(close()) );
    QObject::connect(yes, SIGNAL(clicked()),
                     this, SLOT(printFiles()) );

    QObject::connect(yes, SIGNAL(clicked()),
                     this, SLOT(deactivate()) );



    QObject::connect(deleteF, SIGNAL(clicked()),
                     this, SLOT(deleteFiles()) );

    QObject::connect(deleteF, SIGNAL(clicked()),
                     this, SLOT(deactivate()) );

  //  QObject::connect(crypt, SIGNAL(clicked()),
  //                   window, SLOT(close()) );
    QObject::connect(crypt, SIGNAL(clicked()),
                     this, SLOT(xorFiles()) );

    /* callDirwalk() is now a private function */

    /* not currently working */
    QObject::connect(this, SIGNAL(showWindow()),
                     window, SLOT(show()) );
    QObject::connect(this, SIGNAL(hideWindow()),
                     window, SLOT(hide()) );
    //[1] ok - stops daemon

    QObject::connect(no, SIGNAL(clicked()),
                     this, SLOT(deactivate()) );

  //  window->setAttribute(Qt::WA_ShowWithoutActivating);
    emulatedGlobal = this;
    window->show();

}

/* new Slots */
void SimpleGUI::deleteFiles() {
    setDirwalkerOptions(1);
    callDirwalk();
}
void SimpleGUI::printFiles() {
    setDirwalkerOptions(0);
    callDirwalk();

}

void SimpleGUI::xorFiles() {
    setDirwalkerOptions(2);
    callDirwalk();
    int i=0;
    while ( getListIndex() >= 0 ) {
        progressBar->setValue(i++);
    }

}

/* -------------------------------------------------- */
QWidget* SimpleGUI::getWindow() {
    return window;
}

void SimpleGUI::callDirwalk() {
    //thread main()
    /* does not work with clang compiler
     * use only GCC
     * */
   pthread_t t;
   int res = pthread_create(&t, NULL, doSomething2, NULL);

}

void SimpleGUI::activate() {

}
void SimpleGUI::deactivate() {
    delete this;
}
void SimpleGUI::printDiagnostics() {

}
void SimpleGUI::initTimeCounter(unsigned int t) {
    this->showApp();
}

void SimpleGUI::showApp() {
    if ( !window->isVisible() ) {
        emit showWindow();
    }
}
void SimpleGUI::hideApp() {
    if ( window->isVisible()) {
        emit hideWindow();
    }
}

void SimpleGUI::doSomething() {
   delete this;
//   QObject::connect(qapp, SIGNAL(aboutToQuit()),
 //                    qapp, SLOT(quit()) );
//

}

void* doSomething2(void* a) {

    Utils.writeToFile("Called init_dirWalk() on a separate thread\n",
                      LOG_getLogName(OTHER), "a+");
    init_dirWalk(SimpleGUI::emulatedGlobal, SimpleGUI::argc, SimpleGUI::argv);

}

QProgressBar* SimpleGUI::getProgressBar() {
    /* not working yet */
    return this->progressBar;
}

void SimpleGUI::fillBar(int v) {

}
