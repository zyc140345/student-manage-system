QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    insertsinglegradeormajororclass.cpp \
    insertsinglestu.cpp \
    insertsinglesubject.cpp \
    main.cpp \
    mainwindow.cpp \
    search.cpp \
    showsomething.cpp \
    studatabase.cpp

HEADERS += \
    dulinklist.h \
    insertsinglegradeormajororclass.h \
    insertsinglestu.h \
    insertsinglesubject.h \
    mainwindow.h \
    search.h \
    showsomething.h \
    studatabase.h

FORMS += \
    insertsinglegradeormajororclass.ui \
    insertsinglestu.ui \
    insertsinglesubject.ui \
    mainwindow.ui \
    search.ui \
    showsomething.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
