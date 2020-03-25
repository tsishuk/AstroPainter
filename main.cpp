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

        hlayout->addWidget(btn_left);
        hlayout->addWidget(btn_right);
        hlayout->addWidget(wgt);

        setLayout(hlayout);

        this->setFixedSize(900,600);
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
