#ifndef STOCHASTIC_H
#define STOCHASTIC_H

#include <QWidget>
#include <QGraphicsScene>
#include <QImage>
#include "customgraphicsview.h"
#include <random>

namespace Ui {
class Stochastic;
}

class Stochastic : public QWidget
{
    Q_OBJECT

public:
    explicit Stochastic(QWidget *parent = nullptr);
    ~Stochastic();

signals:
    void signal();

private slots:
    void on_pushButton_clicked();

    void RecursiveFillRect(QImage &image, double x, double y, double size, QColor colorLU, QColor colorRU, QColor colorRD, QColor colorLD);
private:
    Ui::Stochastic *ui;
    QGraphicsScene *scene;
    QImage *image;

    void closeEvent(QCloseEvent *event);
};

#endif // STOCHASTIC_H
