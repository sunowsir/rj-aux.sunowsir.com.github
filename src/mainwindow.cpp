#include "mainwindow.h"

DWIDGET_USE_NAMESPACE

MainWindow::MainWindow( QWidget *parent )
    : DMainWindow( parent )
{

    this->resize( 640, 540 );

    this->w = new authWidget( this );
    // this->resize(this->w->size()); //设置窗口大小
    setCentralWidget( this->w );

    this->t = new TrayWidget( this );

}

MainWindow::~MainWindow() {
    this->w->close();
    delete this->w;
    this->t->close();
    delete this->t;
}

/* slot */

void MainWindow::trayAction( QSystemTrayIcon::ActivationReason reason ) {
    if ( reason == QSystemTrayIcon::Trigger ) {
        this->showNormal();
    }
}


/* rewrite */


void MainWindow::changeEvent( QEvent *e ) {
    if ( ( e->type() == QEvent::WindowStateChange ) && this->isMinimized() ) {
        QTimer::singleShot( 100, this, SLOT( close() ) );
    }
}


void MainWindow::closeEvent( QCloseEvent *e ) {
    e->ignore();
    this->hide();
}


