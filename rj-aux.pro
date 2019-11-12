greaterThan(QT_MAJOR_VERSION, 4):

QT += widgets
QT += core
QT += gui
QT += network

TARGET = rj-aux
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += include/

SOURCES += \
        src/main.cpp \
        src/mainwindow.cpp \
        src/authwidget.cpp \
        src/showinfowidget.cpp \
        src/traywidget.cpp

HEADERS += \
        include/mainwindow.h \
        include/authwidget.h \
        include/showinfowidget.h \
        include/traywidget.h \


CONFIG += link_pkgconfig

CONFIG += c++11

PKGCONFIG += dtkwidget

DISTFILES +=

RESOURCES += \
    image.qrc \

