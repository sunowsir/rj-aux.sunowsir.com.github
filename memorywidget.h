#ifndef MEMORYWIDGET_H
#define MEMORYWIDGET_H

#include <QWidget>
#include <QCheckBox>

#include <dlabel.h>

DWIDGET_USE_NAMESPACE

class MemoryWidget : public QWidget
{
    Q_OBJECT

    DLabel          *memory_label;
    QCheckBox       *memory_checkbox;

public:

    explicit MemoryWidget(QWidget *parent = nullptr);
    bool getCheckStatus();

signals:

public slots:

};

#endif // MEMORYWIDGET_H
