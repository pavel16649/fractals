#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "geometric.h"
#include "ui_geometric.h"
#include "stochastic.h"
#include "ui_stochastic.h"
#include "algebraic.h"
#include "ui_algebraic.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_geo_closed();

    void on_stochastic_closed();

    void on_algebraic_closed();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    Geometric* geo_window;
    Stochastic* stochastic_window;
    Algebraic* algebraic_window;
};
#endif // MAINWINDOW_H
