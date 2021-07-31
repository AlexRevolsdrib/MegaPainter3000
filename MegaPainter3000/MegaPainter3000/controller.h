#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QMainWindow>
#include <layer.h>
#include <plane.h>
#include <QList>
#include <vislayer.h>
//#include <colorwidget.h>
#include <QCheckBox>
//#include <colorone.h>
//#include <colorwindow.h>
//#include <transfplane.h>
#include <QTableWidget>
#include <QFileDialog>
#include <QDir>
#include <QAction>
//#include <widrow.h>
#include <QListWidget>

class Controller: public QWidget
{
    Q_OBJECT
    QListWidget *lWid; //QListWidget c ui
    QList<QWidget*> listRow; // Список виджетов в QListWidget, которые содержат layout
    QList<Layer* > *layers; //
    QList<VisLayer* > vislayers;
    Plane *plane;

public:
    int enteredRow;
    void setLWid(QListWidget * ListWidget);
    void setPlane(Plane *plane);
    QList<QCheckBox *> check;
    QList<QLineEdit *> lNames;
    QList<QSlider *> slProzs;
    Controller();
    QWidget *AddRow();//Добавляет новую строку в QListWidget
    void DeleteRow();
    void DeleteRows();
    void updateVis();
    void joinLayerUp();
    void joinLayerDown();
    void joinLayerMany();
public slots:
    void upRow();
    void downRow();
    void on_visible_widget();
    void setOpacity(int value);
    void on_clicked_plane();
    void on_current_item_change(int current);
    void on_listWidget_itemEntered(QListWidgetItem *item);
};

#endif // CONTROLLER_H
