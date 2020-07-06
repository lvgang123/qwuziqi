#include "aicore.h"

unique_ptr<AICore> AICore::self;

AICore *AICore::Instance()        //instance译为例子  创建实例
{
    if (self == NULL) {
        mutex mutex;
        mutex.lock();
        if (self == NULL) {
            self.reset(new AICore);    //将self指针指向new AppInit
        }
        mutex.unlock();
    }

    return self.get();
}

AICore::AICore()
{
}


AICore::~AICore()
{
}

void AICore::start()
{

}

void AICore::setConnInfo(int length)
{
    this->LocalLength = length;
}

void AICore::initScoreVec()
{
    scoreMapVec.clear();
    for (int i = 0; i < LocalLength; i++)
    {
        LChess lineScores;
        for (int j = 0; j < LocalLength; j++)
            lineScores.push_back(0);
        scoreMapVec.push_back(lineScores);
    }
}

void AICore::setScore(LChess scores)
{
    Localscore.clear();
    for(int i=0;i<scores.size();i++){
        Localscore.push_back(scores[i]);
    }
}

vChess AICore::calculateScore(vChess calchess,int calCorlor,int index)
{
    // 清空评分数组
    initScoreVec();
    this->LocalAICorlor = calCorlor;

    // 计分（此处是完全遍历，其实可以用bfs或者dfs加减枝降低复杂度，通过调整权重值，调整AI智能程度以及攻守风格）
    for (int row = 0; row < LocalLength; row++)
        for (int col = 0; col < LocalLength; col++)
        {
            //已有棋子点跳过
            if(calchess[row][col] != 0)
                continue;

            //得到中间转换容器
            vChess tranMapVec;
            this->GetTran(row,col,tranMapVec,calchess);

            //对容器进行整合
            vChess killMapVec,makeMapVec;
            this->DealTran(tranMapVec,killMapVec,makeMapVec);
            //对容器进行评分判定,评分包括杀2-5  成1-5
            scoreMapVec[row][col] += CalculateTran(killMapVec,makeMapVec,index);
        }

    return scoreMapVec;
}

void AICore::GetTran(int row,int col,vChess &tranMapVec,vChess calchess)
{

    // 遍历周围八个方向，并将结果存入容器
    for (int y = -1; y <= 1; y++)
        for (int x = -1; x <= 1; x++)
        {
            //去掉多余分支，减少计算量
            if((x+y)<0 || (x == 1 && y==-1))
                continue;

            int personNum = 0; // 玩家连成子的个数
            int botNum = 0; // AI连成子的个数
            int emptyNum = 0; // 各方向空白位的个数

            // 原坐标不算
            if (y == 0 && x == 0){
                continue;
            }

            LChess onetran;
            //每个方向延伸四个子，对AI进行评分,10-越界 2-判断位
            for (int i = -4; i <= 4; i++)
            {
                //超限位跳过
                if(row+i*y<0 || row+i*y>=LocalLength || col+i*x<0 || col+i*x>=LocalLength){
                    onetran.push_back(10);
                    continue;
                }

                if(i==0){
                    onetran.push_back(2);
                    continue;
                }

                onetran.push_back(calchess[row+i*y][col+i*x]);
            }
            tranMapVec.push_back(onetran);
        }
}

void AICore::DealTran(vChess tranMapVec,vChess &killMapVec,vChess &makeMapVec)
{
    killMapVec.clear();
    makeMapVec.clear();
    //对容器进行整合,kill为遇到LocalAICorlor，10的时候断点
    for(int i=0;i<tranMapVec.size();i++){
        int left_index_kill = 0;
        int right_index_kill = 8;
        int left_index_make = 0;
        int right_index_make = 8;
        for(int m=1;m<5;m++){
            //kill左侧定位
            if(left_index_kill == 0){
                if(tranMapVec[i][4-m] == 10 || tranMapVec[i][4-m] == LocalAICorlor){
                    left_index_kill = 4-m+1;
                }
            }

            //kill右侧定位
            if(right_index_kill == 8){
                if(tranMapVec[i][4+m] == 10 || tranMapVec[i][4+m] == LocalAICorlor){
                    right_index_kill = 4+m-1;
                }
            }

            //make左侧定位
            if(left_index_make == 0){
                if(tranMapVec[i][4-m] == 10 || tranMapVec[i][4-m] == -LocalAICorlor){
                    left_index_make = 4-m+1;
                }
            }

            //make右侧定位
            if(right_index_make == 8){
                if(tranMapVec[i][4+m] == 10 || tranMapVec[i][4+m] == -LocalAICorlor){
                    right_index_make = 4+m-1;
                }
            }
        }

        //kill开始整合
        LChess onekill;
        for(int n=left_index_kill;n<=right_index_kill;n++){
            onekill.push_back(tranMapVec[i][n]);
        }
        killMapVec.push_back(onekill);

        //make开始整合
        LChess onemake;
        for(int n=left_index_make;n<=right_index_make;n++){
            onemake.push_back(tranMapVec[i][n]);
        }
        makeMapVec.push_back(onemake);
    }
}

