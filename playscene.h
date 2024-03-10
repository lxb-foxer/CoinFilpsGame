#ifndef PLAYSCENE_H
#define PLAYSCENE_H
#include <QMainWindow>
#include <mycoin.h>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
//    explicit PlayScene(QWidget *parent = nullptr);

      PlayScene(int levelChoose);

      void paintEvent(QPaintEvent *);

      int levelIndex;

      bool isWin;  //判断是否胜利

      int gameArray[4][4]; //二维数组数据

      MyCoin *coinBtn[4][4]; //金币按钮数组

signals:
    void chooselevelBack();
};

#endif // PLAYSCENE_H
