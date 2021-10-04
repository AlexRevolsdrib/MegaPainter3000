#include "colorpallete.h"

ColorPallete::ColorPallete(QWidget *parent) : QWidget(parent)
{

}
void ColorPallete:: paintEvent(QPaintEvent *event)
{
    QImage img(width(),height(), QImage::Format_ARGB32);
    for(int x=0;x<width();x++){
        for(int y=0; y<height() ;y++)
        {
            QColor color;
            color.setHsl(360*x/width(),255*(height()-y)/height(),127);
            img.setPixel(x,y,qRgba(color.red(),color.green(),color.blue(),255));
        }
    }
    QPainter painter;
    painter.begin(this);
    painter.drawImage(this->rect(),img);
    painter.end();
    this->img = img;
    event->accept();
}

void ColorPallete:: mousePressEvent(QMouseEvent *event)
{
    emit clicked(img.pixelColor(event->pos()));
    event->accept();
}
void ColorPallete:: mouseMoveEvent(QMouseEvent *event)
{
    if((event->pos().x()>=0 && event->pos().x()<=width())
        && ((event->pos().y()>=0 && event->pos().y()<=height())))
        emit clicked(img.pixelColor(event->pos()));
    event->accept();
}
