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

void MainWindow::load_core() {

    QFileDialog *select_core = new QFileDialog(this);

    select_core->setWindowTitle(QString("选择锐捷提供的linux有线客户端文件"));
    select_core->setDirectory(".");
    select_core->setNameFilters(QStringList() << QString("rjsupplicant.sh (rjsupplicant.sh)")
											  << QString("rjsupplicant (rjsupplicant)"));
    select_core->setFileMode(QFileDialog::ExistingFiles);
    select_core->setViewMode(QFileDialog::Detail);

    if (select_core->exec()) {
        QStringList select_list;
        select_list = select_core->selectedFiles();
        this->w->SetCore(select_list[0]);
    }

    delete select_core;
}



/* rewrite */

/*
void MainWindow::changeEvent( QEvent *e ) {
    if ( ( e->type() == QEvent::WindowStateChange ) && this->isMinimized() ) {
        QTimer::singleShot( 100, this, SLOT( close() ) );
    }
}


void MainWindow::closeEvent( QCloseEvent *e ) {
    e->ignore();
    this->hide();
}

*/

