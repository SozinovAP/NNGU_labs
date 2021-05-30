QT       += core gui
QT       += qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += debug
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    autolevel.cpp \
    blackwhite.cpp \
    blur.cpp \
    brightness.cpp \
    emboss.cpp \
    filter.cpp \
    gaussblur.cpp \
    glowingedges.cpp \
    grayworld.cpp \
    inverse.cpp \
    main.cpp \
    mainwindow.cpp \
    mathmorphology.cpp \
    maximum.cpp \
    median.cpp \
    sepia.cpp \
    sharp.cpp \
    sobel.cpp \
    structelem.cpp \
    transfer.cpp \
    turn.cpp \
    wave1.cpp \
    wave2.cpp

HEADERS += \
    FilterLibrary.h \
    autolevel.h \
    blackwhite.h \
    blur.h \
    brightness.h \
    emboss.h \
    filter.h \
    gaussblur.h \
    glowingedges.h \
    grayword.h \
    inverse.h \
    mainwindow.h \
    mathmorphology.h \
    maximum.h \
    median.h \
    sepia.h \
    sharp.h \
    sobel.h \
    structelem.h \
    transfer.h \
    turn.h \
    wave1.h \
    wave2.h

FORMS += \
    mainwindow.ui \
    structelem.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
