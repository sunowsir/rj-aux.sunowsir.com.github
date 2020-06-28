#include "traywidget.h"

TrayWidget::TrayWidget( QWidget *parent ) : QWidget( parent )
{
    /* tray */

    this->tray_icon = new QSystemTrayIcon( this );
    this->tray_icon->setIcon( QIcon( ":/image/resource/icon.png" ) );
    this->tray_icon->show();

    this->menu = new QMenu( this );
    this->show_act = new QAction( this );
    this->hide_act = new QAction( this );
    this->exit_act = new QAction( this );

    this->show_act->setText( "显示" );
    this->hide_act->setText( "隐藏" );
    this->exit_act->setText( "退出" );


    // this->tray_icon->setToolTip("test set tool tip for tray_icon");

    this->tray_icon->setContextMenu( this->menu );
    this->menu->addAction( this->show_act );
    this->menu->addAction( this->hide_act );
    this->menu->addAction( this->exit_act );


    /* connect signal with slot. */

    QWidget::connect( this->tray_icon, SIGNAL( activated( QSystemTrayIcon::ActivationReason ) ),
                    parent, SLOT( trayAction( QSystemTrayIcon::ActivationReason ) ),
                    Qt::AutoConnection );
    QWidget::connect( this->show_act, SIGNAL( triggered() ),
                    parent, SLOT( show() ),
                    Qt::AutoConnection );
    QWidget::connect( this->hide_act, SIGNAL( triggered() ),
                    parent, SLOT( hide() ),
                    Qt::AutoConnection );
    QWidget::connect( this->exit_act, SIGNAL( triggered() ),
                    qApp, SLOT( quit() ),
                    Qt::AutoConnection );
}
