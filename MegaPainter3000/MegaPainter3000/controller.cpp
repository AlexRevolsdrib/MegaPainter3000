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
    //int i = enteredRow;
    int i = lWid->currentRow();
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
        bool bTmp = lWidList[i]->bVisible->isChecked();
        lWidList[i]->bVisible->setChecked(lWidList[i-1]->bVisible->isChecked());
        lWidList[i-1]->bVisible->setChecked(bTmp);
        int nTmp = lWidList[i]->sOccup->value();
        lWidList[i]->sOccup->setValue(lWidList[i-1]->sOccup->value());
        lWidList[i-1]->sOccup->setValue(nTmp);

    }
    plane->updateIllustration();
    plane->update();

}
void Controller:: downRow()
{
    //int i = enteredRow;
    int i = lWid->currentRow();
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
        bool bTmp = lWidList[i]->bVisible->isChecked();
        lWidList[i]->bVisible->setChecked(lWidList[i+1]->bVisible->isChecked());
        lWidList[i+1]->bVisible->setChecked(bTmp);
        int nTmp = lWidList[i]->sOccup->value();
        lWidList[i]->sOccup->setValue(lWidList[i+1]->sOccup->value());
        lWidList[i+1]->sOccup->setValue(nTmp);
    }
    plane->updateIllustration();
    plane->update();
}

void Controller:: on_visible_widget()
{
   int i = enteredRow;//lWid->currentRow();
 //  qDebug()<<enteredRow<<"!";
   layers->at(i)->setVisible(lWidList[i]->bVisible->isChecked());
   plane->updateIllustration();
   plane->update();
}

void Controller:: setPlane(Plane *plane)
{
    this->plane = plane;
    layers = plane->Layers();
    QObject::connect(this->plane, SIGNAL(clicked()), this, SLOT(on_clicked_plane()));
    pen = plane->Pen();
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
        //Видимость слоя
          CheckButton *c = new CheckButton;
           c->setMouseTracking(true);
           c->setChecked(true);
           widitem->bVisible = c;
       // check.push_front(c);
        QPushButton *rb = new QPushButton();
        rb->setObjectName("DrawActive");
        widitem->bDraw = rb;
        QObject::connect(c, SIGNAL(clicked()), this, SLOT(on_visible_widget()));
        //Кнопка Поднять слой
       // QPushButton *bUp = new QPushButton("∧");
       //QObject::connect(bUp, SIGNAL(clicked()), this, SLOT(upRow()));
       // bUp->setFixedSize(c->size());
        //bUp->setObjectName("evil");
        //bUp->setObjectName("t");
         /*//Кнопка Опустить слой
        QPushButton *bDown = new QPushButton("∨");       
        bDown->setFixedSize(c->size());
        QObject::connect(bDown, SIGNAL(clicked()), this, SLOT(downRow()));*/
        //Имя слоя
        QLineEdit *lNameLayer = new QLineEdit(str);

        widitem->leName = lNameLayer;
        //Прозрачность слоя
        QSlider *slProz = new QSlider(Qt::Horizontal);
        slProz->setMaximum(100);
        slProz->setMinimum(0);
        slProz->setValue(100);
        QObject::connect(slProz, SIGNAL(valueChanged(int)), this, SLOT(setOpacity(int)));
        lWidList.push_front(widitem);
        widitem->sOccup = slProz;
        //Компоновка

        QVBoxLayout *vBut = new QVBoxLayout;
       // vBut->addWidget(bUp);
       // vBut->addSpacing(15);
        vBut->addWidget(c);
        vBut->addWidget(rb);
      //  vBut->addSpacing(15);
      // vBut->addWidget(bDown);
        // bUp->setMouseTracking(true);
        // bDown->setMouseTracking(true);
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
        itm->setSizeHint(QSize(lWid->width()-100, v->height()+25));
        lWid->setCurrentItem(itm,QItemSelectionModel::ClearAndSelect);
        //lWid->setCurrentRow(0);

        QWidget *tmp = new QWidget;

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
    listRow.removeAt(i);
    layers->removeAt(i);
    delete lWidList[i]->vLayer->Img();
    delete lWidList[i];
    lWidList.removeAt(i);
    lWid->update();

    lWid->setCurrentRow(i-1>0?i-1:0);
    plane->updateIllustration();
//    int i = lWid->currentRow();
//    lWid->removeItemWidget(lWid->currentItem());
//    delete lWid->currentItem();
//    delete lWidList[i]->vLayer;
//    //vislayers.removeAt(i);
//    delete lWidList[i]->leName;
//    //lNames.removeAt(i);
//   // delete listRow[i];
//    listRow.removeAt(i);
//    //delete layers->at(i);
//    layers->removeAt(i);
//    delete lWidList[i]->sOccup;

//    lWid->update();
//    lWid->setCurrentRow(i-1>0?i-1:0);
//    plane->updateIllustration();

}

