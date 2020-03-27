#include "mywidget.h"
#include <QWidget>
#include <QPainter>
#include <QtGui>

#define FIRST_MARKER_OFFSET 20


//! [1]
MyWidget::MyWidget(QWidget *parent):
    QWidget(parent),
    current_fv(0),  marker_counter(0),
    adc_value(-1), current_indeks(0)
{
    setFixedSize(680,550);
    this->setMouseTracking(true);

    // First init when widget create
    for (int i=0;i<64;i++){
        marker_values[i] = -1;
        adc_values[i] = -1;
    }

    indeks1 = indeks2 = -1;

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMarker()));
    timer->start(30);
}
//! [1]



//! [0]
void MyWidget::mouseMoveEvent(QMouseEvent *pe)
{
    int x_indeks=-1;
    if (pe->x()>(FIRST_MARKER_OFFSET-5)){
        x_indeks = (pe->x()-FIRST_MARKER_OFFSET)/10;
        if ((pe->y() < (marker_values[x_indeks] + 6))&&(pe->y() > (marker_values[x_indeks] - 1)))
            qDebug()<<"in marker area " << x_indeks;
    }

    //qDebug()<<"x = "<<pe->x()<<"y = "<<pe->y()<<"x_indeks = "<<x_indeks;
}
//! [0]



//! [3]
void MyWidget::updateMarker()
{
    static int step_counter = 0;

    int fv = 1;

    // Initialize array of values when fv change
    if (fv != current_fv){
        current_fv = fv;
        step_counter = 0;

        // TODO: INIT Variables when change fv
        for (int i=0;i<64;i++){
            marker_values[i] = -1;
            adc_values[i] = -1;
        }
    }

    // Generate random adc value and update region for current fv
    if (step_counter < 64){
        adc_value = rand()%512;
        kf_value = marker_counter*4;
        current_indeks = step_counter;
        QRect upd_rect(FIRST_MARKER_OFFSET + step_counter*10, 0, 10, 512);  // Update whole rect for current fv
        adc_values[step_counter] = adc_value;
        marker_values[step_counter] = 512-adc_value;
        qDebug()<<"update_part: left: "<< upd_rect.left() << " right: "<<upd_rect.right() <<" kf_value = "
               << kf_value << " adc_value =" << adc_value << "marker_value = "<<marker_values[step_counter];
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
    int i;
    static const QPoint marker[3] = {
        QPoint(5, 5),
        QPoint(-5, 5),
        QPoint(0, 0)
    };

    //--------------------------------------------------
    //
    QImage   img(size(), QImage::Format_ARGB32_Premultiplied);
    QPainter painter;

    painter.begin(&img);
    painter.initFrom(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.eraseRect(rect());

    painter.fillRect(pe->rect(),Qt::black);
    painter.setPen(QPen(Qt::darkGray, 1, Qt::DashLine));
    painter.setBrush(Qt::green);

    // Paint vertical grid
    for(int i=FIRST_MARKER_OFFSET+5; i<=670; i+=40){
        painter.drawLine(QPoint(i,0), QPoint(i,512));
    }

    // Paint hex labels under vertical grid
    int scale_counter = 0;
    for (i=(FIRST_MARKER_OFFSET-5); i<660; i+=40){
        if (scale_counter >= 127)
            scale_counter = 0;
        painter.drawText(i, 525, "0x"+QString::number(scale_counter, 16));
        scale_counter += 16;
    }

    // Draw markers
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::green);
    painter.translate(FIRST_MARKER_OFFSET-5, 0);
    for (i=0;i<64;i++){
        if ((i == indeks1)||(i == indeks2))
            painter.setBrush(Qt::red);
        else
            painter.setBrush(Qt::green);
        if (adc_values[i] >= 0){
            painter.translate(10, marker_values[i]);
            painter.drawConvexPolygon(marker, 3);
            painter.translate(0, -marker_values[i]);
        }
        else
            painter.translate(10, 0);
    }

    painter.end();

    painter.begin(this);
    painter.drawImage(0, 0, img);
    painter.end();
}
//! [2]



//! [4]
void MyWidget::findMax()
{
    min1 = min2 = 0xFFF;
    indeks1 = indeks2 = -1;

//    for (int i=0; i<64; i++)
//        qDebug()<< i <<" "<<adc_values[i];

    for (int i=0; i<32;i++){
        if (adc_values[i]<min1){
            min1 = adc_values[i];
            indeks1 = i;
        }
    }

    for (int i=32; i<64;i++){
        if (adc_values[i]<min2){
            min2 = adc_values[i];
            indeks2 = i;
        }
    }

    qDebug()<< "min1=" << min1 << "kf = "<<QString::number((indeks1*4)%128, 16);
    qDebug()<< "min2=" << min2 << "kf = "<<QString::number((indeks2*4)%128, 16);

    this->update();
}
//! [4]




