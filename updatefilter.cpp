#include <QtWidgets>
#include "updatefilter.h"

//[1]
UpdateFilter::UpdateFilter(QObject *pobj)
    :QObject(pobj)
{}
//[1]

//[2]
bool UpdateFilter::eventFilter(QObject *pobj, QEvent *pe)
{
    qDebug()<<"IN Event Filter"<<"type = "<< pe->type();

    if (pe->type() == QEvent::WindowActivate){
        return true;
    }
    if (pe->type() == QEvent::WindowDeactivate){
        return true;
    }

    qDebug()<<"Event" << pe->type() << "->Exit";
    return false;
}
//[2]

/*

#include <QtWidgets>
#include "MouseFilter.h"

// ----------------------------------------------------------------------
MouseFilter::MouseFilter(QObject* pobj)
    : QObject(pobj)
{
}

// ----------------------------------------------------------------------
bool MouseFilter::eventFilter(QObject* pobj, QEvent* pe)
{
    if (pe->type() == QEvent::MouseButtonPress) {
        if (static_cast<QMouseEvent*>(pe)->button() == Qt::LeftButton) {
            QString strClassName = pobj->metaObject()->className();
            QMessageBox::information(0, "Class Name", strClassName);
            return true;
        }
        if (static_cast<QMouseEvent*>(pe)->button() == Qt::RightButton){
            //pobj->deleteLater();  //program crash
            //QWidget* pwgt = static_cast<QObject*>(pobj);
            QMessageBox::information(0, "Right Button Pressed","Right Button Pressed");
            //QObject::destroyed(pobj);
            return true;
        }
    }
    return false;
}
*/
