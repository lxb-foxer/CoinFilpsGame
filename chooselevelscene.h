#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

    PlayScene * pScene = NULL;

signals:

    //自定义信号，点击了返回按钮
    void chooselevelBack ();

};

#endif // CHOOSELEVELSCENE_H
