#include "vislayer.h"

VisLayer::VisLayer(QWidget *parent) : QWidget(parent)
{
    img = nullptr;

}
void VisLayer:: setLayer(Layer *layer)
{
    img = layer;
}

void VisLayer:: paintBackgound()
{
//    QPainter painter;
//    painter.begin(img);
//    painter.fillRect(0,0,img->width(),img->height(),img->getBackground());
//    painter.end();
}

VisLayer:: VisLayer(Layer *layer)
{
    img = layer;
}

void VisLayer:: paintEvent(QPaintEvent *event)
{
    Layer illustration;
    if(img)illustration = *img;
    else return;

    QPainter painter;
    painter.begin(this);
    //painter.drawImage(0,0,Layer::SubLayer(width(),height()));
    painter.drawImage(0,0,illustration.scaled(width(), height(), Qt::IgnoreAspectRatio));
    painter.end();
    event->accept();
}

