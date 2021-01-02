/*
	* File     : core_manager.h
	* Author   : sunowsir
	* Mail     : sunowsir@163.com
	* Github   : github.com/sunowsir
	* Creation : 2021年01月01日 星期五 19时20分10秒
*/

#ifndef _CORE_MANAGER_H
#define _CORE_MANAGER_H

#include <QWidget>
#include <QMainWindow>

#include <QList>
#include <QString>

class core_manager : public QWidget {
private: 
    Q_OBJECT;

    QString *core;

    QStringList *login_args;
    QStringList *logout_args;
    QStringList *status_args;

    static core_manager *public_core_mgr_pro;

public: 
    core_manager(QMainWindow *parent = nullptr);
    ~core_manager();

    static core_manager* get_core_mgr_pro();
};

#endif
