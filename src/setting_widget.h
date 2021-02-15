/*
	* File     : setting_widget.h
	* Author   : sunowsir
	* Mail     : sunowsir@163.com
	* Github   : github.com/sunowsir
	* Creation : 2021年02月13日 星期六 16时03分26秒
*/

#ifndef _SETTING_WINDOW_H
#define _SETTING_WINDOW_H

#include <QtGui>
#include <QMenu>
#include <QList>
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QCheckBox>
#include <QComboBox>
#include <QSettings>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>

#include <qlabel.h>
#include <qlineedit.h>
#include <qtextedit.h>

#include <QMainWindow>
#include <QGridLayout>

class setting_widget : public QWidget {
    Q_OBJECT

    QSettings       *settings;
    QMainWindow     *parent;
    QGridLayout     *setting_layout;

    QLabel          *select_core_label;
    QLabel          *acct_arg_label;
    QLabel          *pass_arg_label;
    QLabel          *other_arg_label;

    QPushButton     *select_core_button;
    QLineEdit       *acct_arg_input;
    QLineEdit       *pass_arg_input;
    QLineEdit       *other_arg_input;

    QPushButton     *save_cfg;
public:
    explicit setting_widget(QMainWindow *parent = nullptr);
    ~setting_widget();

    QGridLayout     *get_layout();
public slots:
    void on_clicked_select_core_button();
    void get_account_arg_input(const QString&);
    void get_passwd_arg_input(const QString&);
    void get_other_arg_input(const QString&);
    void on_clicked_save_cfg_button();
};

#endif
