#include <DApplication>
#include <DWidgetUtil>
#include "mainwindow.h"


DWIDGET_USE_NAMESPACE
int main(int argc, char *argv[])
{

    DApplication::loadDXcbPlugin();  //让bar处在标题栏中
    DApplication a(argc, argv);

    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    a.loadTranslator();
    a.setOrganizationName("deepin");
    a.setApplicationVersion(DApplication::buildVersion("1.0"));
    //a.setApplicationAcknowledgementPage("https://你的网站");
    // a.setProductIcon(QIcon(":/image/resource/logo.png"));  //设置Logo
    //a.setProductName("DtkDemo");
    a.setApplicationName("锐捷linux有线认证GUI辅助"); //只有在这儿修改窗口标题才有效

    a.setWindowIcon(QIcon(":/image/resource/icon.png"));

    MainWindow w(nullptr);
    w.show();

    //让打开时界面显示在正中
    Dtk::Widget::moveToCenter(&w);

    return a.exec();
}

