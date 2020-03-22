#include "mywidget.h"
#include <QWidget>
#include <QPainter>


//! [1]
MyWidget::MyWidget(QWidget *parent):
    QWidget(parent),current_color(0)
{
    setFixedSize(520,520);
    //setAttribute(Qt::WA_PaintOnScreen);
}
//! [1]


//! [2]
void MyWidget::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);
    QBrush cur_brush;
    if (current_color == 0)
        cur_brush = QBrush(Qt::red);
    else if (current_color == 1)
        cur_brush = QBrush(Qt::green);
    else if (current_color == 2)
        cur_brush = QBrush(Qt::cyan);
    painter.fillRect(0, 0, width(), height(), Qt::white);
    //painter.fillRect(pe->rect(),Qt::cyan);
    painter.fillRect(pe->rect(),cur_brush);
    qDebug()<<"PaintEvent: Width = "<< width() <<" Height = "<< height() << "Foot.x = "<<pe->rect().bottomLeft().x()<<"Foot.y = "<<pe->rect().bottomLeft().y()
           <<"Top.x = "<<pe->rect().topRight().x()<<"Top.y = "<<pe->rect().topRight().y();
}
//! [2]


void MyWidget::renderPoint()
{
    ;
}


void MyWidget::renderLeft()
{
    int width = this->width();
    int height = this->height();
    QRect upd_rect = QRect(0, 0, width/2, height/2);
    current_color = 1;
    //update(0, 0, width/2, height/2);
    this->update(upd_rect);
    //this->update();
    qDebug()<<"renderLeft: Width = "<< this->width() <<" Height = "<< this->height() << "Foot.x = "<<upd_rect.bottomLeft().x()<<"Foot.y = "<<upd_rect.bottomLeft().y()
           <<"Top.x = "<<upd_rect.topRight().x()<<"Top.y = "<<upd_rect.topRight().y();
}


void MyWidget::renderRight()
{
    int width = this->width();
    int height = this->height();
    QRect upd_rect = QRect(width/2, height/2, width, height);
    current_color = 2;
    qDebug()<<"width = "<<width;
    qDebug()<<"renderRight: Width = "<< this->width() <<" Height = "<< this->height() << "Foot.x = "<<upd_rect.bottomLeft().x()<<"Foot.y = "<<upd_rect.bottomLeft().y()
           <<"Top.x = "<<upd_rect.topRight().x()<<"Top.y = "<<upd_rect.topRight().y();
    this->update(upd_rect);
    //this->update();
}








