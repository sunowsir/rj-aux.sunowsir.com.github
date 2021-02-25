#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    this->setFixedSize(640, 540);
    this->setWindowTitle(tr("锐捷校园网有线认证linux辅助客户端"));
    this->setWindowIcon(QIcon(QString(":/image/resource/icon.png")));

    this->w = new loginWidget(this);
    // this->resize(this->w->size()); //设置窗口大小
    setCentralWidget(this->w);

    this->t = new TrayWidget(this);

    QWidget::connect(this->t, SIGNAL(save_cfg_button_released(const QStringList&)),
                      this->w, SLOT(on_clicked_save_cfg_button(const QStringList&)),
                      Qt::AutoConnection);
}

MainWindow::~MainWindow() {
    this->w->close();
    delete this->w;
    this->t->close();
    delete this->t;
}

/* slot */

void MainWindow::trayAction(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::Trigger) {
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

