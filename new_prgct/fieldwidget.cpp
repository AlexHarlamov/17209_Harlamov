#include "fieldwidget.h"

#include "../lab2/Field.h"

#include <QPainter>
#include <math.h>
#include <iostream>

FieldWidget::FieldWidget(QWidget *parent) : QWidget(parent)
{

}

QBrush make_color(int pos){
    int num_of_wrr = Field::getGlobal()->last_visit_at(pos);
    if( num_of_wrr == -1){
        return QBrush(QColor(10,102,163));
    }
    else {
        int r=0;
        int g=0;
        int b=0;
        r = (50*(num_of_wrr+1))%255;
        g = (100*(num_of_wrr+1))%255;
        b = (50*(num_of_wrr+1))%255;
        return QBrush(QColor(r,g,b));
    }
}

void FieldWidget::paintEvent(QPaintEvent *event){
    QPainter painter1(this);

    painter1.setRenderHint(QPainter::Antialiasing);
    painter1.setPen (QPen(QColor(11,139,224),Qt::SolidLine));

    double S1 = (width()*height())/Field::getGlobal()->give_size();
    double w1 = sqrt(S1);
    int in_line = (int)(width() / w1);
    int in_column = (int)(height()/w1)+1;
    w1 = height()/in_column;
   // std::cout<<"w - "<<width()<<" h - "<<height()<<" w1 - "<<w1<<" in line - "<<in_line <<" in column - "<<in_column<<std::endl;
    int start_x = (width() - in_line*w1)/2;
    int start_y = (height() - in_column*w1)/2;
    int pos = 0;
    for(int i = 0; i < in_column - 1; i++){
        for(int j = 0; j < in_line; j++){
            painter1.setBrush(make_color(pos));
            painter1.drawRect(start_x+j*w1,start_y+i*w1,w1,w1);
            pos++;
        }
    }
    int count = Field::getGlobal()->give_size()-(in_column-1)*in_line;
    start_x = (width() - count*w1)/2;
    for(int i = in_column-1, j=0; j< count; j++){
        painter1.setBrush(make_color(pos));
        painter1.drawRect(start_x+j*w1,start_y+i*w1,w1,w1);
        pos++;
    }

    //painter1.restore();
}
