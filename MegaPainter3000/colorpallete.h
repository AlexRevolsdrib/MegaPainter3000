#ifndef COLORPALLETE_H
#define COLORPALLETE_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPoint>
#include <QPen>
#include <QBrush>
#include <math.h>
#include <QRect>
#include <QList>
#include <QColor>


class ColorPallete : public QWidget
{
    Q_OBJECT
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QImage img;
    QImage tmp;
public:
    explicit ColorPallete(QWidget *parent = nullptr);
signals:
    void clicked(QColor color);
public slots:
};

#endif // COLORPALLETE_H
