#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMenu>
#include <QtGui>
#include <QWidget>

#include <QMainWindow>

#include <QMessageBox>

#include "loginwidget.h"
#include "traywidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    loginWidget  *w;
    TrayWidget  *t;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *event);
    void changeEvent(QEvent *e);
public slots:
    void trayAction(QSystemTrayIcon::ActivationReason reason);
};

#endif // MAINWINDOW_H
