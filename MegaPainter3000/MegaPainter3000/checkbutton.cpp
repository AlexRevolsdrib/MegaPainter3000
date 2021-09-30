#include "checkbutton.h"

CheckButton::CheckButton(QWidget *parent) : QPushButton(parent)
{
    QFile file("D:/QtProject/MegaPainter3000/MegaPainter3000/CheckButton.css");
    file.open(QFile::ReadOnly);
    setStyleSheet(file.readAll());
    checked = true;
    setObjectName("Check");
}
bool CheckButton:: isChecked(){
   return checked;
}

void CheckButton:: setChecked(bool checked)
{
    this->checked = checked;
}

void CheckButton:: mousePressEvent(QMouseEvent *event)
{
    checked = !checked;
    checked?setObjectName("Check"):setObjectName("None");
    this->style()->polish(this);
    emit clicked();
    event->accept();
}
