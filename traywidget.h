#ifndef TRAYWIDGET_H
#define TRAYWIDGET_H

#include <QMenu>
#include <QtGui>
#include <QWidget>
#include <QProcess>
#include <QSystemTrayIcon>

class TrayWidget : public QWidget
{
    Q_OBJECT
    QSystemTrayIcon *tray_icon;

    QMenu           *menu;

    QAction         *show_act;
    QAction         *exit_act;
    QAction         *hide_act;

public:
    explicit TrayWidget(QWidget *parent = nullptr);

signals:

public slots:

};

#endif // TRAYWIDGET_H


