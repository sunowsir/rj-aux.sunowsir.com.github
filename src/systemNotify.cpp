#include "systemNotify.h"

#include <QApplication>

SystemNotify::SystemNotify( QThread *parent) : QThread( parent ) {
}

void SystemNotify::run() {
	
	// QDBusMessage msg = QDBusMessage::createMethodCall(	QString("org.freedesktop.Notifications"),
	// 													QString("/org/freedesktop/Notifications"),
	// 													QString("org.freedesktop.Notifications"),
	// 													QString("Notify") );
	
	QDBusInterface interface(	QString("org.freedesktop.Notifications"),
								QString("/org/freedesktop/Notifications"),
								QString("org.freedesktop.Notifications"));

	if (!interface.isValid()) {
		qDebug() << qPrintable(QDBusConnection::sessionBus().lastError().message());
		return;
	}

    QStringList actions;
    QVariantMap hints;

    QList<QVariant> arg;
    arg << QString("rj-aux")							// appname
		<< ((unsigned int) 0)							// id
		<< QString("rj-aux")							// icon
		<< QString("success")                           // summary
		<< QString("already hided")						// body
		<< actions                                      // actions
		<< actions                                      // hints
		<< ((int) -1);                                  // timeout

	// msg << arg;
	// qDebug() << QString("Send status") << QDBusConnection::sessionBus().send(msg);

	QDBusReply<int> reply = interface.call(QString("Notify"), arg);

	if (reply.isValid()) {
		qDebug() << QString("return : ") << reply.value();
    } else {
		qDebug() << QString("Call Notify fail!/n");
	}

}

