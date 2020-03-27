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
    void updateMarker();
    void findMax();

protected:
    void paintEvent(QPaintEvent* pe) Q_DECL_OVERRIDE;

private:
    //int offset;
    int current_fv;
    int marker_counter;
    int kf_value;
    int adc_value;
    int current_indeks;
    static int values_of_markers[64];
    int indeks1, indeks2;
    int min1, min2;
};


#endif // MYWIDGET_H
