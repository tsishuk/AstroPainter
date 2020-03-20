#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include "mywidget.h"


class Container : public QWidget
{
    //Q_OBJECT
public:
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

        //connect(btn_left, SIGNAL(clicked(bool)), wgt, SLOT(renderLeft()));
        //connect(btn_right, SIGNAL(clicked(bool)), wgt, SLOT(renderRight()));

        setLayout(hlayout);
    }
};


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Container cnt;
    cnt.show();

    return app.exec();
}
