#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMap>
#include <QUrl>

class QGraphicsSvgItem;
class QGraphicsScene;

namespace Ui {
    class Widget;
}

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void changeEvent(QEvent *e);
    void resizeEvent ( QResizeEvent * event );
    void keyPressEvent ( QKeyEvent * event );

private:
    Ui::Widget *ui;

    QMap<int,QUrl> m_cards;
    QGraphicsSvgItem *card;
    QGraphicsScene *scene;

    void mixCards( void );
};

#endif // WIDGET_H
