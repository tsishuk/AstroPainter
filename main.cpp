#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include "mywidget.h"
#include "updatefilter.h"
#include "imagedraw.h"


class Container : public QWidget
{
    //Q_OBJECT
public:
    //![1]
    Container(QWidget* parent = NULL)
        :QWidget(parent)
    {
        QHBoxLayout* hlayout = new QHBoxLayout;
        QPushButton* btn_left = new QPushButton("Press me LEFT");
        QPushButton* btn_right = new QPushButton("Press me RIGHT");

        MyWidget* wgt = new MyWidget;
        wgt->installEventFilter(new UpdateFilter(wgt));

        ImageDraw* img = new ImageDraw;
        img->resize(250,200);
        img->setFixedSize(250,200);

        hlayout->addWidget(btn_left);
        hlayout->addWidget(btn_right);
        hlayout->addWidget(wgt);
        hlayout->addWidget(img);

        setLayout(hlayout);
        this->setFixedSize(1200,600);
        //this->setWindowState();
    }
    //![1]


public slots:
    //![2]
    void EmptySlot()
    {
        qDebug()<<"I ama slot";
    }
    //![2]

};



int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    srand(QTime::currentTime().msec());

    Container cnt;
    cnt.show();

    return app.exec();
}
