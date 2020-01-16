#include <QString>

#include <DWidgetUtil>
#include <DApplication>

#include "mainwindow.h"

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{

    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);
	a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    // a.loadTranslator();
    a.setOrganizationName("deepin");
    a.setApplicationVersion(DApplication::buildVersion("2.4"));
    a.setApplicationName("rj-aux");

    a.setWindowIcon(QIcon(":/image/resource/icon.png"));

    MainWindow w(nullptr);
    w.show();

    //让打开时界面显示在正中
    Dtk::Widget::moveToCenter(&w);

	return a.exec();
}

