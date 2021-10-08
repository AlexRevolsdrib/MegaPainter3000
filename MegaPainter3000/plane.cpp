#include "plane.h"
#include <qdebug.h>
#include <QBitmap>
#include <QColorDialog>

Plane::Plane(QWidget *parent) : QWidget(parent)
{
    img = nullptr; //new Layer(581, 401, QImage::Format_ARGB32_Premultiplied);
    layers.clear();
    background.setColor(QColor(0, 0, 0, 0));
    background.setStyle(Qt::SolidPattern);
    illustrationDown = nullptr;
    illustrationUp = nullptr;
    pen = new QPen(Qt::red, 5, Qt::SolidLine);
    SubLayer = nullptr;
}

QPen* Plane:: Pen()
{
    return pen;
}

int Plane:: getInstrument()
{
    return typeInstrument;
}

void Plane:: setPen(QPen *pen)
{

    this->pen = pen;
}

void Plane:: setImg(Layer *layer){
    img = layer;
    if(layers.empty()){

        QPainter painter;
        painter.begin(img);
        painter.fillRect(0,0,width(),height(),background.color());
       painter.end();
    }
    press = false;
    transform = false;
   // typeInstrument = inPen;
    typeCursor = Normal;
    i=0;
    shoot = false;
    setMouseTracking(true);
    updateIllustration();
}
bool prinadlezit(QList<QPoint> list, QPoint point){
    bool ret = false;
    for(int i=0; i<list.count(); i++){
        if (list[i]==point)
        {
            ret = true;
            return ret;
        }
    }
    return ret;
}


void Plane:: setInstrument(int type){
    typeInstrument = type;
    shootRect();
}

bool Plane::shootRect(){
    QPainter pRot;
    if(typeCursor == Normal && transform)
    {
        pRot.begin(&withoutRect);
        pRot.drawImage(rectImage, transf);
        pRot.end();
        *img = withoutRect;
        transform = false;
        shoot = true;
        i=0;
    }
    update();

    return true;
}

