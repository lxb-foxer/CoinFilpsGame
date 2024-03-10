#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include "mypushbutton.h"
#include <QDebug>
#include <QSound>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡场景
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

    QSound *chooseSound = new QSound(":/res/TapButtonSound.wav",this);
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);

    //返回按钮
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    connect(backBtn,&MyPushButton::clicked,[=](){
        qDebug()<<"点击了返回按钮";
        backSound->play();

        //告诉主场景，我返回了，主场景监听信号
        QTimer::singleShot(500,this,[=](){
            this->hide();
            //触发自定义信号，关闭自身，该信号写到signals下做声明
            emit this->chooselevelBack();
        });

    });


    //1-20的关卡按钮
    for(int i=0 ; i<20 ;i++){
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25 + i % 4 * 70,130 + i / 4 *70);

        connect(menuBtn,&MyPushButton::clicked,[=](){
            chooseSound->play();
            QString string = QString("你选择了第%1关卡").arg(i+1);
            qDebug()<<string;

            //进入选择的游戏关卡界面
            if(pScene == NULL){
                this->hide();
                pScene = new PlayScene(i+1);
                pScene->setGeometry(this->geometry());
                pScene->show();

                //playscene的返回按钮监听
                connect(pScene,&PlayScene::chooselevelBack,[=](){
                    this->setGeometry(pScene->geometry());
                    this->show();
                    delete pScene;
                    pScene = NULL;
                });
            }
        });

        //按钮上显示的文字
        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label->move(25 + i % 4 * 70,130 + i / 4 *70);
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;

    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}

