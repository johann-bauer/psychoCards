#define DURATION 2000

#include <QDebug>
#include "card.h"

Card::Card( QString filename, QGraphicsItem *parent) :
    QGraphicsSvgItem(filename, parent)
{
   this->setAcceptHoverEvents(true);
   timeLineX = new QTimeLine( DURATION, this );
   timeLineY = new QTimeLine( DURATION, this );

   connect( timeLineX, SIGNAL( frameChanged( int ) ), this, SLOT( moveItemX( int ) ) );
   connect( timeLineY, SIGNAL( frameChanged( int ) ), this, SLOT( moveItemY( int ) ) );

   scale( 0.7, 0.7 );
}

void Card::moveItemX( int x ) {
   this->setPos( x, this->y());
}

void Card::moveItemY( int y ) {
   this->setPos( this->x(), y );
}

void Card::moveAnimated( int x, int y) {
   timeLineX->setFrameRange( this->x(), x );
   timeLineY->setFrameRange( this->y(), y );

   timeLineX->start();
   timeLineY->start();
}

void Card::hoverEnterEvent ( QGraphicsSceneHoverEvent * event ) {
   int i = this->data(0).toInt();
   int x = i % 3;
   int y = i / 3;
   qDebug() << "Card Position: " << x << "," << y;
}
