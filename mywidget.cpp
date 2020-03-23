#include "mywidget.h"
#include <QWidget>
#include <QPainter>


//! [1]
MyWidget::MyWidget(QWidget *parent):
    QWidget(parent),
    current_fv(0), marker_counter(0)
{
    setFixedSize(670,550);
    this->setUpdatesEnabled(true);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMarker()));
    timer->start(2000);
}
//! [1]



void MyWidget::updateMarker()
{
    static int step_counter = 0;

    int fv = 1;

    this->update(100+step_counter,100+step_counter,100,50);

    if (fv != current_fv){
        current_fv = fv;
        step_counter = 0;
        for (int i=0;i<64;i++)
            values_of_markers[i] = 0;
    }

    step_counter++;
    marker_counter++;
    if (marker_counter >= 32)
        marker_counter = 0;

    if (step_counter < 64){
        adc_value = rand()%512;
        kf_value = marker_counter*4;
        QRect upd_rect(15+step_counter*10,0,30,512);
        qDebug()<<"update_part: left: "<<upd_rect.left()<< " right: "<<upd_rect.right()<<" kf_value = "
               <<kf_value<< " adc_value = "<<adc_value;
        //this->update(upd_rect);
    }
}



//! [2]
void MyWidget::paintEvent(QPaintEvent *pe)
{
    static const QPoint marker[3] = {
        QPoint(5, 5),
        QPoint(-5, 5),
        QPoint(0, 0)
    };

    static const QPoint second_marker[3] = {
        QPoint(5, 5),
        QPoint(7,0),
        QPoint(1, 1)
    };


    // If update event for part of widget
    if ((pe->rect()).width() < 300){
        QPainter painter(this);
        painter.setPen(QPen(Qt::darkGray, 1, Qt::DashLine));
        painter.setBrush(Qt::green);
        painter.drawPoint(10,10);
        //painter.fillRect(pe->rect(), Qt::red);
//        QPainter painter(this);
//        //painter.save();
//        painter.setPen(Qt::NoPen);
//        //painter.fillRect(pe->rect(),Qt::black);
//        painter.setBrush(Qt::green);
//        painter.drawConvexPolygon(second_marker, 3);
//        //painter.translate(0, adc_value);
//        painter.fillRect(0,0,10,10,Qt::red);
//        //
//        painter.setPen(QPen(Qt::darkGray, 1, Qt::DashLine));
//        painter.drawText(10, 10 , "0x");

//        painter.drawConvexPolygon(marker, 3);
//        qDebug()<<"draw polygon";
//        //painter.restore();
//        painter.end();
    }

    // update event for whole widget
    else {
        QPainter painter(this);
        //QBrush temp_brush = QBrush(Qt::yellow);
        painter.fillRect(pe->rect(),Qt::black);
        //painter.fillRect(300,100,50,30,temp_brush);   // Fill yellow rect
        painter.setPen(QPen(Qt::darkGray, 1, Qt::DashLine));
        painter.setBrush(Qt::green);

        // Paint vertical grid
        for(int i=20; i<=650; i+=40){
            painter.drawLine(QPoint(i,0), QPoint(i,512));
        }

        painter.save();
        painter.setPen(Qt::NoPen);
        painter.translate(20,300);

        // Paint markers
        painter.drawConvexPolygon(marker, 3);
        painter.translate(10,10);
        for (int i=0; i<32;i++){
            painter.drawConvexPolygon(marker, 3);
            painter.translate(10,1);
        }
        painter.restore();
        int scale_counter = 0;

        // Paint hex labels under vertical grid
        for (int i=10; i<650; i+=40){
            if (scale_counter >= 127)
                scale_counter = 0;
            painter.drawText(i, 525, "0x"+QString::number(scale_counter, 16));
            scale_counter += 16;
        }
        painter.end();
    }

    //painter.end();
}
//! [2]



void MyWidget::paintMarker(int faza, int value)
{
    static const QPoint marker[3] = {
        QPoint(5, 5),
        QPoint(-5, 5),
        QPoint(0, 0)
    };

    qDebug()<<"In paintMarker()";

    int trunc_value = value/8;  // Truncate for paint oxFFF in 512 pixels

//    if (faza != current_faza){
//        marker_counter = 0;
//        for (int i=0;i<64;i++)
//            values_of_markers[i] = 0;
//    }

    QPainter painter(this);

    marker_counter++;
    // Move X to the current position
    // Clear current at next markers
    painter.fillRect(-5,0,20,512,Qt::black);

    painter.setPen(QPen(Qt::darkGray, 1, Qt::DashLine));
    painter.setBrush(Qt::green);
    if ((marker_counter % 4) == 0)
        painter.drawLine(QPoint(0,0), QPoint(0,512));
    // Move Y to the current position
    painter.translate(0,trunc_value);
    painter.drawConvexPolygon(marker, 3);

    painter.end();
}



//! [3]
void MyWidget::renderLeft()
{
    int width = this->width();
    int height = this->height();
    QRect upd_rect = QRect(0, 0, width/2, height/2);
    //current_color = 1;

    this->update(upd_rect);
}
//! [3]



//! [4]
void MyWidget::renderRight()
{
    int width = this->width();
    int height = this->height();
    QRect upd_rect = QRect(width/2, height/2, width/2, height/2);
    //current_color = 2;

    this->update(upd_rect);
}
//! [4]







