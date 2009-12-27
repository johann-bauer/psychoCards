#define DURATION 2000

#include <QDebug>
#include "card.h"

Card::Card( QString filename, QGraphicsItem *parent) :
    QGraphicsSvgItem(filename, parent)
{
   timeLineX = new QTimeLine(DURATION,this);
   timeLineY = new QTimeLine(DURATION,this);

   connect(timeLineX, SIGNAL(frameChanged(int)), this, SLOT(moveItemX(int)));
   connect(timeLineY, SIGNAL(frameChanged(int)), this, SLOT(moveItemY(int)));

   scale(0.7,0.7);
}

/*
QVariant Card::itemChange ( GraphicsItemChange change, const QVariant & value ) {
   return QGraphicsItem::itemChange(change, value);
}
*/

void Card::moveItemX( int x) {
   this->setPos( x, this->y());
}

void Card::moveItemY( int y) {
   this->setPos(this->x(), y);
}

void Card::moveAnimated( int x, int y) {
   timeLineX->setFrameRange( this->x(), x );
   timeLineY->setFrameRange( this->y(), y );

   timeLineX->start();
   timeLineY->start();
}
