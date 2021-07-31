#ifndef PLANE_H
#define PLANE_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPoint>
#include <QPen>
#include <QBrush>
#include <math.h>
#include <QRect>
#include <layer.h>
#include <QList>
#include <QQueue>
#include <QStack>

//константы определющие положение курсора и действие при выделении
const int Normal = 0;
const int Move = 1;
const int ResizeGorizRight = 2;
const int ResizeGorizLeft = 3;
const int ResizeVerticalUp = 4;
const int ResizeVerticalDown = 5;
const int ResizeUpLeft = 6;
const int ResizeUpRight = 7;
const int ResizeDownLeft = 8;
const int ResizeDownRight = 9;

//константы для инструментов
const int inPen = 10;
const int inBrush1 = 11;
const int inBrush2 = 20;
const int inBrush3 = 21;
const int inRect = 12;
const int inLine = 13;
const int inElips = 14;
const int inVydel = 4;

const int inPipetka = 16;
const int inlastis = 17;
const int inZavivka = 5;
const int inLupa = 19;


class Plane : public QWidget
{
    Q_OBJECT
public:
    explicit Plane(QWidget *parent = 0);
    void setInstrument(int type); // установить тип инструмента
    void setImg(Layer *layer); //установить активный слой
    void setIllustration(QList<Layer*> layer); //установить слои визуализации
    void setIllustration(Layer* layer); // установить один слой, который всегда виден
    void setPen(QPen *pen);
    int getInstrument();
    QRect getRect();
    QImage getTransf();
    void delTransf();
    void drawImage(QImage image, QRect rec);
    bool videl();
    QList<Layer*>* Layers();
    Layer* getActiveLayer();
    void updateIllustration();
private:
    bool shootRect(); // снять выделение
    //обработка событий
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    QImage *SubLayer;

    int  LineFill(int x, int y, int dir, int preXL, int preXR);//заливка

    QList<Layer*> layers; //список слоев
    Layer *img, tmp, withoutRect, *illustrationDown, *illustrationUp; // img - активный слой, tmp - доп слой, хранит изобржение до нажатия кнопки
    // withoutRect - слой без выделения (служит дл сняти выделения
    QPoint begin, end; //коортинаты точки нажатия (начала, конца)
    int typeInstrument; //тип инструмента рисования
    bool press, transform, shoot; //press - кнопка нажата, transorm - область выделена и можно трасформировать,
    //shoot - снять выделение
    QRect rect; //выделенная область
    QRect rectImage; // Выделенная область с положительной высотой и шириной для отрисовки выделенного изображения
    QImage transf; // часть выделенного изображения
    int i; // служит логической переменной, когда нужно скопировать img в withoutRect
    QBrush background; //фон
    QPen *pen;// цвет и толщина линии
    int typeCursor; // тип курсора
QSize sizeHint() const
{
    return QSize(10,10);
}

signals:
    void clicked();
    void before_clicked();
public slots:
};

#endif // PLANE_H
