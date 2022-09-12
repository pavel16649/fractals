#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      geo_window(new Geometric),
      stochastic_window(new Stochastic),
      algebraic_window(new Algebraic)
{
    ui->setupUi(this);
    connect(geo_window, SIGNAL(signal()), this, SLOT(on_geo_closed()));
    connect(stochastic_window, SIGNAL(signal()), this, SLOT(on_stochastic_closed()));
    connect(algebraic_window, SIGNAL(signal()), this, SLOT(on_algebraic_closed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    geo_window->show();
    ui->pushButton->setEnabled(false);
}

void MainWindow::on_geo_closed()
{
    ui->pushButton->setEnabled(true);
}

void MainWindow::on_stochastic_closed()
{
    ui->pushButton_3->setEnabled(true);
}

void MainWindow::on_algebraic_closed()
{
    ui->pushButton_2->setEnabled(true);
}

void MainWindow::on_pushButton_3_clicked()
{
    stochastic_window->show();
    ui->pushButton_3->setEnabled(false);
}

void MainWindow::on_pushButton_2_clicked()
{
    algebraic_window->show();
    ui->pushButton_2->setEnabled(false);
}
