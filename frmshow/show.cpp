#include "show.h"
#include "qpainter.h"
#include <QMouseEvent>
#include <QMessageBox>

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
    this->LcoalvChess = inchess;
    std::cout<<LcoalvChess<<"\n";
}

Show::Show(QWidget *parent) : QMainWindow(parent)
{
    // 设置棋盘大小
    setFixedSize(APP::kBoardMargin * 2 + APP::kBlockSize * APP::kBoardSizeNum, APP::kBoardMargin * 2 + APP::kBlockSize * APP::kBoardSizeNum);

    // 开启鼠标hover功能，这两句一般要设置window的
    setMouseTracking(true);

    this->show();

}

Show::~Show()
{
    if(self != nullptr)
        self = nullptr;
}

void Show::start()
{
    qcout<<"show model start";
    update();
}

void Show::paintEvent(QPaintEvent *event)
{
    qcout<<&APP::gameMapVec;
    QPainter painter(this);
   // 绘制棋盘网格
   painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿

   for (int i = 0; i < APP::kBoardSizeNum + 1; i++)
   {
       painter.drawLine(APP::kBoardMargin + APP::kBlockSize * i, APP::kBoardMargin, APP::kBoardMargin + APP::kBlockSize * i,
                        size().height() - APP::kBoardMargin);
       painter.drawLine(APP::kBoardMargin, APP::kBoardMargin + APP::kBlockSize * i, size().width() - APP::kBoardMargin,
                        APP::kBoardMargin + APP::kBlockSize * i);
   }


    // 绘制落子标记
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    if (clickPosRow > 0 && clickPosRow < APP::kBoardSizeNum)
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

   //发送判断信号

}

void Show::mouseMoveEvent(QMouseEvent *event)
{
    // 通过鼠标的hover确定落子的标记
    int x = event->x();
    int y = event->y();

    // 棋盘边缘不能落子
    if (x >=  APP::kBoardMargin +  APP::kBlockSize / 2 &&
            x < size().width() -  APP::kBoardMargin &&
            y >=  APP::kBoardMargin +  APP::kBlockSize / 2 &&
            y < size().height()-  APP::kBoardMargin)
    {
        // 获取最近的左上角的点
        int col = x /  APP::kBlockSize;
        int row = y /  APP::kBlockSize;

        int leftTopPosX =  APP::kBoardMargin +  APP::kBlockSize * col;
        int leftTopPosY =  APP::kBoardMargin +  APP::kBlockSize * row;

        // 根据距离算出合适的点击位置,一共四个点，根据半径距离选最近的
        clickPosRow = -1; // 初始化最终的值
        clickPosCol = -1;
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
    }

    // 存了坐标后也要重绘
    update();
}


void Show::mouseReleaseEvent(QMouseEvent *event)
{
    if (/*game_type != BOT || game->playerFlag*/1)
    {
        emit actionByPerson(clickPosRow, clickPosCol);

    }
}
