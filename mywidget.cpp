#include "mywidget.h"
#include <QWidget>
#include <QPainter>


//! [1]
MyWidget::MyWidget(QWidget *parent):
    QWidget(parent)
{
    setFixedSize(520,520);
}
//! [1]


//! [2]
void MyWidget::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);

    painter.fillRect(0, 0, width(), height(), Qt::white);
    painter.fillRect(pe->rect(),Qt::green);
}
//! [2]


void MyWidget::renderPoint()
{
    ;
}

/*
void MyWidget::renderLeft()
{
    int width = this->width();
    int height = this->height();
    update(0, 0, width/2, height/2);
}


void MyWidget::renderRight()
{
    int width = this->width();
    int height = this->height();
    update(width/2, height/2, width, height);
}
*/







