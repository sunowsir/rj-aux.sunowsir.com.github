/*
	* File     : core_manager.h
	* Author   : sunowsir
	* Mail     : sunowsir@163.com
	* Github   : github.com/sunowsir
	* Creation : 2021年01月01日 星期五 19时20分10秒
*/

#ifndef _CORE_MANAGER_H
#define _CORE_MANAGER_H

#include <QObject>

#include <QList>
#include <QString>

class core_manager {
private: 
    Q_OBJECT;

    QString core;

    QStringList login_args;
    QStringList logout_args;
    QStringList status_args;
    QStringList info_args;

public: 

};

#endif
