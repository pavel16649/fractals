#ifndef GEOMETRIC_H
#define GEOMETRIC_H

#include <QWidget>
#include <QGraphicsScene>
#include <QVector>
#include "customgraphicsview.h"

namespace Ui {
class Geometric;
}

class Geometric : public QWidget
{
    Q_OBJECT

public:
    explicit Geometric(QWidget *parent = nullptr);
    ~Geometric();

private slots:
    void on_pushButton_2_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_pushButton_clicked();

signals:
    void signal();

private:
    Ui::Geometric *ui;

    const double k_RECT_SIZE = 600;
    int step;
    QGraphicsScene *scene_rect, *scene_triangle;

    void Redraw();

    void closeEvent(QCloseEvent *event);

    void RedrawRect(double, double, double, double, int);
};

#endif // GEOMETRIC_H
