#ifndef CARD_H
#define CARD_H

#define DURATION 2000
#define SCALE 0.7

#include <QGraphicsSvgItem>
#include <QTimeLine>

class Card : public QGraphicsSvgItem
{
Q_OBJECT
public:
    explicit Card(QString filename, QGraphicsItem *parent = 0);
    void moveAnimated( int x, int y);
    void scaleAnimated( int x, int y);

signals:

 public slots:
    void moveItemX( int );
    void moveItemY( int );
    void scaleItem( int x );

protected:
    virtual void hoverEnterEvent ( QGraphicsSceneHoverEvent * event );

private:
    QTimeLine *timeLineX;
    QTimeLine *timeLineY;
    QTimeLine *timeLineS;

};

#endif // CARD_H
