#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>
#include <QImage>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QObject>
#include <QGraphicsPixmapItem>

class CustomGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    CustomGraphicsView(QWidget* parent = 0);
    QImage* image;
    QGraphicsScene* scene;
    QGraphicsRectItem* cur_rect;
    QGraphicsPixmapItem* pixmap;

    long double get_cur_x() { return cur_x; }
    long double get_cur_y() { return cur_y; }
    long double get_scale() { return scale; }
    long double get_cursor_x() { return cursor_pos_x; }
    long double get_cursor_y() { return cursor_pos_y; }

signals:
    void signal2(long double);
    void signalReleased(long double, long double, long double, long double);
    void signalMove(long double, long double);

protected:
    virtual void wheelEvent(QWheelEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

    long double cursor_pos_x;
    long double cursor_pos_y;

    long double cur_x;
    long double cur_y;

    long double scale;
};

#endif // CUSTOMGRAPHICSVIEW_H
