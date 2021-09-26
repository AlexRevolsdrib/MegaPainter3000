#include "controller.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QPushButton>
#include <QLineEdit>
#include <QSlider>
#include <QRadioButton>

Controller::Controller()
{

}

void Controller:: setOpacity(int value)
{
    int i = enteredRow;
    layers->at(i)->setOpacity(value/100.);
    plane->updateIllustration();
    plane->update();
}

void Controller:: upRow()
{
    int i = enteredRow;
    if(i != 0)
    {
        QString sNameLayer = lWidList[i]->leName->text();
        lWidList[i]->leName->setText(lWidList[i-1]->leName->text());
        lWidList[i-1]->leName->setText(sNameLayer);
        layers->swapItemsAt(i,i-1);
        lWidList[i]->vLayer->setLayer(layers->at(i));
        lWidList[i]->vLayer->update();
        lWidList[i-1]->vLayer->setLayer(layers->at(i-1));
        lWidList[i-1]->vLayer->update();
        lWid->setCurrentRow(i-1);
    }
    plane->updateIllustration();
    plane->update();

}
void Controller:: downRow()
{
    int i = enteredRow;
    if(i != layers->size()-1)
    {
        QString sNameLayer = lWidList[i]->leName->text();
        lWidList[i]->leName->setText(lWidList[i+1]->leName->text());
        lWidList[i+1]->leName->setText(sNameLayer);
        layers->swapItemsAt(i,i+1);
        lWidList[i]->vLayer->setLayer(layers->at(i));
        lWidList[i]->vLayer->update();
        lWidList[i+1]->vLayer->setLayer(layers->at(i+1)/*tmp*/);
        lWidList[i+1]->vLayer->update();
        lWid->setCurrentRow(i+1);
    }
    plane->updateIllustration();
    plane->update();
}

void Controller:: on_visible_widget()
{
   int i = enteredRow;//lWid->currentRow();
 //  qDebug()<<enteredRow<<"!";
   layers->at(i)->setVisible(check[i]->isChecked());
   plane->updateIllustration();
   plane->update();
}

void Controller:: setPlane(Plane *plane)
{
    this->plane = plane;
    layers = plane->Layers();
    QObject::connect(this->plane, SIGNAL(clicked()), this, SLOT(on_clicked_plane()));
}

void Controller:: setLWid(QListWidget *ListWidget)
{
    lWid = ListWidget;
    ListWidget->setSelectionMode(QListWidget::ExtendedSelection);
    //lWid->setMouseTracking(true);
    QObject::connect(this->lWid, SIGNAL(currentRowChanged(int)), this, SLOT(on_current_item_change(int)));
    QObject::connect(this->lWid, SIGNAL(itemEntered(QListWidgetItem *)), this, SLOT(on_listWidget_itemEntered(QListWidgetItem *)));
    QObject::connect(this->lWid->model(), SIGNAL(rowsMoved(QModelIndex,int,int,QModelIndex,int)), this, SLOT(on_recal_wid_on_item(QModelIndex,int,int,QModelIndex,int)));
}
QWidget* Controller::AddRow()//Добавляет новую строку в QListWidget
{
        WidOnListItem *widitem = new WidOnListItem;
        QString str = "Cлой " + QString::number(layers->count());
        Layer *layer = new Layer(plane->width(), plane->height(), QImage::Format_ARGB32);
        if (layers->isEmpty()) //Если список пустой, то добавим фон
        {
          str = "Фон";
          QPainter painter;
          painter.begin(layer);
          painter.fillRect(0,0,layer->width(),layer->height(),qRgb(255,255,255));
          painter.end();
        }
        layers->push_front(layer);
        plane->setImg(layer);
        //добавление listwidget
        VisLayer *v = new VisLayer;
        v->setLayer(layer);
        v->setFixedSize(80,80);
        v->update();
        widitem->vLayer = v;
        vislayers.push_front(v);
        //Видимость слоя
        QCheckBox *c = new QCheckBox;
        c->setMouseTracking(true);
        //c->setFixedSize(30, 30);
                c->setChecked(true);
        c->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
//        c->setMaximumSize(30,30);
        c->setFixedSize(30, 30);
        c->setIconSize(QSize(30,30));

//        c->setMinimumSize(30,30);
          c->updateGeometry();
          widitem->bVisible = c;
        check.push_front(c);
        QRadioButton *rb = new QRadioButton();
        rb->setChecked(true);
        widitem->bDraw = rb;
        QObject::connect(c, SIGNAL(clicked()), this, SLOT(on_visible_widget()));
        //Кнопка Поднять слой
        /*QPushButton *bUp = new QPushButton("∧");
        QObject::connect(bUp, SIGNAL(clicked()), this, SLOT(upRow()));
        bUp->setFixedSize(c->size());
        //Кнопка Опустить слой
        QPushButton *bDown = new QPushButton("∨");       
        bDown->setFixedSize(c->size());
        QObject::connect(bDown, SIGNAL(clicked()), this, SLOT(downRow()));*/
        //Имя слоя
        QLineEdit *lNameLayer = new QLineEdit(str);
        lNames.push_front(lNameLayer);
        widitem->leName = lNameLayer;
        //Прозрачность слоя
        QSlider *slProz = new QSlider(Qt::Horizontal);
        slProzs.push_front(slProz);
        slProz->setMaximum(100);
        slProz->setMinimum(0);
        slProz->setValue(100);
        QObject::connect(slProz, SIGNAL(valueChanged(int)), this, SLOT(setOpacity(int)));
        widitem->sOccup = slProz;
        //Компоновка

        QVBoxLayout *vBut = new QVBoxLayout;
        //vBut->addWidget(bUp);
       // vBut->addSpacing(15);
        vBut->addWidget(c);
        vBut->addWidget(rb);
      //  vBut->addSpacing(15);
      // vBut->addWidget(bDown);

        QVBoxLayout *vName  = new QVBoxLayout;
        vName->addWidget(lNameLayer);
        vName->addWidget(slProz);
        QHBoxLayout *lRow = new QHBoxLayout;
        lRow->addLayout(vBut);
        lRow->addWidget(v);
        lRow->addLayout(vName);

        QListWidgetItem *itm = new QListWidgetItem;
        widitem->LWitem = itm;
        lWid->insertItem(0,itm);
        itm->setSizeHint(QSize(400, v->height()+25));
        lWid->setCurrentItem(itm,QItemSelectionModel::ClearAndSelect);
        //lWid->setCurrentRow(0);

        QWidget *tmp = new QWidget;

       // bUp->setMouseTracking(true);
       // bDown->setMouseTracking(true);
        v->setMouseTracking(true);
        tmp->setMouseTracking(true);

        tmp->setLayout(lRow);
        lWid->setMouseTracking(true);
        lWid->setItemWidget(itm, tmp);
        plane->updateIllustration();
        lWidList.push_front(widitem);
        return tmp;
}

