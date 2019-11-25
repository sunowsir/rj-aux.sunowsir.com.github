#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMenu>
#include <QtGui>
#include <QWidget>

#include <DMainWindow>

#include <QMessageBox>

#include "authwidget.h"
#include "traywidget.h"

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT
    authWidget  *w;
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
