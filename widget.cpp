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
//    rectItem = scene->addRect(scene->sceneRect());
    ui->graphicsView->setScene( scene );
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);

//    card = new QGraphicsSvgItem( "./pix/1.svg");
//    scene->addItem( card );

    this->createCards();

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
   int space = 10;


}

void Widget::createCards( void ) {
   int i, width, dx,dy;
   int space = 10;

   Card *tmp;
   for( i = 0; i < 21; i++ ) {
      QString filename = QString("./pix/%1.svg").arg(i);
      tmp = new Card( filename );
      card = tmp;
      scene->addItem(tmp);
      width = tmp->boundingRect().width();
      tmp->moveAnimated( ( i % 3 ) * ( width + space ) , i/3 * 80);
//      tmp->moveBy( ( i % 3 ) * ( width + space ) , i/3 * 80);
      tmp->setData( 0 , i );
      tmp->setFlags( QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable );
      tmp->setZValue( i );

   }
//    ui->graphicsView->fitInView( rectItem );

}

void Widget::resizeEvent ( QResizeEvent * /*event*/ ) {
//   qDebug() << "resize";
//   ui->graphicsView->fitInView( this->scene->sceneRect(), Qt::KeepAspectRatio);
}

void Widget::keyPressEvent ( QKeyEvent * event ) {
   qDebug() << "key pressed";
   //   mixCards();
   //   card->moveAnimated(200, 200);
   if( event->key() == Qt::Key_Up )
      qDebug() << "yeah";
   switch ( event->key() ) {
   case Qt::Key_W: card->moveAnimated( card->x() , card->y() - 100); break;
   case Qt::Key_S: card->moveAnimated( card->x(), card->y() + 100); break;
   case Qt::Key_A: card->moveAnimated( card->x() - 100, card->y() ); break;
   case Qt::Key_D: card->moveAnimated( card->x() + 100, card->y() ); break;
   default: mixCards();
   }
}

void Widget::moveByX( int x) {
   card->setPos( x, card->y() );;
   qDebug() << x;
}


void Widget::moveByY( int y ) {
   card->setPos( card->x(), y);
}
