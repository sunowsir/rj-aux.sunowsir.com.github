#ifndef AUTHWIDGET_H
#define AUTHWIDGET_H

#include <QtGui>
#include <QMenu>
#include <QList>
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QProcess>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QtNetwork/QNetworkInterface>

#include <dlabel.h>
#include <dlineedit.h>
#include <dpasswordedit.h>
#include <dtextedit.h>

#include <DMainWindow>

DWIDGET_USE_NAMESPACE

class authWidget : public QWidget
{
    Q_OBJECT

    /* control */

    DLabel          *label_acco_num;
    DLabel          *label_pass_num;
    DLabel          *label_choose_card;
    DLabel          *label_chbox;

    QTextEdit       *show_info_edit;

    DLineEdit       *lineedit_acco_num;

    DPasswordEdit   *passwordedit_pass_num;

    QComboBox       *combox;

    QPushButton     *button_confirm;

    QStringList     *network_list;

    QCheckBox       *checkbox;

    /* information */

    QString         *account;
    QString         *password;
    QString         *netcard;
    QString         *command;
    QStringList     *cmd_args;

    QProcess        *process;

    QString& runProOnce(QString pro_name = "", QStringList arg = QStringList());

signals:

public:
    explicit authWidget(DMainWindow *parent = nullptr);
    ~authWidget();

public slots:
    void getLineEditText(const QString&);
    void getPasswdText(const QString&);
    void getNetCardText(const QString&);
    void triggerauthen();
    void getProOutput();
    void getProErrout();
};

#endif // AUTHWIDGET_H
