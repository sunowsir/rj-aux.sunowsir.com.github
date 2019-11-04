#include "netcardwidget.h"

NetCardWidget::NetCardWidget(QWidget *parent) : QWidget(parent)
{

    RefreshNetCard();

    /* net card label */
    this->netcard_label = new DLabel( this );
    this->netcard_label->setText( "网卡" );
    this->netcard_label->move( 200, 270 );

    /* choose net card QComboBox */
    this->netcard_combox = new QComboBox( this );
    this->netcard_combox->move( 260, 265 );
    this->netcard_combox->addItems( this->netcard_list );

    QWidget::connect( this->netcard_combox, SIGNAL( activated( const QString& ) ),
                      this, SLOT( getNetCardChoice( QString ) ),
                      Qt::AutoConnection );

}

void NetCardWidget::RefreshNetCard() {

    this->netcard.clear();
    this->netcard_list.clear();

    foreach ( QNetworkInterface i, QNetworkInterface::allInterfaces() ) {
        if ( i.flags().testFlag( QNetworkInterface::IsLoopBack ) ) continue;
        QString cardname = i.name();

        if ( !cardname.isEmpty() &&
             cardname.startsWith( "e", Qt::CaseInsensitive ) ) {
             this->netcard.append( cardname );
             continue;
        }
        this->netcard_list.append( cardname );
    }

    if ( !this->netcard.isEmpty() ) {
        this->netcard_list.insert( 0, this->netcard );
    } else {
        this->netcard.append( this->netcard_list[0] );
    }

}

QString NetCardWidget::getNetcard() {
    RefreshNetCard();
    return this->netcard;
}



/* slot */

void NetCardWidget::getNetCardChoice( const QString& choice_str ) {
    this->netcard = choice_str;
}










