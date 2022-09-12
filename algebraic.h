#ifndef ALGEBRAIC_H
#define ALGEBRAIC_H

#include <QWidget>
#include <QGraphicsScene>
#include <QDebug>

#include "complex.h"

namespace Ui {
class Algebraic;
}

class Algebraic : public QWidget
{
    Q_OBJECT

public:
    explicit Algebraic(QWidget *parent = nullptr);
    ~Algebraic();

private slots:
    void Draw(long double, long double, long double, long double);
    void DrawRect(long double, long double);

    void on_pushButton_clicked();

signals:
    void signal();

private:
    Ui::Algebraic *ui;
    QPen* pen;
    QBrush* brush;
    double prev_height;
    double prev_width;

    void closeEvent(QCloseEvent *event);
};

#endif // ALGEBRAIC_H
