#include "mywidget.h"
#include <QWidget>
#include <QPainter>

#define FIRST_MARKER_OFFSET 20


//! [1]
MyWidget::MyWidget(QWidget *parent):
    QWidget(parent),
    current_fv(0),  marker_counter(0),
    adc_value(-1), current_indeks(0)
{
    setFixedSize(680,550);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMarker()));
    timer->start(50);
}
//! [1]


//! [3]
void MyWidget::updateMarker()
{
    static int step_counter = 0;

    int fv = 1;

    // Initialize array of values when fv change
    if (fv != current_fv){
        this->setUpdatesEnabled(true);
        current_fv = fv;
        step_counter = 0;
        for (int i=0;i<64;i++)
            values_of_markers[i] = -1;
    }

    // Generate random adc value and update region for current fv
    if (step_counter < 64){
        adc_value = rand()%512;
        kf_value = marker_counter*4;
        current_indeks = step_counter;
        QRect upd_rect(FIRST_MARKER_OFFSET + step_counter*10, 0, 10, 512);  // Update whole rect for current fv
        qDebug()<<"update_part: left: "<< upd_rect.left() << " right: "<<upd_rect.right() <<" kf_value = "
               << kf_value << " adc_value =" << adc_value;
        this->update(upd_rect);
    }

    if (step_counter == 64)
    {
        findMax();
    }

    step_counter++;
    marker_counter++;
    if (marker_counter >= 32)
        marker_counter = 0;

}
//! [3]



//! [2]
void MyWidget::paintEvent(QPaintEvent *pe)
{
    static const QPoint marker[3] = {
        QPoint(5, 5),
        QPoint(-5, 5),
        QPoint(0, 0)
    };

    //--------------------------------------------------
    //
    QPainter painter(this);
    painter.fillRect(pe->rect(),Qt::black);
    painter.setPen(QPen(Qt::darkGray, 1, Qt::DashLine));
    painter.setBrush(Qt::green);

    // Paint vertical grid
    for(int i=FIRST_MARKER_OFFSET+5; i<=670; i+=40){
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
    for (int i=(FIRST_MARKER_OFFSET-5); i<660; i+=40){
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
        //qDebug()<<"kf_value = 0x"<<QString::number(kf_value,16);
        values_of_markers[current_indeks] = adc_value;   // store current adc value in array
    }

    painter.end();
//    }

}
//! [2]



//! [4]
void MyWidget::findMax()
{
    int indeks1, indeks2;
    int min1, min2;
    min1 = min2 = 0xFFF;
    indeks1 = indeks2 = 0;
    for (int i=0; i<64; i++)
        qDebug()<< i <<" "<<values_of_markers[i];

    for (int i=0; i<32;i++){
        if (values_of_markers[i]<min1){
            min1 = values_of_markers[i];
            indeks1 = i;
        }
    }

    for (int i=32; i<64;i++){
        if (values_of_markers[i]<min2){
            min2 = values_of_markers[i];
            indeks2 = i;
        }
    }

    qDebug()<< "min1=" << min1 << "indeks1 = " << indeks1;
    qDebug()<< "min2=" << min2 << "indeks2 = " << indeks2;

    this->setUpdatesEnabled(false);
    qDebug()<<"Updates enabled = "<<this->updatesEnabled();
}
//! [4]




