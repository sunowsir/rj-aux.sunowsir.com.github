#ifndef TRAYWIDGET_H
#define TRAYWIDGET_H

#include <QMenu>
#include <QtGui>
#include <QFile>
#include <QDebug>
#include <QWidget>
#include <QString>
#include <QIODevice>
#include <QByteArray>
#include <qfiledialog.h>
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

    QString 		core_zip;

public:
    explicit TrayWidget(QWidget *parent = nullptr);

signals:

public slots:
    void load_core();
    void show_about();
};

#endif // TRAYWIDGET_H


