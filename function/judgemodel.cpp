#include "judgemodel.h"

QScopedPointer<JudgeModel> JudgeModel::self;  //调用QScopedPointer智能指针格式

JudgeModel *JudgeModel::Instance()        //instance译为例子  创建实例
{
    if (self.isNull()) {
        static QMutex mutex;
        QMutexLocker locker(&mutex);    //创建互斥锁,出作用域时自动解锁销毁
        if (self.isNull()) {
            self.reset(new JudgeModel);    //将self指针指向new AppInit
        }
    }

    return self.data();
}

JudgeModel::JudgeModel(QObject *parent) : QObject(parent)
{

}

void JudgeModel::start()
{
}

void JudgeModel::setConnInfo(vChess* inchess)
{
    LcoalvChess = inchess;
}

bool JudgeModel::isWin(int row ,int col)
{
    // 横竖斜四种大情况，每种情况都根据当前落子往后遍历5个棋子，有一种符合就算赢
   // 水平方向
   for (int i = 0; i < 5; i++)
   {
       // 往左5个，往右匹配4个子，20种情况
       if (col - i >= 0 &&
           col - i + 4 < LcoalvChess->size() &&
           (*LcoalvChess)[row][col - i] == (*LcoalvChess)[row][col - i + 1] &&
           (*LcoalvChess)[row][col - i] == (*LcoalvChess)[row][col - i + 2] &&
           (*LcoalvChess)[row][col - i] == (*LcoalvChess)[row][col - i + 3] &&
           (*LcoalvChess)[row][col - i] == (*LcoalvChess)[row][col - i + 4])
           return true;
   }

   // 竖直方向(上下延伸4个)
   for (int i = 0; i < 5; i++)
   {
       if (row - i >= 0 &&
           row - i + 4 <  LcoalvChess->size() &&
           (*LcoalvChess)[row - i][col] == (*LcoalvChess)[row - i + 1][col] &&
           (*LcoalvChess)[row - i][col] == (*LcoalvChess)[row - i + 2][col] &&
           (*LcoalvChess)[row - i][col] == (*LcoalvChess)[row - i + 3][col] &&
           (*LcoalvChess)[row - i][col] == (*LcoalvChess)[row - i + 4][col])
           return true;
   }

   // 左斜方向
   for (int i = 0; i < 5; i++)
   {
       if (row + i <  LcoalvChess->size() &&
           row + i - 4 >= 0 &&
           col - i >= 0 &&
           col - i + 4 <  LcoalvChess->size() &&
           (*LcoalvChess)[row + i][col - i] == (*LcoalvChess)[row + i - 1][col - i + 1] &&
           (*LcoalvChess)[row + i][col - i] == (*LcoalvChess)[row + i - 2][col - i + 2] &&
           (*LcoalvChess)[row + i][col - i] == (*LcoalvChess)[row + i - 3][col - i + 3] &&
           (*LcoalvChess)[row + i][col - i] == (*LcoalvChess)[row + i - 4][col - i + 4])
           return true;
   }

   // 右斜方向
   for (int i = 0; i < 5; i++)
   {
       if (row - i >= 0 &&
           row - i + 4 <  LcoalvChess->size() &&
           col - i >= 0 &&
           col - i + 4 <  LcoalvChess->size() &&
           (*LcoalvChess)[row - i][col - i] == (*LcoalvChess)[row - i + 1][col - i + 1] &&
           (*LcoalvChess)[row - i][col - i] == (*LcoalvChess)[row - i + 2][col - i + 2] &&
           (*LcoalvChess)[row - i][col - i] == (*LcoalvChess)[row - i + 3][col - i + 3] &&
           (*LcoalvChess)[row - i][col - i] == (*LcoalvChess)[row - i + 4][col - i + 4])
           return true;
   }

   return false;
}

bool JudgeModel::isDeadGame()
{
    // 出现空格为
    for (int i = 0; i < LcoalvChess->size(); i++)
        for (int j = 0; j < LcoalvChess->size(); j++)
        {
            if ((*LcoalvChess)[i][j] == 0)
                return false;
        }

    return true;
}

int JudgeModel::NextColour()
{
    //遍历棋盘找到两种颜色棋子进行记录
    int black_piece = 0;
    int white_piece = 0;

    for(int i = 0; i < LcoalvChess->size();i++){
        for(int k = 0; k < (*LcoalvChess)[i].size(); k++){
            if((*LcoalvChess)[i][k] == -1)
                black_piece++;
            if((*LcoalvChess)[i][k] == 1)
                white_piece++;
        }
    }

    if(black_piece>white_piece)
        return 1;
    else
        return -1;
}
