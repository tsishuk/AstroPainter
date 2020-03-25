#ifndef UPDATEFILTER
#define UPDATEFILTER

#include <QObject>

class UpdateFilter : public QObject
{
protected:
    virtual bool eventFilter(QObject *, QEvent *);

public:
    UpdateFilter(QObject* pobj = 0);

};

#endif // UPDATEFILTER

