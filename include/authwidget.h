#ifndef AUTHWIDGET_H
#define AUTHWIDGET_H

#include <QtGui>
#include <QMenu>
#include <QList>
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QProcess>
#include <QCheckBox>
#include <QPushButton>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QComboBox>
#include <QtNetwork/QNetworkInterface>


#include <dlabel.h>
#include <dlineedit.h>
#include <dtextedit.h>
#include <DMainWindow>
#include <DApplication>
#include <dpasswordedit.h>

#include "showinfowidget.h"

DWIDGET_USE_NAMESPACE

class authWidget : public QWidget
{
    Q_OBJECT
    DMainWindow     *parent;

    /* control */

    QPushButton     *button_confirm;

    DLabel          *memory_label;
    QCheckBox       *memory_checkbox;

    // MemoryWidget    *memoryMaster;
    ShowInfoWidget  *ShowInfoMaster;

    /* information */

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

    bool getCheckStatus();
    void RefreshNetCard();
    static QString runProOnce(QString pro_name = "", QStringList arg = QStringList());
signals:

public:
    explicit authWidget(DMainWindow *parent = nullptr);
    ~authWidget();

public slots:
    void triggerauthen();
    void getProOutput();
    void getProErrout();
    void getAccountInput(const QString&);
    void getPasswordInput(const QString&);
    void getNetCardChoice(const QString&);
};

#endif // AUTHWIDGET_H
