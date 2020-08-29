#ifndef loginWIDGET_H
#define loginWIDGET_H

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

// #include <dlabel.h>
// #include <dlineedit.h>
// #include <dtextedit.h>
// #include <DMainWindow>
// #include <DApplication>
// #include <dpasswordedit.h>

#include "showinfowidget.h"

// DWIDGET_USE_NAMESPACE

class loginWidget : public QWidget
{
    Q_OBJECT

    QSettings       *settings;

    QMainWindow     *parent;

    /* control */

    QPushButton     *button_confirm;

    QLabel          *memory_label;
    QCheckBox       *memory_checkbox;

    QLabel          *auto_label;
    QCheckBox       *auto_checkbox;

    // MemoryWidget    *memoryMaster;
    ShowInfoWidget  *ShowInfoMaster;

    /* QProcess */

    static QProcess *static_process;
    QProcess        *process;
    QStringList     pro_args;

    /* Input infomation get */

    QLabel          *account_label;
    QLabel          *password_label;

    QLineEdit       *account_input;
    QLineEdit       *password_input;

    QString         account;
    QString         default_account;
    QString         password;
    QString         default_password;

    QLabel          *netcard_label;
    QComboBox       *netcard_combox;

    /* information save */

    QString         core_file;
    QString         netcard;
	QString			core_process_name;
	QString			get_account_process_name;
	QString			setting_init_file_name;
	QString			notify_process_name;
    QStringList     netcard_list;

    // NetCardWidget   *netcardMaster;

    bool getMCheckStatus();
    bool getLCheckStatus();
    void RefreshNetCard();
	QString runProOnce(QString pro_name = "", QStringList arg = QStringList());

signals:

public:
    explicit loginWidget(QMainWindow *parent = nullptr);
    ~loginWidget();

    void SetCore(QString);

public slots:
    void triggerlogin();
    void getProOutput();
    void getProErrout();
    void getAccountInput(const QString&);
    void getPasswordInput(const QString&);
    void getNetCardChoice(const QString&);
};

#endif // loginWIDGET_H
