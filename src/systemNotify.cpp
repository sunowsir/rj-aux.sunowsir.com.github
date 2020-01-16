#include "systemNotify.h"

#include <QApplication>

SystemNotify::SystemNotify( QThread *parent) : QThread( parent ) {
    QStringList actions;
    QVariantMap hints;

    this->arg	<< QString("rj-aux")							// appname
				<< ((unsigned int) 0)							// id
				<< QString("rj-aux")							// icon
				<< QString("success")                           // summary
				<< QString("already hided")						// body
				<< actions                                      // actions
				<< hints										// hints
				<< ((int) -1);                                  // timeout
}

void SystemNotify::run() {
	
	qDebug()	<< QString("Connect Status : ") 
				<< QDBusConnection::connectToBus(	QDBusConnection::SessionBus, 
													QString("org.freedesktop.Notifications")).isConnected();
	QDBusInterface interface(	QString("org.freedesktop.Notifications"),
								QString("/org/freedesktop/Notifications"),
								QString("org.freedesktop.Notifications"), 
								QDBusConnection::connectToBus(	QDBusConnection::SessionBus,
																QString("org.freedesktop.Notifications")));

	if (!interface.isValid()) {
		qDebug()	<< QString("inerface error : ") 
					<< qPrintable(QDBusConnection::sessionBus().lastError().message());
		return;
	}

	QDBusReply<int> reply = interface.call(QString("Notify"), this->arg);

	if (reply.isValid()) {
		qDebug() << QString("return : ") << reply.value();
    } else {
		qDebug() << QString("Call Notify fail!/n");
	}

	
	// QDBusMessage msg = QDBusMessage::createMethodCall(	QString("org.freedesktop.Notifications"),
	// 													QString("/org/freedesktop/Notifications"),
	// 													QString("org.freedesktop.Notifications"),
	// 													QString("Notify") );
	// msg << this->arg;
	// qDebug() << QString("Send status") << QDBusConnection::sessionBus().send(msg);

}

