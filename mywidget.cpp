#include "mywidget.h"
#include <QWidget>
#include <QPainter>


//! [1]
MyWidget::MyWidget(QWidget *parent):
    QWidget(parent),
    current_fv(0),  marker_counter(0),
    adc_value(-1), current_indeks(0)
{
    setFixedSize(680,550);
    this->setUpdatesEnabled(true);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMarker()));
    timer->start(1000);
}
//! [1]



void MyWidget::updateMarker()
{
    static int step_counter = 0;

    int fv = 1;

    //this->update(100+step_counter,100+step_counter,200,200);

    if (fv != current_fv){
        current_fv = fv;
        step_counter = 0;
        for (int i=0;i<64;i++)
            values_of_markers[i] = 0;
    }

    if (step_counter < 64){
        adc_value = rand()%512;
        kf_value = marker_counter*4;
        current_indeks = step_counter;
        QRect upd_rect(15+step_counter*10,0,10,512);
        qDebug()<<"update_part: left: "<< upd_rect.left() << " right: "<<upd_rect.right() <<" kf_value = "
               << kf_value << " adc_value =" << adc_value;
        this->update(upd_rect);
    }

    step_counter++;
    marker_counter++;
    if (marker_counter >= 32)
        marker_counter = 0;
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

    //--------------------------------------------------
    //
    QPainter painter(this);
    painter.fillRect(pe->rect(),Qt::black);
    painter.setPen(QPen(Qt::darkGray, 1, Qt::DashLine));
    painter.setBrush(Qt::green);

    // Paint vertical grid
    for(int i=20; i<=660; i+=40){
        painter.drawLine(QPoint(i,0), QPoint(i,512));
    }

    //        painter.save();
    //        painter.setPen(Qt::NoPen);
    //        painter.translate(20,300);

    //        // Paint markers
    //        painter.drawConvexPolygon(marker, 3);
    //        painter.translate(10,10);
    //        for (int i=0; i<32;i++){
    //            painter.drawConvexPolygon(marker, 3);
    //            painter.translate(10,1);
    //        }


    //        painter.restore();

    // Paint hex labels under vertical grid
    int scale_counter = 0;
    for (int i=10; i<660; i+=40){
        if (scale_counter >= 127)
            scale_counter = 0;
        painter.drawText(i, 525, "0x"+QString::number(scale_counter, 16));
        scale_counter += 16;
    }
    //
    //--------------------------------------------------


    // If there non-zero adc_value, paint it in update region
    if (adc_value >= 0){
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::green);
        painter.translate(pe->rect().x() + 5, 512-adc_value);
        painter.drawConvexPolygon(marker, 3);
        qDebug()<<"kf_value = 0x"<<QString::number(kf_value,16);
        values_of_markers[current_indeks] = adc_value;   // store current adc value in array
    }

    painter.end();
//    }

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







