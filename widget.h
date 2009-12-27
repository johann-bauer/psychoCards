#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMap>
#include <QUrl>
#include <QTimeLine>

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

    QMap<int,QUrl> m_cards;
    Card *card;
    QGraphicsScene *scene;
    QGraphicsRectItem *rectItem;

    void mixCards( void );
    void createCards( void );
};

#endif // WIDGET_H
