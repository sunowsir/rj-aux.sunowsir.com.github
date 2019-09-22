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

    QMenu           *tray_menu;

    QAction         *tray_action_show;
    QAction         *tray_action_exit;

public:
    explicit TrayWidget(QWidget *parent = nullptr);
    ~TrayWidget();

signals:

public slots:

};

#endif // TRAYWIDGET_H
