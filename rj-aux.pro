greaterThan(QT_MAJOR_VERSION, 4):

QT += widgets
QT += core
QT += gui
QT += network

TARGET = rj-aux
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
        src/main.cpp \
        src/mainwindow.cpp \
        src/loginwidget.cpp \
        src/showinfowidget.cpp \
        src/traywidget.cpp

HEADERS += \
        src/mainwindow.h \
        src/loginwidget.h \
        src/showinfowidget.h \
        src/traywidget.h \


CONFIG += link_pkgconfig

CONFIG += c++11

PKGCONFIG += dtkwidget

DISTFILES +=

RESOURCES += \
    image.qrc \

