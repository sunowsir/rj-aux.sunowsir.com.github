#ifndef SHOWINFOWIDGET_H
#define SHOWINFOWIDGET_H

#include <QWidget>
#include <QString>
#include <qtextedit.h>

class ShowInfoWidget : public QWidget
{
    Q_OBJECT

    QTextEdit       *show_edit;

public:
    explicit ShowInfoWidget(QWidget *parent = nullptr);
    void clear();
    void append( const QString& );
    void setText( const QString& );

signals:

public slots:
};

#endif // SHOWINFOWIDGET_H

