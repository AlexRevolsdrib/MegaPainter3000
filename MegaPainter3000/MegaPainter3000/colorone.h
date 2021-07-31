#ifndef COLORONE_H
#define COLORONE_H

#include <QWidget>
#include <QImage>
#include <QColor>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPoint>
#include <QPen>
#include <QBrush>
#include <math.h>
#include <QRect>
#include <layer.h>

class ColorOne : public QWidget
{
    Q_OBJECT
public:
    explicit ColorOne(QWidget *parent = 0);
    QColor color();
    void setColor(QColor);
private:
    void mousePressEvent(QMouseEvent *event);
    void  paintEvent(QPaintEvent *event);
    //QImage img;
    QColor c;
signals:
    void clicked();
public slots:
};

#endif // COLORONE_H
