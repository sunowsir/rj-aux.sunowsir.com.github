#include "loginwidget.h"


loginWidget::loginWidget(QMainWindow *parent) : QWidget(parent)
{
    
    this->settings = new QSettings(QString(QCoreApplication::applicationDirPath() +
                                           "/Config.ini" + "/Config.ini"),
                                   QSettings::IniFormat);
    qDebug() << QCoreApplication::applicationDirPath() + "/Config.ini";

    this->parent = parent;


    this->default_account = runProOnce(QString(QCoreApplication::applicationDirPath() + "/getLastAccount"));
    this->default_password = "******";

    /* account label */

    this->account_label = new QLabel(this);
    this->account_label->setText(tr("账号"));
    this->account_label->move(200, 150);


    /* account line edit  */

    this->account_input = new QLineEdit(this);
    this->account_input->setText(this->account = this->default_account);
    // this->lineedit_acco_num->setPlaceholderText("please input account");
    this->account_input->move(260, 145);


    /* password label */

    this->password_label = new QLabel(this);
    this->password_label->setText(tr("密码"));
    this->password_label->move(200, 210);


    /* password line edit */

    this->password_input = new QLineEdit(this);
    this->password_input->setEchoMode(QLineEdit::Password);
    this->password_input->setText(this->password = default_password);
    // this->passwordedit_pass_num->setPlaceholderText("please input password");
    this->password_input->move(260, 205);





    /* netcard */

    RefreshNetCard();

    /* net card label */
    this->netcard_label = new QLabel(this);
    this->netcard_label->setText(tr("网卡"));
    this->netcard_label->move(200, 270);

    /* choose net card QComboBox */
    this->netcard_combox = new QComboBox(this);
    this->netcard_combox->move(260, 265);
    this->netcard_combox->addItems(this->netcard_list);





    /*  password checkbox  */
    this->settings->beginGroup("CheckBox");
    bool default_mstatus = this->settings->value("memory_checkbox").toInt();
    this->settings->endGroup();
    this->memory_checkbox = new QCheckBox(this);
    this->memory_checkbox->move(200, 320);
    this->memory_checkbox->setChecked(default_mstatus);


    /* password checkbox label */
    this->memory_label = new QLabel(this);
    this->memory_label->setText(tr("记住密码"));
    this->memory_label->move(230, 320);



    /* auto login checkbox  */
    this->settings->beginGroup("CheckBox");
    bool default_lstatus = this->settings->value("auto_checkbox").toInt();
    this->settings->endGroup();
    this->auto_checkbox = new QCheckBox(this);
    this->auto_checkbox->move(320, 320);
    this->auto_checkbox->setChecked(default_lstatus);


    /* auto login checkbox label */
    this->auto_label = new QLabel(this);
    this->auto_label->setText(tr("自动登陆"));
    this->auto_label->move(350, 320);



    this->ShowInfoMaster = new ShowInfoWidget(this);


    this->rund_status = false;
    this->process = nullptr;
    this->pro_args = QStringList(QStringList() << "-a"
                                     << "1"
                                     << "-d"
                                     << "0"
                                     << "-u"
                                     << this->account
                                     << "-n"
                                     << this->netcard);

    /* confirm button */
    this->button_confirm = new QPushButton(this);
    this->button_confirm->setText(tr("认证"));
    this->button_confirm->move(260, 385);

    /* connect signal with slot */

    QWidget::connect(this->account_input, SIGNAL(textChanged(QString)),
                      this, SLOT(getAccountInput(QString)),
                      Qt::AutoConnection);
    QWidget::connect(this->password_input, SIGNAL(textChanged(QString)),
                      this, SLOT(getPasswordInput(QString)),
                      Qt::AutoConnection);
    QWidget::connect(this->netcard_combox, SIGNAL(activated(const QString&)),
                      this, SLOT(getNetCardChoice(QString)),
                      Qt::AutoConnection);
    QWidget::connect(this->button_confirm, SIGNAL(released()),
                      this, SLOT(triggerlogin()),
                      Qt::AutoConnection);
    
    if (default_lstatus) {
        triggerlogin();
    }

}

loginWidget::~loginWidget() {
    if (this->rund_status) {
        if (this->process != nullptr) {
            runProOnce("./rjsupplicant.start", QStringList() << "-q");
        }
        // restart network;
        runProOnce("systemctl", QStringList() << "restart" << "NetworkManager.service");
    }
}



