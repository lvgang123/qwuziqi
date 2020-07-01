#include "app.h"

int APP::WorkModle = 1;

int APP::kBoardSizeNum = 15;
int APP::kBoardMargin = 50;
int APP::kRadius = 15;
int APP::kMarkSize = 6;
int APP::kBlockSize = 40;
int APP::kPosDelta = 20;
int APP::kAIDelay = 100;


vChess APP::gameMapVec;


void APP::initchess()
{
    // 初始棋盘
    gameMapVec.clear();
    for (int i = 0; i < kBoardSizeNum; i++)
    {
        std::vector<int> lineBoard;
        for (int j = 0; j < kBoardSizeNum; j++)
            lineBoard.push_back(0);
        gameMapVec.push_back(lineBoard);
    }
}
