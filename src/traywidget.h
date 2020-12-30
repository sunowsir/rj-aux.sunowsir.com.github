#ifndef TRAYWIDGET_H
#define TRAYWIDGET_H

#include <QMenu>
#include <QtGui>
#include <QWidget>
#include <QProcess>
#include <QFileDialog>
#include <QMessageBox>
#include <QSystemTrayIcon>

class TrayWidget : public QWidget
{
    Q_OBJECT
    QSystemTrayIcon *tray_icon;

    QMenu           *menu;

    QAction         *show_act;
    QAction         *hide_act;
    QAction 		*core_act;
    QAction 		*about_act;
    QAction         *exit_act;


public:
    explicit TrayWidget(QWidget *parent = nullptr);

signals:

public slots:
    void load_core();
    void show_about();
};

#endif // TRAYWIDGET_H


