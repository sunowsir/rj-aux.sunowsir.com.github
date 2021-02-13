/*
	* File     : setting_widget.h
	* Author   : sunowsir
	* Mail     : sunowsir@163.com
	* Github   : github.com/sunowsir
	* Creation : 2021年02月13日 星期六 15时05分17秒
*/

#ifndef _SETTING_WIDGET_H
#define _SETTING_WIDGET_H

#include <QtGui>
#include <QMenu>
#include <QList>
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QProcess>
#include <QCheckBox>
#include <QComboBox>
#include <QSettings>
#include <QPushButton>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QtNetwork/QNetworkInterface>
#include <QProcessEnvironment>
#include <qlabel.h>
#include <qlineedit.h>
#include <qtextedit.h>
#include <QMainWindow>


class setting_widget : public QMainWindow {
    Q_OBJECT

    QSettings       *settings;

    QMainWindow     *parent;

public:
    explicit setting_widget(QMainWindow *parent = nullptr);
    ~setting_widget();
    
};

#endif
