#ifndef SYSTEMNOTIFY_H
#define SYSTEMNOTIFY_H

#include <QObject>
#include <QtDBus>
#include <QDBusReply>
#include <QDBusMessage>
#include <QDBusVariant>
#include <QDBusInterface>

#include <QThread>

class SystemNotify : public QThread
{
    Q_OBJECT

public:
    explicit SystemNotify(QThread *parent = nullptr);

signals:

public slots:

private : 
    QList<QVariant> arg;
	
	void run();
};

#endif 


