#ifndef MYCOIN_H
#define MYCOIN_H
#include <QTimer>
#include <QPushButton>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString btnImg);

    int posX; //x坐标
    int posY; //y坐标
    bool flag; //正反标志


    QTimer *timer1; //金翻银
    QTimer *timer2; //银翻金
    int min = 1; //最小图片
    int max = 8; //最大图片
    bool isAnimation = false;
    bool isWin = false;



    void mousePressEvent(QMouseEvent *e);
    void changeFlag(); //改变标志，执行翻转效果


signals:

};

#endif // MYCOIN_H
