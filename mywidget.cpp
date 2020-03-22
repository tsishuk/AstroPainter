#include "mywidget.h"
#include <QWidget>
#include <QPainter>


//! [1]
MyWidget::MyWidget(QWidget *parent):
    QWidget(parent),current_color(0)
{
    setFixedSize(670,550);
}
//! [1]


//! [2]
void MyWidget::paintEvent(QPaintEvent *pe)
{
    static const QPoint marker[3] = {
        QPoint(7, 7),
        QPoint(-7, 7),
        QPoint(0, 0)
    };

    QPainter painter(this);
    QBrush cur_brush;
    if (current_color == 0)
        cur_brush = QBrush(Qt::black);
    else if (current_color == 1)
        cur_brush = QBrush(Qt::green);
    else if (current_color == 2)
        cur_brush = QBrush(Qt::cyan);

    if (pe->rect().width() < this->width()-100)
        painter.fillRect(pe->rect(),cur_brush);
    else {
        QPainter painter(this);
        QBrush temp_brush = QBrush(Qt::yellow);
        painter.fillRect(pe->rect(),Qt::black);
        painter.fillRect(300,100,50,30,temp_brush);
        painter.setPen(QPen(Qt::darkGray, 1, Qt::DashLine));
        painter.setBrush(Qt::green);
        for(int i=20; i<=650; i+=40){
            painter.drawLine(QPoint(i,0), QPoint(i,512));
        }

        painter.save();
        painter.translate(20,400);
        painter.drawConvexPolygon(marker, 3);
        painter.translate(10,10);
        painter.drawConvexPolygon(marker, 3);
        painter.translate(10,1);
        painter.drawConvexPolygon(marker, 3);
        painter.translate(10,1);
        painter.drawConvexPolygon(marker, 3);
        painter.translate(10,1);
        painter.drawConvexPolygon(marker, 3);
        painter.translate(10,1);
        painter.drawConvexPolygon(marker, 3);
        painter.restore();
        int scale_counter = 0;
        for (int i=10; i<650; i+=40){
            if (scale_counter >= 127)
                scale_counter = 0;
            painter.drawText(i, 525, "0x"+QString::number(scale_counter, 16));
            scale_counter += 16;
        }
        //painter->drawText(QRectF(0, 0, width(), height()), Qt::AlignCenter, QStringLiteral("QWindow"));
    }
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

    this->update(upd_rect);
}


void MyWidget::renderRight()
{
    int width = this->width();
    int height = this->height();
    QRect upd_rect = QRect(width/2, height/2, width/2, height/2);
    current_color = 2;

    this->update(upd_rect);
}








