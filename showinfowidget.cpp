#include "showinfowidget.h"

ShowInfoWidget::ShowInfoWidget(QWidget *parent) : QWidget(parent)
{
    /* QTextEdit : show information */
    this->show_edit = new QTextEdit( this );
    this->show_edit->setReadOnly( true );
    this->show_edit->resize( 640, 120 );
    this->show_edit->move( 0, 0 );
}

void ShowInfoWidget::clear() {
    this->show_edit->clear();
}

void ShowInfoWidget::append( const QString& str) {
    this->show_edit->append(str);
}

void ShowInfoWidget::setText( const QString& str ) {
    this->show_edit->setText(str);
}