void Plane:: mouseMoveEvent(QMouseEvent *event){
    //измененен вида курсора
    if(event->pos().x()>rect.x()+10 && event->pos().x()<(rect.x()+rect.width()-10) && !press &&
       event->pos().y()>rect.y()+10 && event->pos().y()<(rect.y()+rect.height()-10) && transform)
    {
        setCursor(Qt::SizeAllCursor);
        typeCursor = Move;
    }
    else
       if(event->pos().x()>rect.x()+10 && event->pos().x()<(rect.x()+rect.width()-10) && !press &&
          event->pos().y()<rect.y()+10 && event->pos().y()>(rect.y()-10) && transform)
        {
            setCursor(Qt::SizeVerCursor);
            typeCursor = ResizeVerticalUp;
        }
        else
           if(event->pos().x()>rect.x()+10 && event->pos().x()<(rect.x()+rect.width())-10 && !press &&
              event->pos().y()>rect.y()+rect.height()-10 && event->pos().y()<(rect.y()+rect.height()+10) && transform)
            {
                setCursor(Qt::SizeVerCursor);
                typeCursor = ResizeVerticalDown;
            }
           else
               if(event->pos().x()<rect.x()+10 && event->pos().x()>(rect.x()-10) && !press &&
                  event->pos().y()>rect.y()+10 && event->pos().y()<(rect.y()+rect.height()-10) && transform)
                {
                    setCursor(Qt::SizeHorCursor);
                    typeCursor = ResizeGorizLeft;
                }
               else
                   if(event->pos().x()>rect.x()+rect.width()-10 && event->pos().x()<(rect.x()+rect.width()+10) && !press &&
                      event->pos().y()>rect.y()+10 && event->pos().y()<(rect.y()+rect.height())-10 && transform)
                    {
                        setCursor(Qt::SizeHorCursor);
                        typeCursor = ResizeGorizRight;
                    }
                   else
                       if(event->pos().x()>rect.x()+rect.width()-10 && event->pos().x()<(rect.x()+rect.width()+10) && !press &&
                          event->pos().y()<rect.y()+10 && event->pos().y()>(rect.y()-10)&& transform)
                        {
                            setCursor(Qt::SizeBDiagCursor);
                            typeCursor = ResizeUpRight;
                        }
                       else
                           if(event->pos().x()<rect.x()+10 && event->pos().x()>(rect.x()-10) && !press &&
                              event->pos().y()<rect.y()+10 && event->pos().y()>(rect.y()-10)&& transform)
                            {
                                setCursor(Qt::SizeFDiagCursor);
                                typeCursor = ResizeUpLeft;
                            }
                           else
                               if(event->pos().x()>rect.x()+rect.width()-10 && event->pos().x()<(rect.x()+rect.width()+10) && !press &&
                                  event->pos().y()>rect.y()+rect.height()-10 && event->pos().y()<(rect.y()+rect.height()+10)&& transform)
                                {
                                    setCursor(Qt::SizeFDiagCursor);
                                    typeCursor = ResizeDownRight;
                                }
                               else
                                   if(event->pos().x()<rect.x()+10 && event->pos().x()>(rect.x()-10) && !press &&
                                      event->pos().y()>rect.y()+rect.height()-10 && event->pos().y()<(rect.y()+rect.height()+10)&& transform)
                                    {
                                        setCursor(Qt::SizeBDiagCursor);
                                        typeCursor = ResizeDownLeft;
                                    }
                                   else
                                       if(!press&& transform)
                                       {
                                           setCursor(QCursor(Qt::ArrowCursor));
                                           typeCursor = Normal;
                                       }





   if(!press){
       event->accept();
       return;
   }
   end = event->pos();


   switch (typeInstrument){
   case inPen:{ // карандаш
       QPainter pLine;
       pLine.begin(img);
//       pLine.setPen(QPen(pen->color(),1));
//       pLine.setBrush(QBrush(pen->color(), Qt::SolidPattern));
//       pLine.drawEllipse(begin,pen->width()/2 -1,pen->width()/2 -1);
       pLine.setPen(*pen);
       pLine.setBrush(QBrush(pen->color(), Qt:: NoBrush));
       pLine.drawLine(begin, end);
       pLine.end();
       begin = end;
       break;}
   case inlastis:{ // ластик
       QPainter pLine;
       pLine.begin(img);
       QPen tmp (background.color(), pen->width() , Qt::SolidLine);
       tmp.setCapStyle(Qt::RoundCap);
       pLine.setPen(tmp);
       pLine.setBackgroundMode(Qt::OpaqueMode);
       pLine.setCompositionMode(QPainter::CompositionMode_Source);
       pLine.setBrush(QBrush(Qt::red, Qt::NoBrush));
       pLine.drawLine(begin, end);
       pLine.end();
       begin = end;
       break;}
   case inBrush1:{ //Кисть 1
       QPainter pLine;
       pLine.begin(img);
       QLinearGradient grad(begin, QPoint(begin.x()+pen->width()/4, begin.y()+pen->width()/4));
       grad.setColorAt(0, pen->color());
       grad.setColorAt(0.5, Qt:: white);
       grad.setColorAt(1, pen->color());
       pLine.setPen(Qt::NoPen);
       pLine.setBrush(grad);
       pLine.drawEllipse(begin,pen->width()/2,pen->width()/2);
       if(abs(begin.x() - end.x())>pen->width()/2 || abs(begin.y() - end.y())>pen->width()/2)
       {
           pLine.setPen(*pen);
           pLine.drawLine(begin, end);
       }
       pLine.end();
      begin = end;
        break;
       }
   case inBrush2:{ //Кисть 2
       QPainter pLine;
       pLine.begin(img);
       QBitmap pix;
       int ran = rand() %5 +1;
       pix.load("./icon/"+QString::number(ran)+".bmp");
       QBrush br;
       br.setStyle(Qt:: TexturePattern);
       br.setColor(pen->color());
       br.setTexture(pix);
       pLine.setPen(Qt::NoPen);
       pLine.setBrush(br);
       pLine.drawEllipse(begin,pen->width()/2,pen->width()/2);
       pLine.end();
      begin = end;
        break;
       }

   case inBrush3:{ //Кисть 3
       QPainter pLine;
       pLine.begin(img);
       pLine.setPen(Qt::NoPen);
       pLine.setBrush(QBrush(pen->color(), Qt:: DiagCrossPattern));
       pLine.drawEllipse(begin,pen->width()/2,pen->width()/2);
       if(abs(begin.x() - end.x())>pen->width()/2 || abs(begin.y() - end.y())>pen->width()/2)
       {
           pLine.setPen(*pen);
           pLine.drawLine(begin, end);
       }
       pLine.end();
      begin = end;
        break;
       }
   case inRect:{ //прямоугольник
       int x = begin.x(), y = begin.y();
         if(begin.x() > end.x())
             x = end.x();
         if(begin.y() > end.y())
             y = end.y();
         *img = tmp;
         QPainter pRect;
         pRect.begin(img);
         pRect.setPen(*pen);
         pRect.setBrush(QBrush(Qt::red, Qt::NoBrush));

         double w = abs(begin.x() - end.x()), h = abs(begin.y() - end.y());
         pRect.drawRect(x, y, w, h);
         pRect.end();
       break;
}
   case inElips:{ //элипс
         *img = tmp;
         QPainter pCircle;
         pCircle.begin(img);
         pCircle.setPen(*pen);
         pCircle.setBrush(QBrush(Qt::red, Qt::NoBrush));
         QRect rect;
         int w = abs(begin.x() - end.x()), h = abs(begin.y() - end.y());
         pCircle.drawEllipse(begin, w, h);
         pCircle.end();
       break;

   }
   case inLine:{ // прямая
        *img = tmp;
       QPainter pPr;
       pPr.begin(img);
       pPr.setPen(*pen);
       pPr.setBrush(QBrush(Qt::red, Qt::NoBrush));
       pPr.drawLine(begin, end);
       pPr.end();
       break;
   }
   case inVydel:{ //  выделение
       int x = begin.x(), y = begin.y();
         if(begin.x() > end.x())
             x = end.x();
         if(begin.y() > end.y())
             y = end.y();
         double w = abs(begin.x() - end.x()), h = abs(begin.y() - end.y());

         if(!transform){
             shoot = false;
             *img = tmp;
             QPainter pRect;
            /* if(!i)
             {
                 i++;
                 tImg = *img;
             } */
             withoutRect = tmp ;
             pRect.begin(img);
             pRect.setPen(QPen(Qt::black, 1, Qt::DashLine));
             pRect.setBrush(QBrush(Qt::black, Qt::NoBrush));
             pRect.drawRect(x, y, w, h);
             pRect.end();
             rect = QRect(x+1, y+1, w-1, h-1);
             transf = img->copy(rect);
             rectImage = rect;
          //   img->
         }
         else{
           //  qDebug()<<rect.x()<<" "<< rect.y();

             int dx = begin.x() - end.x(), dy = begin.y() - end.y();
             *img = withoutRect;
             QPainter pRot, painter;
             if(!i){
                 painter.begin(&withoutRect);
                 painter.setPen(QPen(background, 1, Qt::SolidLine));
                 painter.setBrush(background);
                 painter.setBackgroundMode(Qt::OpaqueMode);
                 painter.setCompositionMode(QPainter::CompositionMode_Source);
              //   painter.fillRect(rect,background);
                 painter.drawRect(rect);
              //   painter.drawImage(rect, QImage(rect.width(),rect.height(), QImage::Format_ARGB32));
                 painter.end();
                 i++;
             }
             pRot.begin(img);
             pRot.setBackground(background);
             pRot.setPen(QPen(Qt::black, 1, Qt::DashLine));

             switch (typeCursor) {
             case Move:{
                 rect.translate(-dx,-dy);
                 break;
                }
             case ResizeVerticalUp:{
                 rect.setY(rect.y()-dy);
                 break;
                }
             case ResizeVerticalDown:{
                 rect.setHeight(rect.height()-dy);
                 break;
                }
             case ResizeGorizRight:{
                 rect.setWidth(rect.width()-dx);
                 break;
                }
             case ResizeGorizLeft:{
                 rect.setX(rect.x()-dx);
                 break;
                }
             case ResizeUpRight:{
                 rect.setY(rect.y()-dy);
                 rect.setWidth(rect.width()-dx);
                 break;
                }
             case ResizeUpLeft:{
                 rect.setY(rect.y()-dy);
                 rect.setX(rect.x()-dx);
                 break;
                }
             case ResizeDownRight:{
                 rect.setHeight(rect.height()-dy);
                 rect.setWidth(rect.width()-dx);
                 break;
                }
             case ResizeDownLeft:{
                 rect.setHeight(rect.height()-dy);
                 rect.setX(rect.x()-dx);
                 break;
                }

             }
             rectImage = rect;
             if(rectImage.width()<0) {
                 rectImage.setX(rectImage.x()+rectImage.width());
                 rectImage.setWidth(-rect.width());
                // rectImage.setX(rectImage.x()-rectImage.width());
             }
             if(rectImage.height()<0)
             {
                 rectImage.setY(rectImage.y()+rectImage.height());
                 rectImage.setHeight(-rect.height());
             }
            // qDebug()<<rect<<rectImage;
             pRot.drawImage(rectImage, transf);
             pRot.drawRect(rect);
             begin = end;
             pRot.end();
         }
      //   qDebug()<<background.color();
         break;

   }

       }
   update();
   event->accept();
}

