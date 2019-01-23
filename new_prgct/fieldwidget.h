#ifndef FIELDWIDGET_H
#define FIELDWIDGET_H

#include <QWidget>
#include <QPainter>

class FieldWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FieldWidget(QWidget *parent = nullptr);

    void Field_upd(){
        //paintEvent();
    }

signals:

public slots:

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // FIELDWIDGET_H
