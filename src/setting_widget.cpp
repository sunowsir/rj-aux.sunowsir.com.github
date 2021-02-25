/*
	* File     : setting_widget.h
	* Author   : sunowsir
	* Mail     : sunowsir@163.com
	* Github   : github.com/sunowsir
	* Creation : 2021年02月13日 星期六 16时03分26秒
*/

#include "setting_widget.h"

setting_widget::setting_widget(QMainWindow *parent) {
    this->parent = parent;
    this->setParent(parent);
    this->setting_layout = new QGridLayout();

    this->select_core_label = new QLabel();
    this->select_core_label->setText(tr("选择核心"));

    this->acct_arg_label = new QLabel();
    this->acct_arg_label->setText(tr("账号参数"));

    this->pass_arg_label = new QLabel();
    this->pass_arg_label->setText(tr("密码参数"));

    this->other_arg_label = new QLabel();
    this->other_arg_label->setText(tr("其他参数"));

    this->select_core_button = new QPushButton();
    this->select_core_button->setText(tr("选择核心"));

    this->acct_arg_input = new QLineEdit();
    this->acct_arg_input->setText(QString("-u %s"));

    this->pass_arg_input = new QLineEdit();
    this->pass_arg_input->setText(QString("-p %s"));

    this->other_arg_input = new QLineEdit();
    this->other_arg_input->setText(QString("-a 1 -d 0"));

    this->save_cfg = new QPushButton();
    this->save_cfg->setText(tr("保存"));

    this->set_info = new QStringList;
    this->core_file_assigned = false;


    /* connect */

    QWidget::connect(this->save_cfg, SIGNAL(released()),
                      this, SLOT(on_clicked_save_cfg_button()),
                      Qt::AutoConnection);
    QWidget::connect(this->acct_arg_input, SIGNAL(textChanged(QString)),
                      this, SLOT(get_account_arg_input(QString)),
                      Qt::AutoConnection);
    QWidget::connect(this->pass_arg_input, SIGNAL(textChanged(QString)),
                      this, SLOT(get_passwd_arg_input(QString)),
                      Qt::AutoConnection);
    QWidget::connect(this->other_arg_input, SIGNAL(textChanged(QString)),
                      this, SLOT(get_other_arg_input(QString)),
                      Qt::AutoConnection);
    QWidget::connect(this->select_core_button, SIGNAL(released()),
                      this, SLOT(on_clicked_select_core_button()),
                      Qt::AutoConnection);


    this->setting_layout->addWidget(this->select_core_label, 0, 0, 1, 1);
    this->setting_layout->addWidget(this->acct_arg_label, 1, 0, 1, 1);
    this->setting_layout->addWidget(this->pass_arg_label, 2, 0, 1, 1);
    this->setting_layout->addWidget(this->other_arg_label, 3, 0, 1, 1);
    this->setting_layout->addWidget(this->select_core_button, 0, 1, 1, 1);
    this->setting_layout->addWidget(this->acct_arg_input, 1, 1, 1, 1);
    this->setting_layout->addWidget(this->pass_arg_input, 2, 1, 1, 1);
    this->setting_layout->addWidget(this->other_arg_input, 3, 1, 1, 1);
    this->setting_layout->addWidget(this->save_cfg, 4, 0, 2, 2, Qt::AlignHCenter);

    this->setting_layout->setHorizontalSpacing(20);
    this->setting_layout->setVerticalSpacing(20);
}

setting_widget::~setting_widget() {
    
}

QGridLayout* setting_widget::get_layout() {
    return this->setting_layout;
}

bool setting_widget::get_core_assigned_status() {
    return this->core_file_assigned;
}

/* solt func */

void setting_widget::on_clicked_select_core_button() {
	QString fileName = QFileDialog::getOpenFileName(
		this, 
		tr("select app core."),
		"~/", 
		tr("*"));
	if (!fileName.isEmpty()) {
        this->core_file_assigned = true;
        *(this->set_info) << fileName;
	}
}

void setting_widget::get_account_arg_input(const QString& input_str) {
    *(this->set_info) << input_str;
}

void setting_widget::get_passwd_arg_input(const QString& input_str) {
    *(this->set_info) << input_str;
}

void setting_widget::get_other_arg_input(const QString& input_str) {
    *(this->set_info) << input_str;
}

void setting_widget::on_clicked_save_cfg_button() {
    if (!this->core_file_assigned) {
        this->set_info->clear();
    }
    emit this->save_cfg_button_released(*(this->set_info));
}

