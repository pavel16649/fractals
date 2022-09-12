#include "algebraic.h"
#include "ui_algebraic.h"

Algebraic::Algebraic(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Algebraic)
    , pen(new QPen(Qt::black))
    , brush(new QBrush(QColor(0, 0, 255, 20)))
{
    ui->setupUi(this);
    ui->graphicsView->image = new QImage(ui->graphicsView->geometry().width(),
                                         ui->graphicsView->geometry().height(),
                                         QImage::Format_RGB32);
    connect(ui->graphicsView, SIGNAL(signalReleased(long double, long double, long double, long double)), this, SLOT(Draw(long double, long double, long double, long double)));
    connect(ui->graphicsView, SIGNAL(signalMove(long double, long double)), this, SLOT(DrawRect(long double, long double)));
}

Algebraic::~Algebraic()
{
    delete ui;
}

void Algebraic::Draw(long double xl, long double yl, long double xr, long double yr)
{

    //qDebug() << "12345678";
    xl +=  ui->graphicsView->get_cur_x();
    xr += ui->graphicsView->get_cur_x();
    yl +=  ui->graphicsView->get_cur_y();
    yr += ui->graphicsView->get_cur_y();

    long double form_width = ui->graphicsView->geometry().width();
    long double form_height = ui->graphicsView->geometry().height();

    long double width = xr - xl, height = yr - yl;
    long double scale =  std::min(ui->graphicsView->geometry().width() / width, ui->graphicsView->geometry().height() / height);

    for (int i = 0; i < form_width; ++i) {
        for (int j = 0; j < form_height; ++j) {
             ui->graphicsView->image->setPixelColor(i, j, Qt::white);
        }
    }

    for (long double i = xl, di = 1.0 / scale; (i - xl) * scale < form_width;  i += di) {
        for (long double j = yl, dj = 1.0 / scale; (j - yl) * scale < form_height;  j += dj) {

            long double x = i - form_width / 2;
            long double y = form_height / 2 - j;

            x = x / 150;
            y = y / 150;

            Complex z(0, 0);
            Complex c(x, y);

            int it = -1;
            int inf = 10;
            int iterations = 100;

            for (int n = 0; n < iterations; ++n) {
                z = (z * z) + c;
                if (z.mod() > inf) {
                    it = n;
                    break;
                }
            }

            if (it == -1) {
               ui->graphicsView->image->setPixelColor((i - xl) * scale, (j - yl) * scale, QColor(Qt::black));
            } else {
               ui->graphicsView->image->setPixelColor((i - xl) * scale, (j - yl) * scale, QColor(255 - 6*it, 255 - 4*it, 255 - 2*it));
            }
        }
    }

    QPixmap pixmap = QPixmap::fromImage(*ui->graphicsView->image);
    ui->graphicsView->scene->items().removeAt(0);
    if (ui->graphicsView->pixmap != nullptr) delete ui->graphicsView->pixmap;
    ui->graphicsView->pixmap = ui->graphicsView->scene->addPixmap(pixmap);
}

void Algebraic::DrawRect(long double x, long double y)
{
    long double cur_x = ui->graphicsView->get_cursor_x();
    long double cur_y  = ui->graphicsView->get_cursor_y();
    if (ui->graphicsView->cur_rect != nullptr) {
        ui->graphicsView->scene->removeItem(ui->graphicsView->cur_rect);
        delete ui->graphicsView->cur_rect;
    }
    ui->graphicsView->cur_rect = ui->graphicsView->scene->addRect(cur_x,
                                                                  cur_y,
                                                                  x - cur_x,
                                                                  y - cur_y,
                                                                  QPen(QColor(0, 0, 200, 80)),
                                                                  QBrush(QColor(0, 0, 255, 30)));
}

void Algebraic::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    emit signal();
}

void Algebraic::on_pushButton_clicked()
{
    Draw(0, 0, ui->graphicsView->geometry().width(), ui->graphicsView->geometry().height());
}