void loginWidget::triggerlogin() {

    if (!this->rund_status) this->rund_status = true;
    

    this->ShowInfoMaster->clear();

    if (this->process == nullptr) {
        this->process = new QProcess(this);
    } else {
        runProOnce("./rjsupplicant.start", QStringList() << "-q");
        this->process->kill();
        this->process->close();
    }

    if (this->pro_args[5] != this->account)
        this->pro_args.replace(5, this->account);
    if (this->pro_args[7] != this->netcard)
        this->pro_args.replace(7, this->netcard);


    /* get checkbox status && judge user input status */

    if (this->account != this->default_account ||
         this->password != this->default_password) {
        if (this->getMCheckStatus()) {
            this->pro_args.append(QStringList() << "-S" << "1");
        }
        this->pro_args.append(QStringList()<< "-p" << this->password);
    }


    /* start run the rjsupplicant.start program. */

    this->process->setWorkingDirectory(QCoreApplication::applicationDirPath());
    this->process->start("./rjsupplicant.start", this->pro_args);
    this->process->waitForStarted();


    /* connect signal with slot. */

    QObject::connect(this->process, SIGNAL(readyReadStandardOutput()),
                      this, SLOT(getProOutput()));
    // QObject::connect(this->process, SIGNAL(readyReadStandardError()),
    //                   this, SLOT(getProErrout()));
    //


    /* save memory password checkbox status.  */
    this->settings->beginGroup("CheckBox");
    this->settings->setValue("memory_checkbox", this->memory_checkbox->checkState());
    this->settings->endGroup();

    /* save auto login checkbox status.  */
    this->settings->beginGroup("CheckBox");
    this->settings->setValue("auto_checkbox", this->auto_checkbox->checkState());
    this->settings->endGroup();

}


QString loginWidget::runProOnce(QString pro_name, QStringList arg) {

    QString ret;

    if (pro_name.isEmpty()) {
        ret.clear();
        return ret;
    }

    QProcess pro;
    pro.setWorkingDirectory(QCoreApplication::applicationDirPath());
    pro.start(pro_name, arg);
    pro.waitForFinished();
    ret = pro.readAllStandardOutput();
    pro.kill();
    pro.close();

    return ret;
}

void loginWidget::RefreshNetCard() {

    this->netcard.clear();
    this->netcard_list.clear();

    foreach (QNetworkInterface i, QNetworkInterface::allInterfaces()) {
        if (i.flags().testFlag(QNetworkInterface::IsLoopBack)) continue;
        QString cardname = i.name();

        if (!cardname.isEmpty() &&
             cardname.startsWith("e", Qt::CaseInsensitive)) {
             this->netcard.append(cardname);
             continue;
        }
        this->netcard_list.append(cardname);
    }

    if (!this->netcard.isEmpty()) {
        this->netcard_list.insert(0, this->netcard);
    } else {
        this->netcard.append(this->netcard_list[0]);
    }

}

bool loginWidget::getMCheckStatus() {
    return this->memory_checkbox->checkState();
}

bool loginWidget::getLCheckStatus() {
    return this->auto_checkbox->checkState();
}




/* slot */

void loginWidget::getProOutput() {

    QString retStr = QString::fromLocal8Bit(
                process->readAllStandardOutput()).replace(QString("\n"), QString(""));

    if (retStr.isEmpty()) return;
    this->ShowInfoMaster->append(retStr);


    if (retStr.contains(QString("成功"))) {
        // restart network;
        runProOnce(QString("systemctl"), QStringList() << "restart" << "NetworkManager.service");
        // this->ShowInfoMaster->setText(retStr);
        
        // QMessageBox::information(nullptr, "登录成功", "登录面板已隐藏到托盘");

        runProOnce(QString("./notify"));

		this->parent->hide();
    }
}

void loginWidget::getProErrout() {

    QString errStr = process->readAllStandardError().data();
    if (!QRegExp("\\s*").exactMatch(errStr) &&
         !errStr.contains("sysctl") &&
         !errStr.contains("write error") &&
         !errStr.contains("错误的文件描述符")
    ) {
        QMessageBox::information(nullptr, "Error", errStr);
    }
}


void loginWidget::getAccountInput(const QString& inputstr) {
    this->account = inputstr;
}

void loginWidget::getPasswordInput(const QString& inputstr) {
    this->password = inputstr;
}

void loginWidget::getNetCardChoice(const QString& choice_str) {
    this->netcard = choice_str;
}


