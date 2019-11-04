#ifndef NETCARDWIDGET_H
#define NETCARDWIDGET_H

#include <QList>
#include <QWidget>
#include <QObject>
#include <QString>
#include <QComboBox>
#include <QtNetwork/QNetworkInterface>

#include <dlabel.h>

DWIDGET_USE_NAMESPACE

class NetCardWidget : public QWidget
{
    Q_OBJECT

    DLabel          *netcard_label;
    QComboBox       *netcard_combox;

    /* information save */

    QString         netcard;
    QStringList     netcard_list;

    void RefreshNetCard();
public:
    explicit NetCardWidget(QWidget *parent = nullptr);
    QString getNetcard();

signals:

public slots:
    void getNetCardChoice(const QString&);
};

#endif // NETCARDWIDGET_H
