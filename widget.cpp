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

void Widget::mixCards( void ) {

}

void Widget::createCards( void ) {
   int space = 10;
   int i, width;

   Card *tmp;
   for( i = 0; i < 21; i++ ) {
      QString filename = QString("./pix/%1.svg").arg(i);
      tmp = new Card( filename );
      m_cards.insert(i,tmp);
      scene->addItem(tmp);
      m_stack.push(i); //if stack is full. all cards are on the hand
   }
   qDebug() << "Nummer of cards: " << m_cards.count();



}

void Widget::resizeEvent ( QResizeEvent * /*event*/ ) {
//   qDebug() << "resize";
//   ui->graphicsView->fitInView( this->scene->sceneRect(), Qt::KeepAspectRatio);
}

void Widget::keyPressEvent ( QKeyEvent * event ) {
   qDebug() << "key pressed";
   mixCards();

   /*
   switch ( event->key() ) {
   case Qt::Key_W: card->moveAnimated( card->x() , card->y() - 100); break;
   case Qt::Key_S: card->moveAnimated( card->x(), card->y() + 100); break;
   case Qt::Key_A: card->moveAnimated( card->x() - 100, card->y() ); break;
   case Qt::Key_D: card->moveAnimated( card->x() + 100, card->y() ); break;
   default: mixCards();
   }*/
}

void Widget::moveByX( int x) {
   card->setPos( x, card->y() );;
   qDebug() << x;
}


void Widget::moveByY( int y ) {
   card->setPos( card->x(), y);
}

void Widget::giveCards( int row ) {
   int width,i;
   int space = 10;
   Card *tmp;
   QMapIterator<int, Card*> iterator(m_cards);
   if( m_stack.count() != m_cards.count() )
      qDebug() << "FATAL: Stack aint got the same card count";

   while( !m_stack.empty() ) {
      i = m_stack.pop();
      tmp = m_cards.value(i);
      width = tmp->boundingRect().width();
      tmp->moveAnimated( ( i % 3 ) * ( width + space ) ,
                           i / 3 * 80);
      tmp->setFlags( QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable );
      tmp->setZValue( i );
      tmp->setData( 0 , i );
   }

   qDebug() << "end of giveCards. stackCount: " << m_stack.count();
}