void Plane:: mousePressEvent(QMouseEvent *event){
    emit before_clicked();
    begin = event->pos();
    shootRect();
    tmp = *img;
    press=true;
    event->accept();
    switch (typeInstrument){
    case inPen:{ // карандаш
        QPainter pLine;
        pLine.begin(img);
        pen->setCapStyle(Qt::RoundCap);
        pLine.setPen(QPen(pen->color(), 1));
        pLine.setBrush(QBrush(pen->color(), Qt:: SolidPattern));
        pLine.drawEllipse(begin, pen->width()/2,pen->width()/2);
        pLine.end();
        break;}
    case inlastis:{ // ластик
        QPainter pLine;
        pLine.begin(img);
        QPen tmp (background.color(),1 , Qt::SolidLine);
        tmp.setCapStyle(Qt::RoundCap);
        pLine.setPen(tmp);
        pLine.setBrush(QBrush(background.color(), Qt:: SolidPattern));
        pLine.drawEllipse(begin, pen->width()/2,pen->width()/2);
        pLine.end();
        break;}
    case inPipetka: {//Пипетка

        pen->setColor(img->pixelColor(begin));
        break;}

    case inZavivka: // заливка
    {
        if( pen->color().red() != img->pixelColor(begin).red() || pen->color().blue() != img->pixelColor(begin).blue()
                || pen->color().green() != img->pixelColor(begin).green() || pen->color().alpha() != img->pixelColor(begin).alpha())
        {
            LineFill(begin.x(), begin.y(), 1, begin.x(), begin.x());
        }
        break;
    }

    }
}

