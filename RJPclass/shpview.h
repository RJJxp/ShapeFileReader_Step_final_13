#ifndef SHPVIEW_H
#define SHPVIEW_H

#include <QWidget>

class shpView : public QWidget
{
    Q_OBJECT
public:
    explicit shpView(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent *event);

};

#endif // SHPVIEW_H
