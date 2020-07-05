#include "show.h"
#include "qpainter.h"
#include <QMouseEvent>
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include "function/judgemodel.h"
#include "function/chesser.h"

Show* Show::self;

Show *Show::Instance()        //instance译为例子
{
    if (self == nullptr) {
        static QMutex mutex;
        QMutexLocker locker(&mutex);    //创建互斥锁,出作用域时自动解锁销毁
        if (self == nullptr) {
            self = new Show();
        }
    }

    return self;
}

void Show::setConnInfo(vChess* inchess)
{
    this->LocalvChess = inchess;
    //std::cout<<LocalvChess<<"\n";
}

Show::Show(QWidget *parent) : QMainWindow(parent)
{
    // 设置棋盘大小,开启鼠标hover功能
    setFixedSize(APP::kBoardMargin * 2 + APP::kBlockSize * (APP::kBoardSizeNum-1),
                 APP::kBoardMargin * 2 + APP::kBlockSize * (APP::kBoardSizeNum-1));
    setMouseTracking(true);

    this->addMenu();

    this->show();

}

Show::~Show()
{
    qcout<<"窗口关闭";
    if(self != nullptr)
        self = nullptr;
}

void Show::addMenu()
{
    //双人对战
    QMenu *gameMenu = menuBar()->addMenu(tr("Game")); // menuBar默认是存在的，直接加菜单就可以了
    QAction *actionPVP = new QAction("双人对战", this);
    connect(actionPVP, &QAction::triggered,
            [=](){
                    if(APP::WorkModle == 0)
                        this->restart();

                    qcout<<"双人大战";
                    APP::WorkModle = 1;
                });
    gameMenu->addAction(actionPVP);

    //人机对战
    QAction *actionPVE = new QAction("人机对战", this);
    connect(actionPVE, &QAction::triggered,
            [=](){
                    APP::WorkModle = 0;

                    //确定谁先走
                    QMessageBox::StandardButton btnValue = QMessageBox::information(this, "先手确认", " 是否同意机器先走?"
                                                                                    ,QMessageBox::Yes, QMessageBox::No);

                    if (btnValue == QMessageBox::Yes){
                        APP::AIColor = -1;
                        this->restart();
                    }else {
                        APP::AIColor = 1;
                        this->restart();
                    }

                    qcout<<"人机对战";

                });
    gameMenu->addAction(actionPVE);

    //机器对战
    QAction *actionEVE = new QAction("机器对战", this);
    connect(actionEVE, &QAction::triggered,
            [=](){
                    qcout<<"机器大战";
                    APP::WorkModle = -1;
                    this->restart();
                });
    gameMenu->addAction(actionEVE);

    //重开
    QAction *actionRes = new QAction("重开", this);
    connect(actionRes, &QAction::triggered,
            [=](){
                    qcout<<"棋盘重置";
                    this->restart();
                });
    gameMenu->addAction(actionRes);

    //悔棋
    QAction *actionBefore = new QAction("悔棋", this);
    connect(actionBefore, &QAction::triggered,
            [=](){
                    qcout<<"悔棋";
                });
    gameMenu->addAction(actionBefore);

}

void Show::start()
{
    qcout<<LocalvChess->at(0).at(0);
    qcout<<"show model start";
    update();
}

void Show::paintEvent(QPaintEvent *event)           //耗费资源事件
{
    QWidget::paintEvent(event);
    QPainter painter(this);
   // 绘制棋盘网格
   painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿

   for (int i = 0; i < APP::kBoardSizeNum; i++)
   {
       painter.drawLine(APP::kBoardMargin + APP::kBlockSize * i, APP::kBoardMargin, APP::kBoardMargin + APP::kBlockSize * i,
                        size().height() - APP::kBoardMargin);
       painter.drawLine(APP::kBoardMargin, APP::kBoardMargin + APP::kBlockSize * i, size().width() - APP::kBoardMargin,
                        APP::kBoardMargin + APP::kBlockSize * i);
   }

    // 绘制落子标记
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    if (clickPosRow >= 0 && clickPosRow < APP::kBoardSizeNum)
    {
       if (/*game->playerFlag*/1)    //判断当前状态
           brush.setColor(Qt::white);
       else
           brush.setColor(Qt::black);
       painter.setBrush(brush);
       painter.drawRect(APP::kBoardMargin + APP::kBlockSize * clickPosCol - APP::kMarkSize / 2,
                        APP::kBoardMargin + APP::kBlockSize * clickPosRow - APP::kMarkSize / 2, APP::kMarkSize, APP::kMarkSize);
    }

   //绘制棋子
    for(int i = 0; i < APP::gameMapVec.size();i++)
    {
        for(int j = 0;j<APP::gameMapVec[i].size();j++)
        {
            if(APP::gameMapVec[i][j] == 1)
            {
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(APP::kBoardMargin + APP::kBlockSize * j - APP::kRadius, APP::kBoardMargin
                                    + APP::kBlockSize * i - APP::kRadius, APP::kRadius * 2, APP::kRadius * 2);

            }else if(APP::gameMapVec[i][j] == -1)
            {
                brush.setColor(Qt::black);
                painter.setBrush(brush);
                painter.drawEllipse(APP::kBoardMargin + APP::kBlockSize * j - APP::kRadius, APP::kBoardMargin
                                    + APP::kBlockSize * i - APP::kRadius, APP::kRadius * 2, APP::kRadius * 2);
            }
        }
    }

    painter.end();
    APP::Show_waite = false;
}