void Plane:: mouseReleaseEvent(QMouseEvent *event){
    press = false;    
    tmp = *img;
    transform = (typeInstrument == 4);
    if(shoot) transform = false;
    emit clicked();
    event->accept();

}

void Plane:: paintEvent(QPaintEvent *event){
    Layer illustration;
     illustration = Layer(width(), height(), QImage::Format_ARGB32);
    if(layers.empty()){
         return;
    }
    int countVis = 0;
    QPainter painter;
    painter.begin(this);
    painter.drawImage(0,0,*(SubLayer));
    painter.drawImage(0,0,*(illustrationDown));
    painter.setOpacity(img->dOpacity);
    if(img->getVisible()) painter.drawImage(0,0,*(img));
    painter.setOpacity(1);
    painter.drawImage(0,0,*(illustrationUp));
    painter.end();
    event->accept();
}

void Plane:: setIllustration(QList<Layer *> layer){
    layers = layer;
}

void Plane:: setIllustration(Layer *layer){
    layers.clear();
    layers.push_back(layer);

}

QRect Plane:: getRect(){
    return rect;
}

QImage Plane:: getTransf()
{
    return transf;
}

void Plane:: drawImage(QImage image, QRect rec)
{
    QPainter pRot;
    pRot.begin(img);
    pRot.drawImage(rec, image);
    pRot.end();
}

