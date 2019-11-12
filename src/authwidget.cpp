#include "authwidget.h"

authWidget::authWidget( DMainWindow *parent ) : QWidget( parent )
{
    this->parent = parent;


    this->default_account = runProOnce( "./getLastAccount" );
    this->default_password = "******";

    /* account label */

    this->account_label = new DLabel( this );
    this->account_label->setText( "账号" );
    this->account_label->move( 200, 150 );


    /* account line edit  */

    this->account_input = new DLineEdit( this );
    this->account_input->setText( this->account = this->default_account );
    // this->lineedit_acco_num->setPlaceholderText("please input account");
    this->account_input->move( 260, 145 );


    /* password label */

    this->password_label = new DLabel( this );
    this->password_label->setText( "密码" );
    this->password_label->move( 200, 210 );


    /* password line edit */

    this->password_input = new DPasswordEdit( this );
    this->password_input->setText( this->password = default_password );
    // this->passwordedit_pass_num->setPlaceholderText("please input password");
    this->password_input->move( 260, 205 );





    /* netcard */

    RefreshNetCard();

    /* net card label */
    this->netcard_label = new DLabel( this );
    this->netcard_label->setText( "网卡" );
    this->netcard_label->move( 200, 270 );

    /* choose net card QComboBox */
    this->netcard_combox = new QComboBox( this );
    this->netcard_combox->move( 260, 265 );
    this->netcard_combox->addItems( this->netcard_list );






    /*  password checkbox  */
    this->memory_checkbox = new QCheckBox( this );
    this->memory_checkbox->move( 200, 320 );
    this->memory_checkbox->setChecked( true );


    /* password checkbox label */
    this->memory_label = new DLabel( this );
    this->memory_label->setText( "记住密码" );
    this->memory_label->move( 230, 320 );




    this->ShowInfoMaster = new ShowInfoWidget( this );

    this->process = nullptr;
    this->pro_args = QStringList(QStringList() << "-a"
                                     << "1"
                                     << "-d"
                                     << "0"
                                     << "-u"
                                     << this->account
                                     << "-n"
                                     << this->netcard);

    /* confirm button */
    this->button_confirm = new QPushButton( this );
    this->button_confirm->setText( "认证" );
    this->button_confirm->move( 260, 385 );

    /* connect signal with slot */

    QWidget::connect( this->account_input, SIGNAL( textChanged( QString ) ),
                      this, SLOT( getAccountInput( QString ) ),
                      Qt::AutoConnection );
    QWidget::connect( this->password_input, SIGNAL( textChanged( QString ) ),
                      this, SLOT( getPasswordInput( QString ) ),
                      Qt::AutoConnection );
    QWidget::connect( this->netcard_combox, SIGNAL( activated( const QString& ) ),
                      this, SLOT( getNetCardChoice( QString ) ),
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



void authWidget::triggerauthen() {

    this->ShowInfoMaster->clear();

    if ( this->process == nullptr ) {
        this->process = new QProcess( this );
    } else {
        runProOnce( "./rjsupplicant", QStringList() << "-q" );
        this->process->kill();
        this->process->close();
    }

    if ( this->pro_args[5] != this->account )
        this->pro_args.replace(5, this->account);
    if ( this->pro_args[7] != this->netcard )
        this->pro_args.replace(7, this->netcard);


    /* get checkbox status && judge user input status */

    if ( this->account != this->default_account ||
         this->password != this->default_password  ) {
        if ( this->getCheckStatus() ) {
            this->pro_args.append( QStringList() << "-S" << "1" );
        }
        this->pro_args.append(QStringList()<< "-p" << this->password);
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

void authWidget::RefreshNetCard() {

    this->netcard.clear();
    this->netcard_list.clear();

    foreach ( QNetworkInterface i, QNetworkInterface::allInterfaces() ) {
        if ( i.flags().testFlag( QNetworkInterface::IsLoopBack ) ) continue;
        QString cardname = i.name();

        if ( !cardname.isEmpty() &&
             cardname.startsWith( "e", Qt::CaseInsensitive ) ) {
             this->netcard.append( cardname );
             continue;
        }
        this->netcard_list.append( cardname );
    }

    if ( !this->netcard.isEmpty() ) {
        this->netcard_list.insert( 0, this->netcard );
    } else {
        this->netcard.append( this->netcard_list[0] );
    }

}

bool authWidget::getCheckStatus() {
    return this->memory_checkbox->checkState();
}




/* slot */

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


void authWidget::getAccountInput( const QString& inputstr ) {
    this->account = inputstr;
}

void authWidget::getPasswordInput( const QString& inputstr ) {
    this->password = inputstr;
}

void authWidget::getNetCardChoice( const QString& choice_str ) {
    this->netcard = choice_str;
}




