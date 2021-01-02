/*
	* File     : core_manager.h
	* Author   : sunowsir
	* Mail     : sunowsir@163.com
	* Github   : github.com/sunowsir
	* Creation : 2021年01月02日 星期六 10时21分53秒
*/

#include "core_manager.h"

core_manager::core_manager(QMainWindow *parent): QWidget(parent) {
    this->core = new QString;
    this->login_args = new QStringList;
    this->logout_args = new QStringList;
    this->status_args = new QStringList;
}

core_manager::~core_manager() {
    delete this->core;
    delete this->login_args;
    delete this->logout_args;
    delete this->status_args;
}

core_manager core_manager::get_core_mgr_pro() {
}