void Show::mouseMoveEvent(QMouseEvent *event)
{
    // 通过鼠标的hover确定落子的标记
    int x = event->x();
    int y = event->y();

    // 对鼠标落定范围进行限制
    if (x >=  APP::kBoardMargin -  APP::kBlockSize / 2 &&
        x <= size().width() -  APP::kBoardMargin + APP::kBlockSize / 2 &&
        y >=  APP::kBoardMargin -  APP::kBlockSize / 2 &&
        y <= size().height()-  APP::kBoardMargin + APP::kBlockSize / 2)
    {
        // 获取最近的左上角的点
        int col = (x - APP::kBoardMargin) /  APP::kBlockSize;
        int row = (y - APP::kBoardMargin) /  APP::kBlockSize;

        int leftTopPosX =  APP::kBoardMargin +  APP::kBlockSize * col;
        int leftTopPosY =  APP::kBoardMargin +  APP::kBlockSize * row;

        // 根据距离算出合适的点击位置,一共四个点，根据半径距离选最近的
        int clickPosRow = -1; // 初始化最终的值
        int clickPosCol = -1;
        int len = 0; // 计算完后取整就可以了

        // 确定一个误差在范围内的点，且只可能确定一个出来
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len <  APP::kPosDelta)
        {
            clickPosRow = row;
            clickPosCol = col;
        }
        len = sqrt((x - leftTopPosX -  APP::kBlockSize) * (x - leftTopPosX -  APP::kBlockSize) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len <  APP::kPosDelta)
        {
            clickPosRow = row;
            clickPosCol = col + 1;
        }
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY -  APP::kBlockSize) * (y - leftTopPosY -  APP::kBlockSize));
        if (len <  APP::kPosDelta)
        {
            clickPosRow = row + 1;
            clickPosCol = col;
        }
        len = sqrt((x - leftTopPosX -  APP::kBlockSize) * (x - leftTopPosX -  APP::kBlockSize) +
                   (y - leftTopPosY -  APP::kBlockSize) * (y - leftTopPosY -  APP::kBlockSize));
        if (len <  APP::kPosDelta)
        {
            clickPosRow = row + 1;
            clickPosCol = col + 1;
        }

        if(this->clickPosRow != clickPosRow || this->clickPosCol != clickPosCol)
        {
            this->clickPosRow = clickPosRow;
            this->clickPosCol = clickPosCol;
            update();
        }
    }

}

void Show::mouseReleaseEvent(QMouseEvent *event)
{
    if (clickPosRow>=0 && clickPosCol>=0 && APP::WorkModle != -1)
    {
        if(APP::WorkModle != 0 || JudgeModel::Instance()->NextColour() != APP::AIColor){
            emit actionByPerson(clickPosRow, clickPosCol);
            qcout << QString("(%1,%2)").arg(clickPosCol).arg(clickPosRow);
        }
    }
}

void Show::closeEvent(QCloseEvent *event)
{
    qcout<<"窗口关闭";
    Chesser::Instance()->stop();
}

void Show::UpdateShow()
{
    update();
}

void Show::restart()
{
    APP::initchess();

    //机器先走往中间首子靠
    if((APP::WorkModle == 0 && APP::AIColor == -1)||APP::WorkModle == -1){
        emit actionByPerson(7, 7);
    }

    update();
}

void Show::GameOver(int index)
{
    QString str,comparestr;
    if (index == 1){
        winwhite++;
        str = "white player";
    }
    else if (index == -1){
        winblack++;
        str = "black player";
    }
    else if (index == 0){
        winno++;
        str = "no player";
    }

    //描述总的场次胜利
    comparestr = QString("黑子赢:%1场，白字赢:%2场,和棋:%3场").arg(winblack).arg(winwhite).arg(winno);
    qcout<<comparestr;

    if(winblack>100 || winwhite>100 || winno>100){

        QMessageBox::StandardButton btnValue = QMessageBox::information(this, "congratulations", str + " win!\nDo you want restart?\n"+comparestr
                                                                        ,QMessageBox::Yes/*, QMessageBox::No*/);

        // 重置游戏状态，否则容易死循环
        if (btnValue == QMessageBox::Yes)
        {
            winblack = 0;
            winwhite = 0;
            winno=0;
            restart();
        }
    }else {

        restart();
    }

}

void Show::actionByshow(int row ,int col)
{
    emit actionByPerson(row, col);
}
