#include "authwidget.h"

authWidget::authWidget( DMainWindow *parent ) : QWidget( parent )
{

    this->inputMaster = new InputWidget( this, runProOnce( "./getLastAccount" ) );
    this->netcardMaster = new NetCardWidget( this );

    this->process = nullptr;
    this->cmd_args = new QStringList(QStringList() << "-a"
                                     << "1"
                                     << "-d"
                                     << "0"
                                     << "-u"
                                     << this->inputMaster->getAccount()
                                     << "-n"
                                     << this->netcardMaster->getNetcard());

    /* QTextEdit : show information */
    this->show_info_edit = new QTextEdit( this );
    this->show_info_edit->setReadOnly( true );
    this->show_info_edit->resize( 640, 120 );
    this->show_info_edit->move( 0, 0 );

    /* confirm button */
    this->button_confirm = new QPushButton( this );
    this->button_confirm->setText( "认证" );
    this->button_confirm->move( 260, 385 );

    /*  password checkbox  */
    this->checkbox = new QCheckBox( this );
    this->checkbox->move( 200, 320 );
    this->checkbox->setChecked( true );


    /* password checkbox label */
    this->label_chbox = new DLabel( this );
    this->label_chbox->setText( "记住密码" );
    this->label_chbox->move( 230, 320 );



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

    this->show_info_edit->clear();

    if ( this->process == nullptr ) {
        this->process = new QProcess( this );
    } else {
        runProOnce( "./rjsupplicant", QStringList() << "-q" );
        this->process->kill();
        this->process->close();
    }

    // this->cmd_args->clear();
    this->cmd_args->replace(5, this->inputMaster->getAccount());
    this->cmd_args->replace(7, this->netcardMaster->getNetcard());

    /* get checkbox status && judge user input status */

    if ( !this->inputMaster->isDefaultAccount() || !this->inputMaster->isDefaultPassword() ) {
        if ( this->checkbox->checkState() ) {
            this->cmd_args->append( QStringList() << "-S" << "1" );
        }
        this->cmd_args->append(QStringList()<< "-p" << this->inputMaster->getPassword());
    }

    /* start run the rjsupplicant program. */

    this->process->setWorkingDirectory( DApplication::applicationDirPath() );
    this->process->start( "./rjsupplicant", *( this->cmd_args ) );
    this->process->waitForStarted();

    /* connect signal with slot. */

    QObject::connect( this->process, SIGNAL( readyReadStandardOutput() ),
                      this, SLOT( getProOutput() ) );
    QObject::connect( this->process, SIGNAL( readyReadStandardError() ),
                      this, SLOT( getProErrout() ) );
}

void authWidget::getProOutput() {

    QString retStr = QString::fromLocal8Bit( process->readAllStandardOutput() ).replace( QRegExp( "^[\\s]*\n+" ), "" );
    if ( retStr.isEmpty() ) return;
    this->show_info_edit->append( retStr );

    if ( retStr.contains( "成功" ) ) {
        // restart network;
        runProOnce( "systemctl", QStringList() << "restart" << "NetworkManager.service" );

        this->show_info_edit->clear();
        this->show_info_edit->append( retStr );
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



