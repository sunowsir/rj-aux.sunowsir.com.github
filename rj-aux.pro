greaterThan(QT_MAJOR_VERSION, 4):

QT += widgets
QT += core
QT += gui
QT += network
QT += dbus

TARGET = rj-aux
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
	src/main.cpp \
	src/mainwindow.cpp \
	src/loginwidget.cpp \
	src/traywidget.cpp \
	src/showinfowidget.cpp \

HEADERS += \
	src/mainwindow.h \
	src/loginwidget.h \
	src/traywidget.h \
	src/showinfowidget.h \

CONFIG += link_pkgconfig c++11 console app_bundle

LIBS += $$PWD/libQt5Quazip.so.1

INCLUDEPATH += $$PWD/src/

RESOURCES += \
    image.qrc \


