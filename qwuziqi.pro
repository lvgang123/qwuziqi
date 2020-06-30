QT     += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    help/app.cpp \
    function/appinit.cpp \
    AI/aido.cpp \
    function/judgemodel.cpp \
    function/chess.cpp \
    help/qhelper.cpp \
    frmshow/show.cpp

HEADERS += \
    AI/chead.h \
    AI/aido.h \
    help/app.h \
    help/head.h \
    help/typedef.h \
    help/qhelper.h \
    function/appinit.h \
    function/judgemodel.h \
    function/chess.h \
    frmshow/show.h
