#ifndef VISLAYER_H
#define VISLAYER_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <layer.h>

class VisLayer : public QWidget
{
    Q_OBJECT
public:
    explicit VisLayer(QWidget *parent = 0);
    void setLayer(Layer *layer);
    void paintBackgound();
    VisLayer(Layer *layer);
    Layer * Img(){return img;}
private:
    void paintEvent(QPaintEvent *event);
    Layer *img;
    QImage SubLayer;

signals:

public slots:
};

#endif // VISLAYER_H
