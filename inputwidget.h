#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QObject>
#include <QWidget>

#include <QString>

#include <dlabel.h>
#include <DLineEdit>
#include <dpasswordedit.h>

DWIDGET_USE_NAMESPACE

class InputWidget : public QWidget
{
    Q_OBJECT

    DLabel          *account_label;
    DLabel          *password_label;

    DLineEdit       *account_input;
    DPasswordEdit   *password_input;

    /* information save */

    QString         account;
    QString         default_account;
    QString         password;
    QString         default_password;

public:
    explicit InputWidget(QWidget *parent = nullptr, QString default_account = "");
    QString getAccount();
    QString getPassword();
    bool isDefaultAccount();
    bool isDefaultPassword();

signals:

public slots:
    void getAccountInput(const QString&);
    void getPasswordInput(const QString&);
};

#endif // INPUTWIDGET_H
