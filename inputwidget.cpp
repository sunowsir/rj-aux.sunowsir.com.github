#include "inputwidget.h"

InputWidget::InputWidget(QWidget *parent, QString default_account) : QWidget(parent)
{
    this->default_account = default_account;
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


    /* connect */

    QWidget::connect( this->account_input, SIGNAL( textChanged( QString ) ),
                      this, SLOT( getAccountInput( QString ) ),
                      Qt::AutoConnection );
    QWidget::connect( this->password_input, SIGNAL( textChanged( QString ) ),
                      this, SLOT( getPasswordInput( QString ) ),
                      Qt::AutoConnection );

}


QString InputWidget::getAccount() {
    return this->account;
}

QString InputWidget::getPassword() {
    return this->password;
}

bool InputWidget::isDefaultAccount() {
    return this->default_account == this->account;
}

bool InputWidget::isDefaultPassword() {
    return this->default_password == this->password;
}


/* slot */

void InputWidget::getAccountInput( const QString& inputstr ) {
    this->account = inputstr;
}

void InputWidget::getPasswordInput( const QString& inputstr ) {
    this->password = inputstr;
}