int AICore::CalculateTran(vChess killMapVec,vChess makeMapVec,int index)
{
    int score = 0;
    //对杀2-5评分,防守
    for(int i=0;i<killMapVec.size() && index<=0;i++){
        //杀2
        score += Localscore.at(0) * linejudge(killMapVec[i],2,true,-LocalAICorlor);
        //杀3，双活三为必杀
        if(linejudge(killMapVec[i],3,true,-LocalAICorlor)>3)
            score += Localscore.at(4) ;
        else if(linejudge(killMapVec[i],3,true,-LocalAICorlor)>0)
            score += Localscore.at(3) * linejudge(killMapVec[i],3,true,-LocalAICorlor);
        else
            score += Localscore.at(1) * linejudge(killMapVec[i],3,false,-LocalAICorlor);
        //杀4，活四为必杀，单四加活三同样必杀
        if(linejudge(killMapVec[i],4,true,-LocalAICorlor)>0)
            score += Localscore.at(6) ;
        else if(linejudge(killMapVec[i],3,true,-LocalAICorlor)>0 && linejudge(killMapVec[i],4,false,-LocalAICorlor)>0)
            score += Localscore.at(5) ;
        else
            score += Localscore.at(2) * linejudge(killMapVec[i],4,false,-LocalAICorlor);
        //杀5，必杀
        if(linejudge(killMapVec[i],5,false,-LocalAICorlor)>0)
            score += Localscore.at(7);
    }

    //对成1-5评分
    for(int i=0;i<makeMapVec.size() && index>=0;i++){
        //成2
        score += Localscore.at(10) * linejudge(makeMapVec[i],2,true,LocalAICorlor);
        //成3，双活三为必成
        if(linejudge(makeMapVec[i],3,true,LocalAICorlor)>3)
            score += Localscore.at(14) ;
        else if(linejudge(makeMapVec[i],3,true,LocalAICorlor)>0)
            score += Localscore.at(13) * linejudge(makeMapVec[i],3,true,LocalAICorlor);
        else
            score += Localscore.at(11) * linejudge(makeMapVec[i],3,false,LocalAICorlor);
        //成4，活四为必成，单四加活三同样必成
        if(linejudge(makeMapVec[i],4,true,LocalAICorlor)>0)
            score += Localscore.at(16) ;
        else if(linejudge(makeMapVec[i],3,true,LocalAICorlor)>0 && linejudge(makeMapVec[i],4,false,LocalAICorlor)>0)
            score += Localscore.at(15) ;
        else
            score += Localscore.at(12) * linejudge(makeMapVec[i],4,false,LocalAICorlor);
        //成5，必成
        if(linejudge(makeMapVec[i],5,false,LocalAICorlor)>0)
            score += Localscore.at(17) * linejudge(makeMapVec[i],5,false,LocalAICorlor);
    }
    return score;
}

int AICore::linejudge(LChess onekill,int level,bool active,int judge_it)
{
    int out_count = 0;
    //当判断片段小于五直接返回0
    if(onekill.size() < 5)
        return 0;

    for(int k=0;k<onekill.size();k++){
        int person_count = 0;
        bool judge_mark = false;     //判断判断位是否包含
        for(int m=0;m<5 && (m+k)<onekill.size();m++){
            if(active){
                //活三判断
                if(level == 3){
                    if((k+4)>=onekill.size())
                        break;
                    if(onekill[k] != 0 || onekill[k+4] != 0)
                        break;
                }
                //活四判断
                if(level == 4){
                    if((k+5)>=onekill.size())
                        break;
                    if(onekill[k] != 0 || onekill[k+5] != 0)
                        break;
                }

            }
            if(onekill[k+m] == judge_it || onekill[k+m] == 2)
                person_count++;
            if(onekill[k+m] == 2)
                judge_mark = true;
        }

        if(person_count == level && judge_mark)
            out_count++;
    }

    return out_count;
}

void AICore::debuge_vchess(vChess outMapVec)
{
    for(int i=0;i<outMapVec.size();i++)
    {
        for(int k=0;k<outMapVec[i].size();k++)
        {
            int out_int = outMapVec[i][k];
            cout<<out_int;
            if(out_int == 0)
                out_int++;
            for(int i=5;i>=0;i--){
                if((int)(out_int/pow(10,i)) != 0)
                    break;
                cout<<" ";
            }
            cout<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n\n";
}

