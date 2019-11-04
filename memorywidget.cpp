#include "memorywidget.h"

MemoryWidget::MemoryWidget(QWidget *parent) : QWidget(parent)
{
    /*  password checkbox  */
    this->memory_checkbox = new QCheckBox( this );
    this->memory_checkbox->move( 200, 320 );
    this->memory_checkbox->setChecked( true );


    /* password checkbox label */
    this->memory_label = new DLabel( this );
    this->memory_label->setText( "记住密码" );
    this->memory_label->move( 230, 320 );

}

bool MemoryWidget::getCheckStatus() {
    return this->memory_checkbox->checkState();
}
