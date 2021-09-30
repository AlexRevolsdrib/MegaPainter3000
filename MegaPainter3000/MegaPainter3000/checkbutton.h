#ifndef CHECKBUTTON_H
#define CHECKBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QFile>
#include <QStyle>

class CheckButton : public QPushButton
{
    Q_OBJECT
    bool checked;
    void mousePressEvent(QMouseEvent *event);
public:
    explicit CheckButton(QWidget *parent = nullptr);
    bool isChecked();
    void setChecked(bool checked);


signals:

public slots:
};

#endif // CHECKBUTTON_H
