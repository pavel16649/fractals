#include "stochastic.h"
#include "ui_stochastic.h"

Stochastic::Stochastic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Stochastic),
    image(nullptr)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
}

Stochastic::~Stochastic()
{
    delete ui;
}

const double RAND = 0.4;

std::random_device rd;
std::mt19937 rng(rd());

double GenRandCol(int color, int size) {
    int min = std::max(0.0, color - RAND * size);
    int max = std::min(255.0, color + RAND * size);

    std::uniform_int_distribution<int> uni(min, max);

    double random = uni(rng);
    return random;
}

void Stochastic::on_pushButton_clicked()
{
    double size = ui->graphicsView->geometry().width();

    if (image != nullptr)
        delete image;
    image = new QImage(ui->graphicsView->geometry().width(),
                       ui->graphicsView->geometry().height(),
                       QImage::Format_RGB32);


    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            image->setPixelColor(i, j, QColor(255, 255, 255));
        }
    }

    int redRU = GenRandCol(127, size);
    int greenRU = GenRandCol(127, size);
    int blueRU = GenRandCol(127, size);
    QColor colorRU(redRU, greenRU, blueRU);

    int redLU = GenRandCol(127, size);
    int greenLU = GenRandCol(127, size);
    int blueLU = GenRandCol(127, size);
    QColor colorLU(redLU, greenLU, blueLU);

    int redRD = GenRandCol(127, size);
    int greenRD = GenRandCol(127, size);
    int blueRD = GenRandCol(127, size);
    QColor colorRD(redRD, greenRD, blueRD);

    int redLD = GenRandCol(127, size);
    int greenLD = GenRandCol(127, size);
    int blueLD = GenRandCol(127, size);
    QColor colorLD(redLD, greenLD, blueLD);

    RecursiveFillRect(*image, 0, 0, size - 1, colorLU, colorRU, colorRD, colorLD);

    QPixmap pixmap = QPixmap::fromImage(*image);
    ui->graphicsView->scene()->addPixmap(pixmap);
}

void Stochastic::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    emit signal();
}

void Stochastic::RecursiveFillRect(QImage &image,
                                   double x,
                                   double y,
                                   double size,
                                   QColor colorLU,
                                   QColor colorRU,
                                   QColor colorRD,
                                   QColor colorLD)
{
    if (size <= 1)
        return;

    int redLU = colorLU.red(), greenLU = colorLU.green(), blueLU = colorLU.blue();
    int redRU = colorRU.red(), greenRU = colorRU.green(), blueRU = colorRU.blue();
    int redLD = colorLD.red(), greenLD = colorLD.green(), blueLD = colorLD.blue();
    int redRD = colorRD.red(), greenRD = colorRD.green(), blueRD = colorRD.blue();

    int redC = GenRandCol((redLU + redRU + redLD + redRD) / 4, size);
    int greenC = GenRandCol((greenLU + greenRU + greenLD + greenRD) / 4, size);
    int blueC = GenRandCol((blueLU + blueRU + blueLD + blueRD) / 4, size);
    QColor colorC(redC, greenC, blueC);
    if (image.pixelColor(x + size / 2, y + size / 2) == QColor(255, 255, 255))
        image.setPixelColor(x + size / 2, y + size / 2, colorC);
    else {
        colorC = image.pixelColor(x + size / 2, y + size / 2);
        redC = colorC.red();
        blueC = colorC.blue();
        greenC = colorC.green();
    }

    int redU = GenRandCol((redLU + redRU + redC) / 3, size);
    int greenU = GenRandCol((greenLU + greenRU + greenC) / 3, size);
    int blueU = GenRandCol((blueLU + blueRU + blueC) / 3, size);
    QColor colorU(redU, greenU, blueU);
    if (image.pixelColor(x + size / 2, y) == QColor(255, 255, 255))
        image.setPixelColor(x + size / 2, y, colorU);
    else
        colorU = image.pixelColor(x + size / 2, y);

    int redR = GenRandCol((redRU + redRD + redC) / 3, size);
    int greenR = GenRandCol((greenRU + greenRD + greenC) / 3, size);
    int blueR = GenRandCol((blueRU + blueRD + blueC) / 3, size);
    QColor colorR(redR, greenR, blueR);
    if (image.pixelColor(x + size, y + size / 2) == QColor(255, 255, 255))
        image.setPixelColor(x + size, y + size / 2, colorR);
    else
        colorR = image.pixelColor(x + size, y + size / 2);

    int redD = GenRandCol((redLD + redRD + redC) / 3, size);
    int greenD = GenRandCol((greenLD + greenRD + greenC) / 3, size);
    int blueD = GenRandCol((blueLD + blueRD + blueC) / 3, size);
    QColor colorD(redD, greenD, blueD);
    if (image.pixelColor(x + size / 2, y + size) == QColor(255, 255, 255))
        image.setPixelColor(x + size / 2, y + size, colorD);
    else
        colorD = image.pixelColor(x + size / 2, y + size);

    int redL = GenRandCol((redLD + redLU + redC) / 3, size);
    int greenL = GenRandCol((greenLD + greenLU + greenC) / 3, size);
    int blueL = GenRandCol((blueLD + blueLU + blueC) / 3, size);
    QColor colorL(redL, greenL, blueL);
    if (image.pixelColor(x, y + size / 2) == QColor(255, 255, 255))
        image.setPixelColor(x, y + size / 2, colorL);
    else
        colorL = image.pixelColor(x, y + size / 2);

    RecursiveFillRect(image, x, y, size/2, colorLU, colorU, colorC, colorL);
    RecursiveFillRect(image, x + size / 2, y, size/2, colorU, colorRU, colorR, colorC);
    RecursiveFillRect(image, x, y + size /2, size/2, colorL, colorC, colorD, colorLD);
    RecursiveFillRect(image, x + size / 2, y + size / 2, size/2, colorC, colorR, colorRD, colorD);
}
