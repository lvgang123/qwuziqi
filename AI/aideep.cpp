#include "aideep.h"


unique_ptr<AIdeep> AIdeep::self;

AIdeep *AIdeep::Instance()        //instance译为例子  创建实例
{
    if (self == NULL) {
        mutex mutex;
        mutex.lock();
        if (self == NULL) {
            self.reset(new AIdeep);    //将self指针指向new AppInit
        }
        mutex.unlock();
    }

    return self.get();
}

AIdeep::AIdeep()
{
}


AIdeep::~AIdeep()
{
}

void AIdeep::start()
{

}

void AIdeep::setConnInfo(int length)
{
    this->LocalLength = length;
}

CPoint AIdeep::Get_deepRsult(vChess calchess,int deep,int calColor)
{
    mutex mutex;
    mutex.lock();
    this->initScoreVec();
    vChess tranchess = copyvChess(calchess);
    int cal_count = 0;              //推演计算深度记录

    scoreMapVec = AICore::Instance()->calculateScore(tranchess,calColor);
    cal_count++;
    vector<CPoint> vPoints = Select_max(scoreMapVec,tranchess);

//    for(int i=0;i<vPoints.size();i++){
//        cout<<"first"<<vPoints[i].x<<"-"<<vPoints[i].y<<"-"<<vPoints[i].score<<"\n";
//    }


    //判断首次循环是否结束
    if(vPoints.at(0).score>9999)
        return vPoints[0];
    //深度较低退出
    if(deep<2){
        // 随机落子，如果有多个点的话
        srand((unsigned)time(0));
        int index = rand() % vPoints.size();
        CPoint pointPair = vPoints.at(index);
        return pointPair;
    }

    //二次推演
    for(int i=0;i<vPoints.size()&&i<5;i++){
        this->initScoreVec();
        vector<CPoint> vPoints2;
        vChess tranchess = copyvChess(calchess);
        tranchess[vPoints.at(i).y][vPoints.at(i).x] = calColor;
        scoreMapVec  = AICore::Instance()->calculateScore(tranchess,-calColor);
        //debuge_vchess(scoreMapVec);
        cal_count++;
        vPoints2 = Select_max(scoreMapVec,tranchess);
//        for(int k=0;k<vPoints2.size();k++){
//            cout<<"hhhh"<<vPoints2[k].x<<"-"<<vPoints2[k].y<<"-"<<vPoints2[k].score<<"\n";
//        }
        int test =vPoints[i].score;
        int test1 =  vPoints2[0].score;
       vPoints[i].score =  test - test1;
    }

//    for(int i=0;i<vPoints.size();i++){
//        cout<<"two"<<vPoints[i].x<<"-"<<vPoints[i].y<<"-"<<vPoints[i].score<<"\n";
//    }
    mutex.unlock();
    //筛选出分值较大点
    CPoint maxPoint;
    maxPoint.score = vPoints[0].score;
    maxPoint.x = vPoints[0].x;
    maxPoint.y = vPoints[0].y;
    for(int i=0;i<vPoints.size();i++){
        if(maxPoint.score<vPoints.at(i).score){
            maxPoint.x = vPoints[i].x;
            maxPoint.y = vPoints[i].y;
            maxPoint.score = vPoints[i].score;
        }
    }
    //cout<<"result"<<maxPoint.x<<"-"<<maxPoint.y<<"-"<<maxPoint.score<<"\n";
    return maxPoint;

//    for(int i=1;(i < deep) && (i < empty_cout(calchess));i++){

//    }
}

void AIdeep::initScoreVec()
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

int AIdeep::empty_cout(vChess calchess)
{
    int get_count=0;
    for(int i=0;i<LocalLength;i++)
        for(int k=0;k<LocalLength;k++)
        {
            if(calchess[i][k]==0)
                get_count++;
        }

    return get_count;
}

vector<CPoint> AIdeep::Select_max(vChess calchess,vChess nowchess)
{
    // 从评分中找出最大分数的位置
    int maxScore = 0;
    vector<CPoint> maxPoints;

    for (int row = 0; row < LocalLength; row++)
        for (int col = 0; col < LocalLength; col++)
        {
            CPoint tranp;
            tranp.x = col;
            tranp.y = row;
            tranp.score = calchess[row][col];
            // 前提是这个坐标是空的
            if (nowchess[row][col] == 0)
            {
                if (calchess[row][col] > maxScore)          // 找最大的数和坐标
                {
                    maxPoints.clear();
                    maxScore = calchess[row][col];
                    maxPoints.push_back(tranp);
                }
                else if (calchess[row][col] == maxScore)     // 如果有多个最大的数，都存起来
                    maxPoints.push_back(tranp);
            }
        }

    // 随机落子，如果有多个点的话
//    srand((unsigned)time(0));
//    int index = rand() % maxPoints.size();

//    CPoint pointPair = maxPoints.at(index);
    return maxPoints;
}

vChess AIdeep::copyvChess(vChess invchess)
{
    vChess outvchess;
    for(int i=0;i<invchess.size();i++){
        LChess tranchess;
        for(int k=0;k<invchess[i].size();k++){
            tranchess.push_back(invchess[i][k]);
        }
        outvchess.push_back(tranchess);
    }
    return outvchess;
}

void AIdeep::debuge_vchess(vChess outMapVec)
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

