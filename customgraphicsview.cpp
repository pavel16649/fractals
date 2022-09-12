#include "customgraphicsview.h"

CustomGraphicsView::CustomGraphicsView(QWidget* parent)
    : QGraphicsView(parent)
    , scene(new QGraphicsScene)
    , cur_rect(nullptr)
    , pixmap(nullptr)
    , cursor_pos_x(0)
    , cursor_pos_y(0)
    , cur_x(0)
    , cur_y(0)
    , scale(1)
{
    setScene(scene);
}

void CustomGraphicsView::wheelEvent(QWheelEvent *event)
{
//    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
//    long double scaleFactor = 1.05;

//    if (event->delta() > 0) {
//        scale(scaleFactor, scaleFactor);
//    } else {
//        scale(1/scaleFactor, 1/scaleFactor);
    //    }
}

void CustomGraphicsView::mousePressEvent(QMouseEvent *event)
{
    cursor_pos_x = event->x();
    cursor_pos_y = event->y();
}

void CustomGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    long double mWidth = this->geometry().width();
    long double mHeight = this -> geometry().height();

    if (event->button() == Qt::LeftButton) {
        if (cursor_pos_x < event->x() && cursor_pos_y < event->y()) {
            emit signalReleased(cursor_pos_x / scale, cursor_pos_y / scale, event->x() / scale, event->y() / scale);

            cur_x += cursor_pos_x / scale;
            cur_y += cursor_pos_y / scale;
            long double w =  (event->x() - cursor_pos_x) / scale;
            long double h =  (event->y() - cursor_pos_y) / scale;
            scale = std::min(this->geometry().width() / w, this->geometry().height() / h);
        }
    } else {
        if (scale <= 1.1) return;

        long double w =  mWidth / scale;
        long double h =  mHeight / scale;

        emit signalReleased(-w / 2, -h / 2, 3 * w / 2, 3 * h / 2);

        cur_x = std::max(cur_x - w / 2, 0.0L);
        cur_y = std::max(cur_y - h / 2, 0.0L);

        scale = std::max(scale / 2, 1.0L);
    }
}

void CustomGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    emit signalMove(event->x(), event->y());
}
