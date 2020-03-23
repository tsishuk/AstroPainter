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
    void renderLeft();
    void renderRight();
    void paintMarker(int faza, int value);
    void updateMarker();

protected:
    void paintEvent(QPaintEvent* pe) Q_DECL_OVERRIDE;

private:
    int current_color;
    int offset;
    int current_faza;
    int marker_counter;
    int values[64];
};


#endif // MYWIDGET_H
