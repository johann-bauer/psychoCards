#define NEWPOS 0
#define OLDPOS 1

#include "widget.h"
#include "card.h"
#include "ui_widget.h"

#include <QDebug>
#include <QList>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSvgItem>
#include <QSvgRenderer>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QTimeLine>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0,0,500,500);
    ui->graphicsView->setScene( scene );
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);

    createHelp();

    run = 0;
    this->createCards();
    this->giveCards();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Widget::mixCards( int col) {
   //there are 3 ways to collect the cards. THE chosen col is left. center or right.
   // so we have to fill the stack the right way.
   int i;

   //FIXME: there have to be a way to get this shorter (and smarter :)
   switch( col ) {
   case 1:

      //collect center col
      for( i = 1; i < 21; i += 3)
         m_stack.push(i);
      //collect left col
      for( i = 0; i < 21; i += 3)
         m_stack.push(i);
      //collect right col
      for( i = 2; i < 21; i += 3)
         m_stack.push(i);
      break;
   case 2:

      //collect left col
      for( i = 0; i < 21; i += 3)
         m_stack.push(i);
      //collect center col
      for( i = 1; i < 21; i += 3)
         m_stack.push(i);
      //collect right col
      for( i = 2; i < 21; i += 3)
         m_stack.push(i);
      break;
   case 3:

      //collect left col
      for( i = 0; i < 21; i += 3)
         m_stack.push(i);
      //collect right col
      for( i = 2; i < 21; i += 3)
         m_stack.push(i);
      //collect center col
      for( i = 1; i < 21; i += 3)
         m_stack.push(i);
      break;

   }

//   qDebug() << "STACK: " << m_stack;

   /*foreach( Card *tmpCard, m_cards ) {
      tmpCard->moveAnimated(-500,500);
   }*/


   this->giveCards();
}

void Widget::createCards( void ) {
   int i;

   Card *tmp;
   for( i = 0; i < 21; i++ ) {
      QString filename = QString("./pix/%1.svg").arg(i);
      tmp = new Card( filename );
      tmp->setPos(-500,500);
      m_cards.insert(i,tmp);
      scene->addItem(tmp);
      tmp->setData( OLDPOS , i );
      m_stack.push(i); //if stack is full. all cards are on the hand
                         // the nummer identify the card.
   }
}

void Widget::resizeEvent ( QResizeEvent * /*event*/ ) {
//   qDebug() << "resize";
//   ui->graphicsView->fitInView( this->scene->sceneRect(), Qt::KeepAspectRatio);
}

void Widget::keyPressEvent ( QKeyEvent * event ) {
   int col = event->key() - 48;
   if( col >= 1 && col <=3)
      mixCards( col );
   else if(event->key() == Qt::Key_R )
      restartGame();
}

void Widget::moveByX( int x) {
   card->setPos( x, card->y() );;
}


void Widget::moveByY( int y ) {
   card->setPos( card->x(), y);
}

void Widget::giveCards( void ) {
   int width, cardNr;
   int space = 10;
   int i = 0;
   Card *tmp;

   if( m_stack.count() != m_cards.count() )
      qDebug() << "FATAL: Stack aint got the same card count";

   while( !m_stack.empty() ) {
      cardNr = m_stack.pop();
      tmp = findCardOnPos( cardNr );
      width = tmp->boundingRect().width(); //FIXME
      tmp->moveAnimated( ( i % 3 ) * ( width + space ) ,
                           i / 3 * 60);
      tmp->setFlags( QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable );
      tmp->setZValue( i );
      tmp->setData( NEWPOS , i );
      i++;
   }

   foreach( Card *tmpCard, m_cards ) {
      tmpCard->setData(OLDPOS, tmpCard->data(NEWPOS)) ;
   }

   if( run >= 3) {
      endOfGame();
   }
   run++;

}

Card * Widget::findCardOnPos( int pos ) {
   Card *returnCard = NULL;
   foreach( Card *tmpCard, m_cards ) {
      if( tmpCard->data( OLDPOS ).toInt() == pos ) {
         returnCard = tmpCard;
      }
   }
   if( !returnCard )
      qDebug () << "FATAL: Card not found. nr:" << pos ;
   return returnCard;
}

void Widget::endOfGame( void ) {
   Card *yourCard = findCardOnPos(10);
   yourCard->setZValue(100);
//   yourCard->scale(2,2);
   yourCard->scaleAnimated( 2 );
}

void Widget::restartGame( void ) {
   run = 0;
   foreach( Card *tmpCard, m_cards ) {
      tmpCard->resetTransform();
      tmpCard->scale( SCALE, SCALE );
   }
   mixCards(3);
}

void Widget::createHelp( void ) {
   QGraphicsTextItem *helpText = scene->addText("Choose a card and tell me in which column it is. Press 1, 2, 3, R: Restart");
   helpText->moveBy(0,-30);
}
