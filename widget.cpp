#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSvgItem>
#include <QKeyEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    ui->graphicsView->setScene( scene );

//    card = new QGraphicsSvgItem( "./pix/1.svg");
//    scene->addItem( card );

    this->mixCards();
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
   int i, width;
   int space = 10;
   QGraphicsSvgItem *tmp;
   for( i = 0; i < 21; i++ ) {
      QString filename = QString("./pix/%1.svg").arg(i);
      qDebug() << filename;
      tmp = new QGraphicsSvgItem( filename );
      scene->addItem(tmp);
      width = tmp->boundingRect().width();
      tmp->moveBy( ( i % 3 ) * ( width + space ) , i/3 * 80);
      tmp->setData( 0 , i );
      tmp->setFlags( QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable );
      tmp->setZValue( i );

   }
}

void Widget::resizeEvent ( QResizeEvent * event ) {
//   qDebug() << "resize";
//   ui->graphicsView->fitInView( this->card, Qt::KeepAspectRatio);
}

void Widget::keyPressEvent ( QKeyEvent * event ) {
   mixCards();
}
