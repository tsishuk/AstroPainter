#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include "mywidget.h"


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

        QObject::connect(btn_left, SIGNAL(clicked(bool)), wgt, SLOT(renderLeft()));
        QObject::connect(btn_right, SIGNAL(clicked(bool)), wgt, SLOT(renderRight()));

        setLayout(hlayout);

        this->startTimer(3000);
    }
    //![1]


    //![2]
public slots:
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
