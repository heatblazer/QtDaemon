TEMPLATE = app
QT       += core gui

QT += widgets
greaterThan(QT_MAJOR_VERSION, 4):
unix {

    message("Using settigns for Unix")
    message("Current working dir: " $$PWD)


    INCLUDEPATH += /usr/include/libxml2/
    LIBS += -lxml2
    INCLUDEPATH +=  $$PWD/libutils/includes/
    LIBS +=         -L$$PWD/libutils/lib/unix/ -lutilz
}
win32 {
    message("*using settings for windows")
    message("Current working dir: " $$PWD)

    INCLUDEPATH += "Z:\\home\\ilian\\.wine\\drive_c\\Qt\\Qt5.3.1\\Tools\\mingw482_32\\i686-w64-mingw32\\include"
    LIBS += -L "Z:\\home\\ilian\\.wine\\drive_c\\Qt/Qt5.3.1\\Tools\\mingw482_32\\i686-w64-mingw32\\include\\windows.h" \
}


SOURCES += \
    Dirwalker.cpp \
    DList.cpp \
    Daemon.cpp \
    XOR.cpp \
    SimpleGUI.cpp \
    main.cpp \
    Service.cpp \
    xmltest.cpp

HEADERS += \
    LNode.h \
    DList.h \
    Dirwalker.h \
    Daemon.h \
    XOR.h \
    SimpleGUI.h \
    Service.h \
    xmltest.h

#RESOURCES += application.qrc
