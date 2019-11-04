greaterThan(QT_MAJOR_VERSION, 4):

QT += widgets
QT += core
QT += gui
QT += network

TARGET = rj-aux
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        inputwidget.cpp \
        main.cpp \
        mainwindow.cpp \
        authwidget.cpp \
        memorywidget.cpp \
        netcardwidget.cpp \
        showinfowidget.cpp \
        traywidget.cpp

HEADERS  += \
        mainwindow.h \
        authwidget.h \
        memorywidget.h \
        netcardwidget.h \
        showinfowidget.h \
        traywidget.h \
        inputwidget.h

CONFIG += link_pkgconfig

CONFIG += c++11

PKGCONFIG += dtkwidget

DISTFILES +=

RESOURCES += \
    image.qrc \

