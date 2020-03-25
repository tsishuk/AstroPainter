#ifndef UPDATEFILTER
#define UPDATEFILTER

#include <QObject>
#include <QEvent>

class UpdateFilter : public QObject
{
protected:
    bool eventFilter(QObject *, QEvent *);

public:
    UpdateFilter(QObject* pobj = 0);

};

#endif // UPDATEFILTER

