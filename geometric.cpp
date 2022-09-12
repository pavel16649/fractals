#include "geometric.h"
#include "ui_geometric.h"

Geometric::Geometric(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Geometric),
    step(0)
{
    ui->setupUi(this);
    scene_rect = new QGraphicsScene;
    scene_triangle = new QGraphicsScene;
    ui->graphicsView->setScene(scene_rect);
}

Geometric::~Geometric()
{
    delete this->ui;
}

void Geometric::on_pushButton_2_clicked()
{
    if (step != 7)
        ++step;
    Redraw();
}


void Geometric::on_tabWidget_tabBarClicked(int index)
{
    if (index == 0) {
        ui->graphicsView->setScene(scene_rect);
    } else {
        ui->graphicsView->setScene(scene_triangle);
    }
}

void Geometric::Redraw()
{
    {
        RedrawRect(0, 0, k_RECT_SIZE, k_RECT_SIZE, 0);
    }

    {

    }
}

void Geometric::closeEvent(QCloseEvent *event)
{
     emit signal();
}

void Geometric::RedrawRect(double x, double y, double width, double height, int deep)
{
    if (deep > step) return;
    if (deep == 0) {
        RedrawRect(0, 0, k_RECT_SIZE, k_RECT_SIZE, 1);
        return;
    } else if (deep == 1) {
        scene_rect->addRect(0, 0, k_RECT_SIZE, k_RECT_SIZE, QPen(Qt::black), QBrush(Qt::black));
        RedrawRect(0, 0, k_RECT_SIZE, k_RECT_SIZE, 2);
        return;
    }

    double new_height = height / 3;
    double new_width = width / 3;
    scene_rect->addRect(x + new_width, y + new_height, new_width, new_height, QPen(Qt::white), QBrush(Qt::white));
    QVector <double> dx = {x, x + new_width, x + new_width * 2};
    QVector <double> dy = {y, y + new_height, y + new_height * 2};
    for (auto yy : dy) {
        for (auto xx : dx) {
            RedrawRect(xx, yy, new_width, new_height, deep + 1);
        }
    }
}

void Geometric::on_pushButton_clicked()
{
    if (step != 0)
        --step;

    if (step == 0) {
        scene_rect->clear();
        scene_triangle->clear();
    }
    Redraw();
}
