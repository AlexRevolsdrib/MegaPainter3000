#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pen = new QPen(Qt::red);
    pen->setWidth(5);
    ui->plane->setPen(pen);
    controller = new Controller();
    controller->setPlane(ui->plane);
    controller->setLWid(ui->listWidget);
    controller->AddRow();
    controller->setColorSlider(ui->ColorSlider);
//    controller->AddRow();
    ui->plane->setInstrument(inPen);

//    QObject :: connect(ui->pallet,SIGNAL(clicked(QColor)),this, SLOT(on_pallet_clicked(QColor)));
 // QObject :: connect(this->plane, SIGNAL(clicked()), this, SLOT(on_clicked_plane()));


    controller->setOne(ui->widColor);
    controller->setPallete(ui->pallet);
    controller->setSpinRGB(ui->sbR,ui->sbG,ui->sbB);
    controller->setSliderRGB(ui->sR,ui->sG,ui->sB);
    controller->setSpinHSB(ui->sbH,ui->sbS,ui->sbBR);
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
//    pen->setColor(color);
//    ui->widColor->setColor(color);
   // ui->plane->setPen(pen);
}

void MainWindow::on_tbUP_clicked()
{
    controller->upRow();
}

void MainWindow::on_tbDown_clicked()
{
    controller->downRow();
}

void MainWindow::on_tbUp_clicked()
{
     controller->upRow();
}
