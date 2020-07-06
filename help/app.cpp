#include "app.h"

int APP::WorkModle = 1;
int APP::AIColor = -1;

int APP::kBoardSizeNum = 15;
int APP::kBoardMargin = 50;
int APP::kRadius = 15;
int APP::kMarkSize = 6;
int APP::kBlockSize = 40;
int APP::kPosDelta = 20;
int APP::kAIDelay = 100;

bool APP::Show_waite = false;
int APP::deepA = 5;
int APP::deepB = 5;
LChess APP::scoreA;
LChess APP::scoreB;

vChess APP::gameMapVec;


void APP::initchess()
{
    // 初始棋盘
    gameMapVec.clear();
    for (int i = 0; i < kBoardSizeNum; i++)
    {
        LChess lineBoard;
        for (int j = 0; j < kBoardSizeNum; j++)
            lineBoard.push_back(0);
        gameMapVec.push_back(lineBoard);
    }
}

void APP::initScore()
{
    scoreA.clear();
    scoreA.push_back(7);
    scoreA.push_back(50);
    scoreA.push_back(110);
    scoreA.push_back(140);
    scoreA.push_back(10000);
    scoreA.push_back(10000);
    scoreA.push_back(30000);
    scoreA.push_back(50000);
    scoreA.push_back(0);
    scoreA.push_back(0);
    scoreA.push_back(8);
    scoreA.push_back(60);
    scoreA.push_back(130);
    scoreA.push_back(150);
    scoreA.push_back(20000);
    scoreA.push_back(20000);
    scoreA.push_back(40000);
    scoreA.push_back(100000);
    scoreA.push_back(0);
    scoreA.push_back(0);

    scoreB.clear();
    scoreB.push_back(7);
    scoreB.push_back(50);
    scoreB.push_back(110);
    scoreB.push_back(140);
    scoreB.push_back(10000);
    scoreB.push_back(10000);
    scoreB.push_back(30000);
    scoreB.push_back(50000);
    scoreB.push_back(0);
    scoreB.push_back(0);
    scoreB.push_back(8);
    scoreB.push_back(60);
    scoreB.push_back(130);
    scoreB.push_back(150);
    scoreB.push_back(20000);
    scoreB.push_back(20000);
    scoreB.push_back(40000);
    scoreB.push_back(100000);
    scoreB.push_back(0);
    scoreB.push_back(0);
}
