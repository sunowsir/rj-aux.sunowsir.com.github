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


#include <dlabel.h>
#include <dlineedit.h>
#include <dtextedit.h>
#include <DMainWindow>
#include <DApplication>
#include <dpasswordedit.h>

#include "showinfowidget.h"
#include "systemNotify.h"

DWIDGET_USE_NAMESPACE

class loginWidget : public QWidget
{
    Q_OBJECT

    QSettings       *settings;

    DMainWindow     *parent;

    /* control */

    QPushButton     *button_confirm;

    DLabel          *memory_label;
    QCheckBox       *memory_checkbox;

    DLabel          *auto_label;
    QCheckBox       *auto_checkbox;

    // MemoryWidget    *memoryMaster;
    ShowInfoWidget  *ShowInfoMaster;

    /* QProcess */

    bool            rund_status;
    QProcess        *process;
    QStringList     pro_args;

    /* Input infomation get */

    DLabel          *account_label;
    DLabel          *password_label;

    DLineEdit       *account_input;
    DPasswordEdit   *password_input;

    QString         account;
    QString         default_account;
    QString         password;
    QString         default_password;

    DLabel          *netcard_label;
    QComboBox       *netcard_combox;

    /* information save */

    QString         netcard;
    QStringList     netcard_list;

    // NetCardWidget   *netcardMaster;

    bool getMCheckStatus();
    bool getLCheckStatus();
    void RefreshNetCard();
    static QString runProOnce(QString pro_name = "", QStringList arg = QStringList());
signals:

public:
    explicit loginWidget(DMainWindow *parent = nullptr);
    ~loginWidget();

public slots:
    void triggerlogin();
    void getProOutput();
    void getProErrout();
    void getAccountInput(const QString&);
    void getPasswordInput(const QString&);
    void getNetCardChoice(const QString&);
};

#endif // loginWIDGET_H
