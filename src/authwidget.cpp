#include "authwidget.h"

#include <iostream>
#include <QString>

#include <DApplication>

authWidget::authWidget( DMainWindow *parent ) : QWidget( parent )
{

    /* init data */

    this->account = new QString;
    this->password = new QString;
    // this->sudo_pass = new QString;
    this->netcard = new QString;
    this->command = new QString( "./rjsupplicant" );
    this->cmd_args = new QStringList();
    this->process = nullptr;

    /* get network card name  */

    this->network_list = new QStringList;
    foreach ( QNetworkInterface i, QNetworkInterface::allInterfaces() ) {
        if ( i.flags().testFlag( QNetworkInterface::IsLoopBack ) ) continue;
        QString cardname = i.name();

        if ( !cardname.isEmpty() &&
             cardname.startsWith( "e", Qt::CaseInsensitive) ) {
             this->netcard->append( cardname );
             continue;
        }
        this->network_list->append( cardname );
    }

    if ( *( this->netcard ) != "" ) {
        this->network_list->insert( 0, *( this->netcard ) );
    } else {
        this->netcard->append( *this->network_list->begin() );
    }


    /* QTextEdit : show information */
    this->show_info_edit = new QTextEdit( this );
    this->show_info_edit->setReadOnly( true );
    this->show_info_edit->resize( 640, 120 );
    this->show_info_edit->move( 0, 0 );


    /* account label */
    this->label_acco_num = new DLabel( this );
    this->label_acco_num->setText( "账号" );
    /* Position */
    this->label_acco_num->move( 200, 150 );



    /* account line edit  */
    this->lineedit_acco_num = new DLineEdit( this );
    this->lineedit_acco_num->setText( *( this->account ) = runProOnce( "./getLastAccount" ) );
    // this->lineedit_acco_num->setPlaceholderText("please input account");
    this->lineedit_acco_num->move( 260, 145 );
    /* connect signal to slot */



    /* password label */
    this->label_pass_num = new DLabel( this );
    this->label_pass_num->setText( "密码" );
    /* position */
    this->label_pass_num->move( 200, 210 );



    /* password line edit */
    this->passwordedit_pass_num = new DPasswordEdit( this );
    this->passwordedit_pass_num->setText( "******" );
    *( this->password ) = "123456";
    // this->passwordedit_pass_num->setPlaceholderText("please input password");
    this->passwordedit_pass_num->move( 260, 205 );


    /* net card label */
    this->label_choose_card = new DLabel( this );
    this->label_choose_card->setText( "网卡" );
    this->label_choose_card->move( 200, 270 );



    /* choose net card QComboBox */
    this->combox = new QComboBox( this );
    this->combox->move( 260, 265 );
    // this->combox->addItem("默认");
    this->combox->addItems( *( this->network_list ) );



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


    QWidget::connect( this->lineedit_acco_num, SIGNAL( textChanged( QString ) ),
                      this, SLOT( getLineEditText( QString ) ),
                      Qt::AutoConnection );
    QWidget::connect( this->passwordedit_pass_num, SIGNAL( textChanged( QString ) ),
                      this, SLOT( getPasswdText( QString ) ),
                      Qt::AutoConnection );
    QWidget::connect( this->combox, SIGNAL( activated( const QString& ) ),
                      this, SLOT( getNetCardText( QString ) ),
                      Qt::AutoConnection );
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


/* slop */

void authWidget::getLineEditText( const QString& inputstr ) {
    *( this->account ) = inputstr;
}

void authWidget::getPasswdText( const QString& inputstr ) {
    *( this->password ) = inputstr;
}

void authWidget::getNetCardText( const QString& card_name ) {
    if ( this->netcard == nullptr ) this->netcard = new QString( card_name );
    else *( this->netcard ) = card_name;
}



void authWidget::triggerauthen() {

    if ( this->process == nullptr ) {
        this->process = new QProcess( this );
    }

    this->show_info_edit->clear();

    runProOnce( "./rjsupplicant", QStringList() << "-q" );

    this->process->kill();
    this->process->close();


    this->process->setWorkingDirectory( DApplication::applicationDirPath() );

    this->cmd_args->clear();
    this->cmd_args->append( QStringList()
                            << "-a"
                            << "1"
                            << "-d"
                            << "0"
                            << "-u"
                            << *( this->account )
                            << "-n"
                            << *( this->netcard ) );



    /* get checkbox status && judge user input status */

    if ( this->checkbox->checkState() ) {
        this->cmd_args->append( QStringList() << "-S" << "1" );
    }

    if ( runProOnce( "./getLastAccount" ) != *( this->account ) || "******" != *( this->password ) ) {
        this->cmd_args->append(QStringList()<< "-p" << *(this->password));
    }

    /* start run the rjsupplicant program. */

    this->process->start( *( this->command ), *( this->cmd_args ) );
    qDebug() << "process->waitForStarted(): " << process->waitForStarted();

    /* connect signal with slot. */

    QObject::connect( this->process, SIGNAL( readyReadStandardOutput() ),
                      this, SLOT( getProOutput() ) );
    QObject::connect( this->process, SIGNAL( readyReadStandardError() ),
                      this, SLOT(getProErrout()) );
}

void authWidget::getProOutput() {
    qDebug() << "get stdout";
    QString retStr = QString::fromLocal8Bit( process->readAllStandardOutput() ).replace( QRegExp( "^[\\s]*\n+" ), "" );
    if ( retStr == "" ) return;
    this->show_info_edit->append( retStr );

    if ( retStr.contains( "成功" ) ) {
        // restart network;
        runProOnce( "systemctl", QStringList() << "restart" << "NetworkManager.service" );

        this->show_info_edit->clear();
        this->show_info_edit->append( retStr );
        this->show_info_edit->append( runProOnce( "./rjsupplicant", QStringList() << "-l") );
    }
}

void authWidget::getProErrout() {
    qDebug() << "get stderr";
    QString errStr = process->readAllStandardError().data();
    if ( !QRegExp( "\\s*" ).exactMatch( errStr ) &&
         !errStr.contains( "sysctl" ) &&
         !errStr.contains( "write error" ) &&
         !errStr.contains( "错误的文件描述符" )
        ) {
        QMessageBox::information( nullptr, "Error", errStr );
    }
}

QString& authWidget::runProOnce( QString pro_name, QStringList arg ) {
    static QString ret;

    if ( pro_name == "" ) {
        ret = "";
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



