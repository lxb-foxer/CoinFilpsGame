#include "mycoin.h"
#include <QDebug>
#include<QPushButton>

//MyCoin::MyCoin(QWidget *parent) : QWidget(parent)
//{

//}

MyCoin::MyCoin(QString btnImg){
    QPixmap pixmap;
    bool ret = pixmap.load(btnImg);
    if(!ret){
        qDebug()<<btnImg<<"加载图片失败";
    }

    this->setFixedSize(pixmap.width(),pixmap.height());
    this->setStyleSheet("QPushButton{border : 0px;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));

    //初始化定时器
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //监听金翻银
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pixmap;
        QString str = QString(":/res/Coin000%1").arg(this->min++);
        pixmap.load(str);
        this->setFixedSize(pixmap.width(),pixmap.height());
        this->setStyleSheet("QPushButton{border : 0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
        if(this->min > this->max){
            this->min = 1;
            this->isAnimation = false;
            timer1->stop();
        }
    });


    //监听银翻金
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pixmap;
        QString str = QString(":/res/Coin000%1").arg(this->max--);
        pixmap.load(str);
        this->setFixedSize(pixmap.width(),pixmap.height());
        this->setStyleSheet("QPushButton{border : 0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
        if(this->min > this->max){
            this->max = 8;
            this->isAnimation = false;
            timer2->stop();
        }
    });
}


void MyCoin::changeFlag(){
    this->isAnimation = true;
    if(this->flag){
        timer1->start(30);
        this->flag = false;
    }else{
        timer2->start(30);
        this->flag = true;
    }
}


void MyCoin::mousePressEvent(QMouseEvent *e){
    if(this->isAnimation || this->isWin){
        return;
    }else{
        return QPushButton::mousePressEvent(e);
    }
}
