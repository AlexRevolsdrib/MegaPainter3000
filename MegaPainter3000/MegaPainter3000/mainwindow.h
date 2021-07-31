#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <controller.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_tbAdd_clicked();

    void on_tbDelete_clicked();

    void on_tbClear_clicked();

    void on_tbPlusUp_clicked();

    void on_tbPlusDown_clicked();

    void on_tbPlusMany_clicked();

    void on_pallet_clicked(QColor color);

private:
    Ui::MainWindow *ui;
    QPen *pen;
    Controller *controller;
};

#endif // MAINWINDOW_H
