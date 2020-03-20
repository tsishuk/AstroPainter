#ifndef MYWIDGET_H
#define MYWIDGET_H


#include <QtGui>
#include <QWidget>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    MyWidget(QWidget* parent = NULL);

public slots:
    void renderPoint();
    //void renderLeft();
   // void renderRight();

protected:
    void paintEvent(QPaintEvent* pe) Q_DECL_OVERRIDE;

private:
    int dummy;
};


#endif // MYWIDGET_H