void Controller:: updateVis()
{
    int i = lWid->currentRow();
    //vislayers.at(i)->update();
    lWidList.at(i)->vLayer->update();
    lWid->itemWidget(lWid->item(i))->layout()->update();
    lWid->itemWidget(lWid->item(i))->update();
    lWid->update();

}

void Controller:: DeleteRow()
{
    int i = lWid->currentRow();
    lWid->removeItemWidget(lWid->currentItem());
    delete lWid->currentItem();
    delete vislayers[i];
    //vislayers.removeAt(i);
    delete lNames[i];
    //lNames.removeAt(i);
   // delete listRow[i];
    listRow.removeAt(i);
    //delete layers->at(i);
    layers->removeAt(i);
    delete slProzs[i];
    slProzs.removeAt(i);
    check.removeAt(i);
    lWid->update();
    lWid->setCurrentRow(i-1>0?i-1:0);
    plane->updateIllustration();
}

void Controller:: on_clicked_plane()
{
    updateVis();
}

void Controller:: on_current_item_change(int current)
{
    plane->setImg(layers->at(current));
}

void Controller::on_listWidget_itemEntered(QListWidgetItem *item)
{
   enteredRow=lWid->row(item);
}
void Controller:: joinLayerUp()
{
    int i = lWid->currentRow();
    if (i>0)
    {
        plane->getActiveLayer()->DrawOnLayer(layers->at(i-1));
        lWid->setCurrentRow(i-1);
        DeleteRow();
    }
}
void Controller:: joinLayerDown()
{
    int i = lWid->currentRow();
    if (i<layers->size())
    {
        layers->at(i+1)->DrawOnLayer(plane->getActiveLayer());
        DeleteRow();
        lWid->setCurrentRow(i);
    }
}
void Controller:: DeleteRows()
{
   QList<QListWidgetItem *> listItem =  lWid->selectedItems();
   for( QListWidgetItem* item : listItem)
   {
       lWid->setCurrentItem(item, QItemSelectionModel::ClearAndSelect);
       DeleteRow();
   }
}

void Controller:: joinLayerMany()
{
    QList<QListWidgetItem *> listItem =  lWid->selectedItems();
    if(listItem.size()<2) return;
    //listItem.reserve(listItem.size());
    Layer *layer = new Layer(plane->width(), plane->height(), QImage::Format_ARGB32); ;
    for( QListWidgetItem* item : listItem)
    {
        int i = lWid->row(item);
        layer->DrawOnLayer(layers->at(i));
    }
    int i = lWid->row(listItem.last());
   // vislayers[i]->setLayer(layer);
    lWidList[i]->vLayer->setLayer(layer);
    layers->replace(i,layer);
    listItem.removeAt(listItem.size()-1);
    for( QListWidgetItem* item : listItem)
    {
        lWid->setCurrentItem(item, QItemSelectionModel::ClearAndSelect);
        DeleteRow();
    }
}

void Controller:: on_recal_wid_on_item(const QModelIndex &parent, int start, int end, const QModelIndex &destination, int row)
{
    for( WidOnListItem *item : lWidList)
    {
        item->index = lWid->row(item->LWitem);
    }

    qSort(lWidList.begin(), lWidList.end(),
          [](const WidOnListItem *a, const WidOnListItem *b) -> bool { return a->index < b->index;});
    QList<Layer *> tmp;


    for(int i = 0; i < lWidList.size(); i++)
    {
        tmp.push_back(lWidList[i]->vLayer->Img());
    }
    plane->setIllustration(tmp);
    layers = plane->Layers();
    plane->updateIllustration();
    plane->update();
}
