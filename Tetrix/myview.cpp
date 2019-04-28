#include "myview.h"
#include "mybox.h"
#include <QIcon>
#include <QObject>
//#include <QGraphicsScene>

static const qreal INITSPEED = 500;


MyView::MyView(QWidget *parent):QGraphicsView (parent)
{
    initView();
}

void MyView::startGame()
{
    initGame();
}

void MyView::clearFullRows()
{
    for(int y=429;y>50;y -= 20){
        QList<QGraphicsItem *>list=scene()->items(QRectF(199,y,202,2),Qt::ContainsItemShape);
        if(list.count() == 10){
            foreach(QGraphicsItem *item,list){
                OneBox *box = (OneBox *)item;
                box->deleteLater();
            }
            rows << y;
        }
    }
    if(rows.count() >0){
        moveBox();
    }else{
        boxGroup->createBox(QPointF(300,70),nextBoxGroup->getCurrentShape());
        nextBoxGroup->clearBoxGroup(true);
        nextBoxGroup->createBox(QPointF(500,70));
    }
}

void MyView::moveBox()
{
    for(int i = rows.count();i>0;--i){
        int row = rows.at(i-1);
        foreach(QGraphicsItem *item,scene()->items(QRectF(199,49,202,row-47),
                                                   Qt::ContainsItemShape)){
            item->moveBy(0,20);
        }
    }
    updateScore(rows.count());
    rows.clear();
    boxGroup->createBox(QPointF(300,70),nextBoxGroup->getCurrentShape());
    nextBoxGroup->clearBoxGroup(true);
    nextBoxGroup->createBox(QPointF(500,70));
}

void MyView::gameOver()
{

}

void MyView::initView()
{
    setRenderHint(QPainter::Antialiasing);
    setCacheMode(CacheBackground);
    setWindowTitle(tr("MyBox方块游戏"));
    setWindowIcon(QIcon(":/images/icon.png"));
    setMinimumSize(810,510);
    setMaximumSize(810,510);

    QGraphicsScene *scene = new QGraphicsScene;
    scene->setSceneRect(5,5,800,500);
    setScene(scene);
    topLine = scene->addLine(197,47,403,47);
    bottomLine = scene->addLine(197,453,403,453);
    leftLine = scene->addLine(197,47,197,453);
    rightLine = scene->addLine(403,47,403,453);
    boxGroup = new BoxGroup;
   // QObject::connect(boxGroup,SIGNAL(needNewBox()),this,SLOT(clearFullRows()));
    connect(boxGroup,SIGNAL(gameFinished()),this,SLOT(gameOver()));
    scene->addItem(boxGroup);
    nextBoxGroup  = new BoxGroup;
    scene->addItem(nextBoxGroup);

    startGame();

}

void MyView::initGame()
{
    boxGroup->createBox(QPointF(300,70));
   // boxGroup->setFocus();
    boxGroup->startTimer(INITSPEED);
    gameSpeed = INITSPEED;
    nextBoxGroup->createBox(QPointF(500,70));
}

void MyView::updateScore(const int fullRowNum)
{

}
