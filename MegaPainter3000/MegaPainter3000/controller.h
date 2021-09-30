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
#include <QLineEdit>
#include <QRadioButton>
#include <checkbutton.h>

struct WidOnListItem{
    int index;
    //QCheckBox *bVisible;
    CheckButton *bVisible;
    QPushButton *bDraw;
    VisLayer *vLayer;
    QLineEdit *leName;
    QSlider *sOccup;
    QListWidgetItem * LWitem;

    ~WidOnListItem()
    {
        delete  LWitem;
        delete bVisible;
        delete bDraw;
        delete vLayer;
        delete leName;
        delete sOccup;

    }
};


class Controller: public QWidget
{
    Q_OBJECT
    QListWidget *lWid; //QListWidget c ui
    QList<QWidget*> listRow; // Список виджетов в QListWidget, которые содержат layout
    QList<Layer* > *layers; //
    QList<VisLayer* > vislayers;
    Plane *plane;
    QList<WidOnListItem *> lWidList;

public:
    int enteredRow;
    void setLWid(QListWidget * ListWidget);
    void setPlane(Plane *plane);
   // QList<QCheckBox *> check;
  //  QList<CheckButton *> check;
  //  QList<QLineEdit *> lNames;
  //  QList<QSlider *> slProzs;
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
    void on_recal_wid_on_item(const QModelIndex &parent, int start, int end, const QModelIndex &destination, int row);
};

#endif // CONTROLLER_H
