#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    controller = new Controller();
    controller->setPlane(ui->plane);
    controller->setLWid(ui->listWidget);
    controller->AddRow();
//    controller->AddRow();
    ui->plane->setInstrument(inPen);

    QObject :: connect(ui->pallet,SIGNAL(clicked(QColor)),this, SLOT(on_pallet_clicked(QColor)));
 // QObject :: connect(this->plane, SIGNAL(clicked()), this, SLOT(on_clicked_plane()));
    pen = new QPen(Qt::red);
    ui->plane->setPen(pen);
    pen->setWidth(5);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tbAdd_clicked()
{
    controller->AddRow();
}

void MainWindow::on_tbDelete_clicked()
{
    controller->DeleteRows ();
}

void MainWindow::on_tbClear_clicked()
{
    ui->plane->getActiveLayer()->claer();
    ui->plane->update();
}

void MainWindow::on_tbPlusUp_clicked()
{
    controller->joinLayerUp();
}

void MainWindow::on_tbPlusDown_clicked()
{
    controller->joinLayerDown();
}


void MainWindow::on_tbPlusMany_clicked()
{
    controller->joinLayerMany();
}

void MainWindow::on_pallet_clicked(QColor color)
{
    pen->setColor(color);
    ui->widColor->setColor(color);
   // ui->plane->setPen(pen);
}
