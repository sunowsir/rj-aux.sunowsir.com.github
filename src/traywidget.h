#ifndef TRAYWIDGET_H
#define TRAYWIDGET_H

#include <QMenu>
#include <QtGui>
#include <QWidget>
#include <QProcess>
#include <QFileDialog>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QMainWindow>

#include "setting_window.h"

class TrayWidget : public QWidget
{
    Q_OBJECT
    QSystemTrayIcon *tray_icon;

    QMenu           *menu;

    QAction         *show_act;
    QAction         *hide_act;
    QAction 		*setting_act;
    QAction 		*about_act;
    QAction         *exit_act;

    setting_window  *st;
public:
    explicit TrayWidget(QMainWindow *parent = nullptr);
signals:

public slots:
    void setting();
    void show_about();
public slots:
    void on_clicked_save_cfg_button();
signals:
    void save_cfg_button_released();
};

#endif // TRAYWIDGET_H


