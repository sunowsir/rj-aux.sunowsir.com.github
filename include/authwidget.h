#ifndef AUTHWIDGET_H
#define AUTHWIDGET_H

#include <QSystemTrayIcon>
#include <QPushButton>
#include <QComboBox>
#include <QWidget>
#include <QDialog>
#include <QtGui>
#include <QMenu>
#include <QList>
#include <QString>
#include <QtNetwork/QNetworkInterface>
#include <QProcess>
#include <QMessageBox>

#include <dlabel.h>
#include <dlineedit.h>
#include <dpasswordedit.h>
#include <dtextedit.h>

#include <DMainWindow>

DWIDGET_USE_NAMESPACE

class authWidget : public QWidget
{
    Q_OBJECT

    DLabel          *label_acco_num;
    DLabel          *label_pass_num;
    DLabel          *label_choose_card;
    DLabel          *label_sudo_pass;

    QTextEdit       *show_info_edit;

    DLineEdit       *lineedit_acco_num;
    DPasswordEdit   *passwordedit_pass_num;
    DPasswordEdit   *passwordedit_sudo_pass;

    QComboBox       *combox;
    QPushButton     *button_confirm;

    QStringList     *network_list;

    /* information */

    QString         *account;
    QString         *password;
    QString         *sudo_pass;
    QString         *netcard;

    QString         *command;
    QStringList     *cmd_args;

    QProcess        *process;

signals:

public:
    explicit authWidget(DMainWindow *parent = nullptr);
    ~authWidget();

public slots:
    void getLineEditText(const QString&);
    void getPasswdText(const QString&);
    void getSudopassText(const QString&);
    void getNetCardText(const QString&);
    void triggerauthen();
    void cmd_output();
    void cmd_errout();
};

#endif // AUTHWIDGET_H
