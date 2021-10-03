#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QMainWindow>
#include <layer.h>
#include <plane.h>
#include <QList>
#include <vislayer.h>
#include <colorpallete.h>
#include <QCheckBox>
#include <colorone.h>
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
#include <QSpinBox>

struct WidOnListItem{
    int index;
    CheckButton *bVisible;
    QPushButton *bDraw;
    VisLayer *vLayer;
    QLineEdit *leName;
    QSlider *sOccup;
    QListWidgetItem * LWitem;
    ~WidOnListItem()
    {
        delete LWitem;
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
    QList<Layer* > *layers;
    QList<VisLayer* > vislayers;
    Plane *plane;
    QList<WidOnListItem *> lWidList;
    ColorPallete *pallete;
    ColorOne *colorWid;
    QSpinBox *sbR,*sbG,*sbB;
    QSpinBox *sbH,*sbS,*sbBR;
    QSlider *sR,*sG,*sB;
    QPen * pen;
public:

    void setPlane(Plane *plane);
    Controller();
    //Работа со слоями
    int enteredRow;
    void setLWid(QListWidget * ListWidget);
    QWidget *AddRow();//Добавляет новую строку в QListWidget
    void DeleteRow();//Удаляет текущую строку
    void DeleteRows();// Удаляет выделленые стоки
    void updateVis();
    void joinLayerUp();//Объедиить с вышествоящим слоем
    void joinLayerDown();//Объедиить с нижествоящим слоем
    void joinLayerMany();//Объедиить выделенные слоем
    //Работа с цветом
    void setPallete(ColorPallete *pallete);
    void setOne(ColorOne *colorWid);
    void setSpinRGB(QSpinBox *sbR, QSpinBox*sbG, QSpinBox*sbB);
    void setSliderRGB(QSlider *sR, QSlider*sG, QSlider*sB);
    void setSpinHSB(QSpinBox *sbH, QSpinBox*sbS, QSpinBox*sbBR);
    void updateColor();
public slots:
    void upRow();
    void downRow();
    void on_visible_widget();
    void setOpacity(int value);
    void on_clicked_plane();
    void on_current_item_change(int current);
    void on_listWidget_itemEntered(QListWidgetItem *item);
    void on_recal_wid_on_item(const QModelIndex &parent, int start, int end, const QModelIndex &destination, int row);
    void on_pallet_clicked(QColor color);
    void changeRed(int red);
    void changeGreen(int green);
    void changeBlue(int blue);
};

#endif // CONTROLLER_H
