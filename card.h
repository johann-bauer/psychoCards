#ifndef CARD_H
#define CARD_H

#include <QGraphicsSvgItem>
#include <QTimeLine>

class Card : public QGraphicsSvgItem
{
Q_OBJECT
public:
    explicit Card(QString filename, QGraphicsItem *parent = 0);
    void moveAnimated( int x, int y);

signals:

 public slots:
    void moveItemX( int );
    void moveItemY( int );

//protected:
//    virtual QVariant itemChange ( GraphicsItemChange change, const QVariant & value );

private:
    QTimeLine *timeLineX;
    QTimeLine *timeLineY;
    bool lock;
};

#endif // CARD_H
