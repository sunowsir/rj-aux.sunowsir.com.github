/*
	* File     : setting_widget.h
	* Author   : sunowsir
	* Mail     : sunowsir@163.com
	* Github   : github.com/sunowsir
	* Creation : 2021年02月13日 星期六 16时03分26秒
*/

#include "setting_widget.h"

setting_widget::setting_widget( QMainWindow *parent ) : QWidget(parent) {
    this->settings = new QSettings( QCoreApplication::applicationDirPath() + "/setting_Config.ini", QSettings::IniFormat );

    this->parent = parent;

    this->acct_arg_label = new QLabel();
    this->acct_arg_label->setText( tr("账号参数") );
    this->acct_arg_label->move(200, 150);
    this->acct_arg_label->resize(100, 30);

    this->pass_arg_label = new QLabel();
    this->pass_arg_label->setText( tr("密码参数") );
    this->pass_arg_label->move(200, 210);
    this->pass_arg_label->resize(100, 30);

    this->other_arg_label = new QLabel();
    this->other_arg_label->setText( tr("其他参数") );
    this->other_arg_label->move(200, 270);
    this->other_arg_label->resize(100, 30);

    this->acct_arg_input = new QLineEdit();
    this->acct_arg_input->setText(QString("-u %d"));


    this->pass_arg_input = new QLineEdit();
    this->pass_arg_input->setText(QString("-p %d"));

    this->other_arg_input = new QLineEdit();
    this->other_arg_input->setText(QString("-a 1 -d 0"));


    QWidget::connect(this->acct_arg_input, SIGNAL( textChanged( QString ) ),
                      this, SLOT(get_account_arg_input(QString)),
                      Qt::AutoConnection);
    QWidget::connect(this->pass_arg_input, SIGNAL( textChanged( QString ) ),
                      this, SLOT(get_passwd_arg_input(QString)),
                      Qt::AutoConnection);
    QWidget::connect(this->other_arg_input, SIGNAL( textChanged( QString ) ),
                      this, SLOT(get_other_arg_input(QString)),
                      Qt::AutoConnection);
}

setting_widget::~setting_widget() {
    
}



/* input solt func */

void setting_widget::get_account_arg_input(const QString&) {
    
}

void setting_widget::get_passwd_arg_input(const QString&) {
    
}

void setting_widget::get_other_arg_input(const QString&) {
    
}
