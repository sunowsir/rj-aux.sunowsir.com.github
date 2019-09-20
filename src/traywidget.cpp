#include "traywidget.h"

TrayWidget::TrayWidget(QWidget *parent) : QWidget(parent)
{
    /* tray */

    this->tray_icon = new QSystemTrayIcon(this);
    this->tray_icon->setIcon(QIcon(":/image/resource/icon.png"));
    this->tray_icon->show();
    QWidget::connect(this->tray_icon, SIGNAL(activated( QSystemTrayIcon::ActivationReason )),
                     parent, SLOT(trayAction( QSystemTrayIcon::ActivationReason )),
                     Qt::AutoConnection);

    this->tray_menu = new QMenu(this);
    this->tray_action_show = new QAction(this);
    this->tray_action_exit = new QAction(this);


    this->tray_action_show->setText("显示");
    this->tray_action_exit->setText("退出");

    QWidget::connect(this->tray_action_show, SIGNAL(triggered()),
                parent, SLOT(show()),
                Qt::AutoConnection);
    QWidget::connect(this->tray_action_exit, SIGNAL(triggered()),
                qApp, SLOT(quit()),
                Qt::AutoConnection);

    // this->tray_icon->setToolTip("test set tool tip for tray_icon");
    this->tray_icon->setContextMenu(this->tray_menu);
    this->tray_menu->addAction(this->tray_action_show);
    this->tray_menu->addAction(this->tray_action_exit);

}
