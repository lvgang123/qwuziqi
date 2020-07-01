#include "aido.h"
#include "mutex"

unique_ptr<AIDO> AIDO::self;

AIDO *AIDO::Instance()        //instance译为例子  创建实例
{
    if (self == NULL) {
        mutex mutex;
        mutex.lock();
        if (self == NULL) {
            self.reset(new AIDO);    //将self指针指向new AppInit
        }
        mutex.unlock();
    }

    return self.get();
}

AIDO::AIDO()
{
}


AIDO::~AIDO()
{
}

void AIDO::start()
{

}

void AIDO::setConnInfo(vChess* inchess)
{
    LcoalvChess = inchess;
}

void AIDO::initScoreVec()
{
    scoreMapVec.clear();
    for (int i = 0; i < LcoalvChess->size(); i++)
    {
        std::vector<int> lineScores;
        for (int j = 0; j < LcoalvChess->size(); j++)
            lineScores.push_back(0);
        scoreMapVec.push_back(lineScores);
    }
}

void AIDO::actionByAI(int &row,int &col)
{

}

void AIDO::calculateScore()
{
    // 清空评分数组
    initScoreVec();

    // 计分（此处是完全遍历，其实可以用bfs或者dfs加减枝降低复杂度，通过调整权重值，调整AI智能程度以及攻守风格）
    for (int row = 0; row < LcoalvChess->size(); row++)
        for (int col = 0; col < LcoalvChess->size(); col++)
        {
            //已有棋子点跳过
            if((* LcoalvChess)[row][col] != 0)
                continue;

            // 遍历周围八个方向
            for (int y = -1; y <= 1; y++)
                for (int x = -1; x <= 1; x++)
                {
                    int personNum = 0; // 玩家连成子的个数
                    int botNum = 0; // AI连成子的个数
                    int emptyNum = 0; // 各方向空白位的个数

                    // 原坐标不算
                    if (y == 0 && x == 0){
                        continue;
                    }



                }
        }
}

