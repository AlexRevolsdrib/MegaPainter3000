#include "layer.h"
#include <QDebug>
Layer::Layer() : QImage()
{
    visible = true;
   // background = qRgb(255,255,255);
}
Layer:: Layer(const QSize &size, Format format) : QImage(size, format){visible = true ; dOpacity = 1; /*background = qRgb(255,255,255);*/}
Layer:: Layer(int width, int height, Format format) : QImage (width,height, format){visible = true ; dOpacity = 1;/*background = qRgb(255,255,255);*/}
//Layer::Layer(uchar *data, int width, int height, Format format, QImageCleanupFunction cleanupFunction = Q_NULLPTR, void *cleanupInfo = Q_NULLPTR):QImage(data, width, height,format) {visible = true ;background = qRgb(255,255,255);}
//Layer::Layer(const uchar *data, int width, int height, Format format, QImageCleanupFunction cleanupFunction = Q_NULLPTR, void *cleanupInfo = Q_NULLPTR):QImage(data,  width,  height,format) {visible = true ;background = qRgb(255,255,255);}
//Layer::Layer(uchar *data, int width, int height, int bytesPerLine, Format format, QImageCleanupFunction cleanupFunction = Q_NULLPTR, void *cleanupInfo = Q_NULLPTR):QImage(data, width, height, bytesPerLine,  format) {visible = true ;background = qRgb(255,255,255);}
//Layer::Layer(const uchar *data, int width, int height, int bytesPerLine, Format format, QImageCleanupFunction cleanupFunction = Q_NULLPTR, void *cleanupInfo = Q_NULLPTR):QImage(data, width, height, bytesPerLine, format) {visible = true ;background = qRgb(255,255,255);}
//Layer::Layer(const char * const[] xpm) :QImage() {visible = true ;background = qRgb(255,255,255);}
//Layer::Layer(const QString &fileName, const char *format = Q_NULLPTR) :QImage(fileName, format) {visible = true ;background = qRgb(255,255,255);}
Layer::Layer(const QImage &image): QImage(image ) {visible = true ; dOpacity = 1;/*background = qRgb(255,255,255);*/}
//Layer::Layer(QImage &&other) :QImage(other) {visible = true ;background = qRgb(255,255,255);}

/*Layer Layer:: operator+(Layer B){
    Layer ret(B);
    for(int i=0; i<this->width(); i++){
        for(int j=0; j<this->height(); j++){
            if(this->pixel(i,j) != qRgba(0, 0, 0, 0))
                ret.setPixel(i,j,this->pixel(i,j));
        }
    }
    return ret;
}*/
void Layer:: setBackground(QRgb pixel){
    background = pixel;
}

void Layer:: setOpacity (double dOpacity)
{
    this->dOpacity =dOpacity;
}
//QRgb Layer:: getBackground()
//{
//    return background;
//}

void Layer:: setVisible(bool vis){
    visible = vis;
}

bool Layer:: getVisible(){
    return visible;
}


QDataStream &operator >>(QDataStream &in, Layer l)
{
    int h, w;
    bool v;
    in >>h>> w>> v;
    l = l.scaled(w,h);
    l.setVisible(v);
    for(int i=0; i<l.height(); i++)
    {
        for(int j=0; j<l.width(); j++)
        {
            QRgb pix;
            in >> pix;
            l.setPixel(j,i,pix);
        }
    }
    return in;
}

QDataStream &operator <<(QDataStream &out, Layer l)
{
    out <<l.height()<< l.width() << l.getVisible();
    for(int i=0; i<l.height(); i++)
    {
        for(int j=0; j<l.width(); j++)
        {
            out << l.pixel(j,i);
        }
    }
    return out;
}
void Layer :: claer()
{
    QPainter painter;
    painter.begin(this);
    painter.setBackgroundMode(Qt::OpaqueMode);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(0,0,width(),height(),QColor(0, 0, 0, 0));
    painter.end();
}

void Layer :: DrawOnLayer(Layer* layer)
{
    QPainter painter;
    painter.begin(this);
   // painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    painter.drawImage(0,0,*layer);
    painter.end();
}

//void Layer:: paintBackgound(QRgb pixel)
//{
//    QPainter painter;
//    painter.begin(this);
//    painter.fillRect(0,0,this->width(),this->height(),pixel);
//    painter.end();
//}

QImage Layer :: SubLayer(int w, int h)
{
    QImage SubLayer(w, h, QImage::Format_ARGB32_Premultiplied);
    QPainter p;
    int r = (w > 100 && h > 100)?40:10;
    p.begin(&SubLayer);
    p.setPen(Qt::NoPen);
    p.setBrush(QBrush(QColor(225,225,225), Qt:: SolidPattern));
    for(int i=0; i< SubLayer.width(); i+=2*r)
    {
        for(int j=0;j < SubLayer.width() - r; j+=2*r)
        {
           p.drawRect(i,j,r,r);
           p.drawRect(i+r,j+r,r,r);
        }
    }
    p.end();
    return SubLayer;
}
