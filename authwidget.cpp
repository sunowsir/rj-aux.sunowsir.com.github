#include "authwidget.h"

authWidget::authWidget( DMainWindow *parent ) : QWidget( parent )
{
    this->parent = parent;

    this->inputMaster = new InputWidget( this, runProOnce( "./getLastAccount" ) );
    this->netcardMaster = new NetCardWidget( this );
    this->memoryMaster = new MemoryWidget( this );
    this->ShowInfoMaster = new ShowInfoWidget( this );

    this->process = nullptr;
    this->pro_args = QStringList(QStringList() << "-a"
                                     << "1"
                                     << "-d"
                                     << "0"
                                     << "-u"
                                     << this->inputMaster->getAccount()
                                     << "-n"
                                     << this->netcardMaster->getNetcard());

    /* confirm button */
    this->button_confirm = new QPushButton( this );
    this->button_confirm->setText( "认证" );
    this->button_confirm->move( 260, 385 );

    /* connect signal with slot */

    QWidget::connect( this->button_confirm, SIGNAL( released() ),
                      this, SLOT( triggerauthen() ),
                      Qt::AutoConnection );

}

authWidget::~authWidget() {
    if ( this->process != nullptr ) {
        runProOnce( "./rjsupplicant", QStringList() << "-q" );
    }
    // restart network;
    runProOnce( "systemctl", QStringList() << "restart" << "NetworkManager.service" );
}



void authWidget::triggerauthen() {

    this->ShowInfoMaster->clear();

    if ( this->process == nullptr ) {
        this->process = new QProcess( this );
    } else {
        runProOnce( "./rjsupplicant", QStringList() << "-q" );
        this->process->kill();
        this->process->close();
    }

    if ( this->pro_args[5] != this->inputMaster->getAccount() )
        this->pro_args.replace(5, this->inputMaster->getAccount());
    if ( this->pro_args[7] != this->netcardMaster->getNetcard() )
        this->pro_args.replace(7, this->netcardMaster->getNetcard());


    /* get checkbox status && judge user input status */

    if ( !this->inputMaster->isDefaultAccount() || !this->inputMaster->isDefaultPassword() ) {
        if ( this->memoryMaster->getCheckStatus() ) {
            this->pro_args.append( QStringList() << "-S" << "1" );
        }
        this->pro_args.append(QStringList()<< "-p" << this->inputMaster->getPassword());
    }


    /* start run the rjsupplicant program. */

    this->process->setWorkingDirectory( DApplication::applicationDirPath() );
    this->process->start( "./rjsupplicant", this->pro_args );
    this->process->waitForStarted();


    /* connect signal with slot. */

    QObject::connect( this->process, SIGNAL( readyReadStandardOutput() ),
                      this, SLOT( getProOutput() ) );
    QObject::connect( this->process, SIGNAL( readyReadStandardError() ),
                      this, SLOT( getProErrout() ) );
}

void authWidget::getProOutput() {

    QString retStr = QString::fromLocal8Bit(
                process->readAllStandardOutput() ).replace(QString("\n"), QString(""));

    if ( retStr.isEmpty() ) return;
    this->ShowInfoMaster->append( retStr );

    if ( retStr.contains( "成功" ) ) {
        // restart network;
        runProOnce( "systemctl", QStringList() << "restart" << "NetworkManager.service" );
        this->ShowInfoMaster->setText( retStr );
        this->parent->hide();
        QMessageBox::information( nullptr, "登录成功", "登录面板已隐藏到托盘" );
    }
}

void authWidget::getProErrout() {

    QString errStr = process->readAllStandardError().data();
    if ( !QRegExp( "\\s*" ).exactMatch( errStr ) &&
         !errStr.contains( "sysctl" ) &&
         !errStr.contains( "write error" ) &&
         !errStr.contains( "错误的文件描述符" )
       ) {
        QMessageBox::information( nullptr, "Error", errStr );
    }
}

QString authWidget::runProOnce( QString pro_name, QStringList arg ) {

    QString ret;

    if ( pro_name.isEmpty() ) {
        ret.clear();
        return ret;
    }

    QProcess pro;
    pro.setWorkingDirectory( DApplication::applicationDirPath() );
    pro.start( pro_name, arg );
    pro.waitForFinished();
    ret = pro.readAllStandardOutput();
    pro.kill();
    pro.close();

    return ret;
}