void Controller:: on_clicked_plane()
{
    updateVis();
}

void Controller:: on_current_item_change(int current)
{

    plane->setImg(layers->at(current));
    for (int i=0;i<lWidList.size();i++) {
         lWidList[i]->bDraw->style()->unpolish(lWidList[i]->bDraw);
        if(current == i){
            lWidList[i]->bDraw->setObjectName("DrawActive");}
        else lWidList[i]->bDraw->setObjectName("DrawNone");
       lWidList[i]->bDraw->style()->polish(lWidList[i]->bDraw);
    }
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

void Controller:: setPallete(ColorPallete *pallete)
{
    this->pallete = pallete;
     QObject :: connect(this->pallete,SIGNAL(clicked(QColor)),this, SLOT(on_pallet_clicked(QColor)));
}
void Controller:: setOne(ColorOne *colorWid)
{
    this->colorWid = colorWid;
}
void Controller:: setSpinRGB(QSpinBox *sbR, QSpinBox*sbG, QSpinBox*sbB)
{
    this->sbR = sbR;
    QObject::connect(this->sbR, SIGNAL(valueChanged(int)), this, SLOT(changeRed(int)));
    this->sbG = sbG;
    QObject::connect(this->sbG, SIGNAL(valueChanged(int)), this, SLOT(changeGreen(int)));
    this->sbB = sbB;
    QObject::connect(this->sbB, SIGNAL(valueChanged(int)), this, SLOT(changeBlue(int)));

}

void Controller:: setSliderRGB(QSlider *sR, QSlider*sG, QSlider*sB)
{
    this->sR = sR;
    QObject::connect(this->sR, SIGNAL(valueChanged(int)), this, SLOT(changeRed(int)));
    this->sG = sG;
    QObject::connect(this->sG, SIGNAL(valueChanged(int)), this, SLOT(changeGreen(int)));
    this->sB = sB;
    QObject::connect(this->sB, SIGNAL(valueChanged(int)), this, SLOT(changeBlue(int)));

}

void Controller:: setSpinHSB(QSpinBox *sbH, QSpinBox*sbS, QSpinBox*sbBR)
{
    this->sbH = sbH;
    this->sbS = sbS;
    this->sbBR = sbBR;
    updateColor();
}

void Controller:: updateColor()
{
    if (pen->color()!= Qt::white && pen->color()!= Qt::black) colorStyleSl.setHsl(pen->color().hslHue(),pen->color().hslSaturation(),127);
    colorWid->setColor(pen->color());
    sbR->setValue(pen->color().red());
    sbG->setValue(pen->color().green());
    sbB->setValue(pen->color().blue());
    sR->setValue(pen->color().red());
    sG->setValue(pen->color().green());
    sB->setValue(pen->color().blue());
    sbH->setValue(pen->color().hsvHue());
    sbS->setValue(pen->color().hsvSaturation());
    sbBR->setValue(pen->color().lightness());
    slColor->setValue(pen->color().lightness());
    slColor->setStyleSheet("QSlider::groove:vertical {background: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, "
                           "stop:0 rgba(0,0,0,255)  stop:1 rgba(255,255,255,255), "
                           "stop :0.5 rgba("+ QString::number(colorStyleSl.red())+","+QString::number(colorStyleSl.green())+","+QString::number(colorStyleSl.blue())+", 255))}");
}

void Controller::on_pallet_clicked(QColor color)
{
    colorStyleSl = color;
    pen->setColor(color);

    updateColor();
}

void Controller:: changeRed(int red)
{
    pen->setColor(QColor(red,pen->color().green(),pen->color().blue()));
    updateColor();
}
void Controller:: changeGreen(int green)
{
    pen->setColor(QColor(pen->color().red(),green,pen->color().blue()));
    updateColor();
}
void Controller:: changeBlue(int blue)
{
    pen->setColor(QColor(pen->color().red(),pen->color().green(),blue));
    updateColor();
}
void  Controller:: setColorSlider(QSlider *slColor)
{
    this->slColor = slColor;
    QObject::connect(this->slColor, SIGNAL(valueChanged(int)), this, SLOT(changeLightness(int)));
}

void Controller:: changeLightness(int lightness)
{
    QColor c;
    c.setHsl(colorStyleSl.hsvHue(),colorStyleSl.hsvSaturation(),lightness);
    pen->setColor(c);
    updateColor();
}
