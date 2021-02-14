/*
	* File     : setting_window.h
	* Author   : sunowsir
	* Mail     : sunowsir@163.com
	* Github   : github.com/sunowsir
	* Creation : 2021年02月13日 星期六 15时05分17秒
*/

#ifndef _SETTING_WIDGET_H
#define _SETTING_WIDGET_H

#include <QMenu>
#include <QtGui>
#include <QWidget>

#include <QMainWindow>

#include <QMessageBox>

#include "setting_widget.h"

class setting_window : public QMainWindow {
    Q_OBJECT

    setting_widget *st;
public:
    explicit setting_window(QWidget *parent = nullptr);
    ~setting_window();
};

#endif