bool Plane:: videl()
{
    return transform;
}
void Plane:: delTransf(){
    shootRect();
    QPainter pRect;
    pRect.begin(img);
    pRect.setPen(QPen(background.color()));
    pRect.setBrush(background);
    pRect.drawRect(rect);
    pRect.end();

}


int Plane::  LineFill(int x, int y, int dir, int preXL, int preXR)
{
    int xl=x, xr=x;
    QColor col = img->pixelColor(x,y), cls;

        do
        {
            cls = img->pixelColor(--xl, y);
        }
        while(col == cls);

        do
        {
            cls = img->pixelColor(++xr, y);
        }
        while(col == cls);

        xl++, xr--;
        QPainter pLine;
        pLine.begin(img);
        pLine.setPen(QPen(pen->color(),1));
        pLine.drawLine(xl,y,xr,y);
        pLine.end();

        for(x=xl; x<=xr; x++)
        {
            cls = img->pixelColor(x, y+dir);
            if(cls == col)
                x = LineFill(x,y+dir,dir,xl,xr);
        }


        for(x=xl; x<=preXL; x++)
        {
            cls = img->pixelColor(x, y-dir);
            if(cls == col)
                x = LineFill(x,y-dir,-dir,xl,xr);
        }


        for(x=preXR; x<=xr; x++)
        {
            cls = img->pixelColor(x, y-dir);
            if(cls == col)
                x = LineFill(x,y-dir,-dir,xl,xr);
        }

        return xr;

}


QList<Layer*>*  Plane::  Layers()
{
    return &layers;
}

void Plane:: updateIllustration()
{
    if (illustrationDown == nullptr)
    {
        illustrationDown = new Layer(width(),height(), QImage::Format_ARGB32);
    }
    if (illustrationUp == nullptr)
    {
        illustrationUp = new Layer(width(),height(), QImage::Format_ARGB32);
    }
    if(SubLayer == nullptr)
    {
        SubLayer = new QImage(width(),height(), QImage::Format_ARGB32);
        *SubLayer = Layer::SubLayer(width(),height());
    }
    illustrationDown->claer();
    illustrationUp->claer();
    int indexImg = layers.size() - layers.indexOf(img) -1;
        for(int j = layers.size()-1; j>layers.indexOf(img); j--){
                if(layers[j]->getVisible()){
                    QPainter painter;
                       painter.begin(illustrationDown);
                       painter.setOpacity(layers[j]->dOpacity);
                       painter.drawImage(0,0,*(layers[j]));
                    painter.end();
        }}
        if(indexImg+1 != layers.size())
            for(int i = layers.indexOf(img)-1; i>=0; i--){
                 if(layers[i]->getVisible()){
                      QPainter painter;
                      painter.begin(illustrationUp);
                      painter.setOpacity(layers[i]->dOpacity);
                      painter.drawImage(0,0,*(layers[i]));
                      painter.end();
              }
        }
    update();
}

Layer* Plane:: getActiveLayer()
{
    return img;
}
