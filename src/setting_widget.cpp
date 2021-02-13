/*
	* File     : setting_widget.h
	* Author   : sunowsir
	* Mail     : sunowsir@163.com
	* Github   : github.com/sunowsir
	* Creation : 2021年02月13日 星期六 15时05分17秒
*/

#include "setting_widget.h"

setting_widget::setting_widget( QMainWindow *parent ) : QMainWindow(parent) {
    this->settings = new QSettings( QCoreApplication::applicationDirPath() + "/setting_Config.ini", QSettings::IniFormat );

    this->parent = parent;
}

setting_widget::~setting_widget() {
    
}

