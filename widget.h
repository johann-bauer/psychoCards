#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMap>
#include <QUrl>
#include <QTimeLine>
#include <QStack>

class QGraphicsSvgItem;
class QGraphicsRectItem;

class QGraphicsScene;
class QTimeLine;

class Card;

namespace Ui {
    class Widget;
}

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
    ~Widget();

 public slots:
    void moveByX( int );
    void moveByY( int );

protected:
    void changeEvent(QEvent *e);
    void resizeEvent ( QResizeEvent * event );
    void keyPressEvent ( QKeyEvent * event );

private:
    Ui::Widget *ui;

    QMap<int,Card*> m_cards;
    Card *card;
    QGraphicsScene *scene;
    QGraphicsRectItem *rectItem;
    QStack<int> m_stack;

    void mixCards( void );
    void createCards( void );
    void giveCards( int row = 0 );
};

#endif // WIDGET_H
