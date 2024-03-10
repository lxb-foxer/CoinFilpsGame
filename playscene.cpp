#include "playscene.h"
#include <QDebug>
#include <QPainter>
#include "mypushbutton.h"
#include <QMenuBar>
#include <QTimer>
#include <QLabel>
#include <QPropertyAnimation>
#include "mycoin.h"
#include "dataconfig.h"
#include <QSound>

//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScene::PlayScene(int level){
    this->levelIndex = level;

    QString str = QString("你当前进入到了第%1关").arg(level);
    qDebug()<<str;

    this->setFixedSize(320,588);

    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("选择关卡");

    //创建菜单栏
    QMenuBar * bar = this->menuBar();
    this->setMenuBar(bar);

    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");
    //创建按钮菜单项
    QAction * quitAction = startMenu->addAction("退出");
    //点击退出 退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });


    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);
    QSound *winSound = new QSound(":/res/LevelWinSound.wav",this);
    QSound *fSound = new QSound(":/res/ConFlipSound.wav",this);


    //返回按钮
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    connect(backBtn,&MyPushButton::clicked,[=](){
        qDebug()<<"在游戏界面，点击了返回按钮";
        backSound->play();
        //告诉选择关卡场景，我返回了，主场景监听信号

        QTimer::singleShot(500,this,[=](){
            this->hide();
            //触发自定义信号，关闭自身，该信号写到signals下做声明
            emit this->chooselevelBack();
        });

    });


    //游戏界面左下角的关卡数字显示
    QLabel *label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    QString str2= QString("Level: %1").arg(this->levelIndex);
    qDebug()<<str2;
    label->setText(str2);
    label->setGeometry(QRect(30,this->height()-50,140,50));

    //胜利图片显示
    QLabel * winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());

       //获取每一关金币的位置，放入数组中
       dataConfig config;
       for(int i=0;i<4;i++){
           for(int j=0;j<4;j++){
               gameArray[i][j]=config.mData[this->levelIndex][i][j];
           }
       }


    for(int i=0;i < 4 ; i++){
        for(int j=0; j<4; j++){
            //创建金币背景图片
            QLabel * label = new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode(1).png"));
            label->setParent(this);
            label->move(57 + i*50,200+j*50);


            QString img;
            if(gameArray[i][j]==1){
                img=":/res/Coin0001.png";
            }else{
                img=":/res/Coin0008.png";
            }

            //创建金币
            MyCoin * coin =new MyCoin(img);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j];

            coinBtn[i][j] = coin;

            //点击金币翻转
            connect(coin,&MyCoin::clicked,[=](){
                fSound->play();
                coin->changeFlag();
                gameArray[i][j] = gameArray[i][j] = 0?1:0;


                //翻转周围金币
                QTimer::singleShot(300,this,[=](){

                    //右边的金币
                    if(coin->posX+1<=3){
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        gameArray[coin->posX+1][coin->posY] = gameArray[coin->posX+1][coin->posY] = 0?1:0;
                    }

                    //左边的金币
                    if(coin->posX-1>=0){
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        gameArray[coin->posX-1][coin->posY] = gameArray[coin->posX-1][coin->posY] = 0?1:0;
                    }


                    //上边的金币
                    if(coin->posY-1>=0){
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        gameArray[coin->posX][coin->posY-1] = gameArray[coin->posX][coin->posY-1] = 0?1:0;
                    }


                    //下边的金币
                    if(coin->posY+1<=3){
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        gameArray[coin->posX][coin->posY+1] = gameArray[coin->posX][coin->posY+1] = 0?1:0;
                    }


                    this->isWin=true;
                    for(int i=0;i<4;i++){
                        for(int j=0;j<4;j++){
                            if(coinBtn[i][j]->flag==false){
                                this->isWin=false;
                                break;
                            }
                        }
                    }

                    if(this->isWin){
                        qDebug()<<"胜利";
                        winSound->play();
                        for(int i=0;i<4;i++){
                            for(int j=0;j<4;j++){
                                coinBtn[i][j]->isWin=true;
                            }
                        }

                        QPropertyAnimation * animation =new QPropertyAnimation(winLabel,"geometry");
                        //延迟时间
                        animation->setDuration(1000);
                        //起始位置
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        //结束位置
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                       //缓冲曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();
                    }


                });
            });

        }
    }


}

void PlayScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;

    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}
