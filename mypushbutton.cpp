#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>

//MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
//{

//}

MyPushButton::MyPushButton(QString normalImg , QString pressImg )
{
    this->normalImaPath = normalImg;
    this->pressImgPath = pressImg;

    QPixmap pix;
    bool flag = pix.load(normalImg);
    if(!flag)
    {
        qDebug()<<"图片加载失败";
        return;
    }

    this->setFixedSize(pix.width(),pix.height());

    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border : 0px;}");

    //设置图标
    this->setIcon(pix);

    this->setIconSize(QSize(pix.width(),pix.height()));
}

void MyPushButton::zoom1()
{
    //向下跳
    //创建动态对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();



    //向上跳
    //创建动态对象
    QPropertyAnimation * animation2 = new QPropertyAnimation(this,"geometry");

    //设置动画时间间隔
    animation2->setDuration(200);

    //起始位置
    animation2->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //结束位置
    animation2->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置弹跳曲线
    animation2->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation2->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *e){

    if(this->pressImgPath!=""){
        QPixmap pix;
        bool flag = pix.load(this->pressImgPath);
        if(!flag)
        {
            qDebug()<<"图片加载失败";
            return;
        }

        this->setFixedSize(pix.width(),pix.height());

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border : 0px;}");

        //设置图标
        this->setIcon(pix);

        this->setIconSize(QSize(pix.width(),pix.height()));
    }


    return QPushButton::mousePressEvent(e);
}


void MyPushButton::mouseReleaseEvent(QMouseEvent *e){

    if(this->normalImaPath!=""){
        QPixmap pix;
        bool flag = pix.load(this->normalImaPath);
        if(!flag)
        {
            qDebug()<<"图片加载失败";
            return;
        }

        this->setFixedSize(pix.width(),pix.height());

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border : 0px;}");

        //设置图标
        this->setIcon(pix);

        this->setIconSize(QSize(pix.width(),pix.height()));
    }


    return QPushButton::mouseReleaseEvent(e);
}
