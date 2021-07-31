#include "controller.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QPushButton>
#include <QLineEdit>
#include <QSlider>

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
        QString sNameLayer = lNames[i]->text();
        lNames[i]->setText(lNames[i-1]->text());
        lNames[i-1]->setText(sNameLayer);
        layers->swapItemsAt(i,i-1);
        vislayers[i]->setLayer(layers->at(i));
        vislayers[i]->update();
        vislayers[i-1]->setLayer(layers->at(i-1));
        vislayers[i-1]->update();
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
        QString sNameLayer = lNames[i]->text();
        lNames[i]->setText(lNames[i+1]->text());
        lNames[i+1]->setText(sNameLayer);
        layers->swapItemsAt(i,i+1);
        vislayers[i]->setLayer(layers->at(i));
        vislayers[i]->update();        
        vislayers[i+1]->setLayer(layers->at(i+1)/*tmp*/);
        vislayers[i+1]->update();
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
}
QWidget* Controller::AddRow()//Добавляет новую строку в QListWidget
{
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
        vislayers.push_front(v);
        //Видимость слоя
        QCheckBox *c = new QCheckBox;
        c->setMouseTracking(true);
        c->setFixedSize(30, 30);
        c->update();
        c->setChecked(true);
        check.push_front(c);
        QObject::connect(c, SIGNAL(clicked()), this, SLOT(on_visible_widget()));
        //Кнопка Поднять слой
        QPushButton *bUp = new QPushButton("∧");
        QObject::connect(bUp, SIGNAL(clicked()), this, SLOT(upRow()));
        bUp->setFixedSize(c->sizeHint());
        //Кнопка Опустить слой
        QPushButton *bDown = new QPushButton("∨");
        bDown->setFixedSize(c->sizeHint());
        QObject::connect(bDown, SIGNAL(clicked()), this, SLOT(downRow()));
        //Имя слоя
        QLineEdit *lNameLayer = new QLineEdit(str);
        lNames.push_front(lNameLayer);
        //Прозрачность слоя
        QSlider *slProz = new QSlider(Qt::Horizontal);
        slProzs.push_front(slProz);
        slProz->setMaximum(100);
        slProz->setMinimum(0);
        slProz->setValue(100);
        QObject::connect(slProz, SIGNAL(valueChanged(int)), this, SLOT(setOpacity(int)));
        //Компоновка

        QVBoxLayout *vBut = new QVBoxLayout;
        vBut->addWidget(bUp);
        vBut->addWidget(c);
        vBut->addWidget(bDown);

        QVBoxLayout *vName  = new QVBoxLayout;
        vName->addWidget(lNameLayer);
        vName->addWidget(slProz);
        QHBoxLayout *lRow = new QHBoxLayout;
        lRow->addLayout(vBut);
        lRow->addWidget(v);
        lRow->addLayout(vName);

        QListWidgetItem *itm = new QListWidgetItem;
        lWid->insertItem(0,itm);
        itm->setSizeHint(QSize(400, v->height()));
        lWid->setCurrentItem(itm,QItemSelectionModel::ClearAndSelect);
        //lWid->setCurrentRow(0);

        QWidget *tmp = new QWidget;

        bUp->setMouseTracking(true);
        bDown->setMouseTracking(true);
        v->setMouseTracking(true);
        tmp->setMouseTracking(true);

        tmp->setLayout(lRow);
        lWid->setMouseTracking(true);
        lWid->setItemWidget(itm, tmp);
        plane->updateIllustration();
        return tmp;
}

void Controller:: updateVis()
{
    int i = lWid->currentRow();
    vislayers.at(i)->update();
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
    vislayers.removeAt(i);
    delete lNames[i];
    lNames.removeAt(i);
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
    vislayers[i]->setLayer(layer);
    layers->replace(i,layer);
    listItem.removeAt(listItem.size()-1);
    for( QListWidgetItem* item : listItem)
    {
        lWid->setCurrentItem(item, QItemSelectionModel::ClearAndSelect);
        DeleteRow();
    }
}
