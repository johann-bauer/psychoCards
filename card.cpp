#include <QDebug>
#include "card.h"

Card::Card( QString filename, QGraphicsItem *parent) :
    QGraphicsSvgItem(filename, parent)
{
   timeLineX = new QTimeLine( DURATION, this );
   timeLineY = new QTimeLine( DURATION, this );
   timeLineS = new QTimeLine( DURATION, this );

   connect( timeLineX, SIGNAL( frameChanged( int ) ), this, SLOT( moveItemX( int ) ) );
   connect( timeLineY, SIGNAL( frameChanged( int ) ), this, SLOT( moveItemY( int ) ) );
   connect( timeLineS, SIGNAL( frameChanged( int ) ), this, SLOT( scaleItem( int ) ) );

   scale( SCALE, SCALE );
}

void Card::moveItemX( int x ) {
   this->setPos( x, this->y());
}

void Card::moveItemY( int y ) {
   this->setPos( this->x(), y );
}


void Card::scaleItem( int x ) {
   QTransform tr;
   tr.translate(this->boundingRect().width()/2.0,this->boundingRect().width()/2.0);
   tr.scale(x/100.0,x/100.0);
   tr.translate( -this->boundingRect().width()/2.0, -this->boundingRect().width()/2.0);

   setTransform(tr);

}

void Card::moveAnimated( int x, int y) {
   if( timeLineX->state() == QTimeLine::Running)
      return;
   if( timeLineY->state() == QTimeLine::Running)
      return;

   timeLineX->setFrameRange( this->x(), x );
   timeLineY->setFrameRange( this->y(), y );

   timeLineX->start();
   timeLineY->start();
}

void Card::scaleAnimated( int x ) {
   timeLineS->setFrameRange( SCALE*100 , x*100 );
   timeLineS->start();
}

