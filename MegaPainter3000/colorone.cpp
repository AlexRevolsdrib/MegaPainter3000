#include "colorone.h"

ColorOne::ColorOne(QWidget *parent) : QWidget(parent)
{
    c = QColor(Qt::red);
}
void ColorOne:: mousePressEvent(QMouseEvent *event)
{
    emit clicked();
}

void ColorOne::  paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.fillRect(0,0,width(),height(),c);
    painter.end();
}
QColor ColorOne:: color()
{
    return c;
}

void ColorOne:: setColor(QColor color)
{
    c = color;
    update();
}
