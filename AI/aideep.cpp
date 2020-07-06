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
    this->initScoreVec();
    vChess tranchess = copyvChess(calchess);
    int cal_count = 0;              //推演计算深度记录

    scoreMapVec = AICore::Instance()->calculateScore(tranchess,calColor);
    cal_count++;
    vector<CPoint> vPoints = Select_max(scoreMapVec,tranchess);

//    for(int i=0;i<vPoints.size();i++){
//        cout<<"first"<<vPoints[i].x<<"-"<<vPoints[i].y<<"-"<<vPoints[i].score<<"\n";
//    }
//    debuge_vchess(scoreMapVec);

    //判断首次循环是否结束
//    if(vPoints.at(0).score>9999)
//        return vPoints[0];
    //深度较低退出
    if(deep<2){
        return Select_Point(vPoints);
    }

    //二次推演
    for(int i=0;i<vPoints.size()&&i<5;i++){
        this->initScoreVec();
        vector<CPoint> vPoints2;
        vChess tranchess = copyvChess(calchess);
        tranchess[vPoints.at(i).y][vPoints.at(i).x] = calColor;
        scoreMapVec  = AICore::Instance()->calculateScore(tranchess,-calColor,1);
        //debuge_vchess(scoreMapVec);
        cal_count++;
        vPoints2 = Select_max(scoreMapVec,tranchess);

        if(vPoints2.size()>0){
            //if(vPoints2[0].score>9999)
                vPoints[i].score =  vPoints[i].score - vPoints2[0].score;
        }
    }

//    for(int i=0;i<vPoints.size();i++){
//        cout<<"two"<<vPoints[i].x<<"-"<<vPoints[i].y<<"-"<<vPoints[i].score<<"\n";
//    }

    //筛选出分值较大点
    CPoint maxPoint = Select_Point(vPoints);
    //cout<<"result"<<maxPoint.x<<"- "<<maxPoint.y<<"- "<<maxPoint.score<<"\n";
    return Select_Point(vPoints);

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
    //对输入分值进行插入排序
    vector<CPoint> sortPoints;
    CPoint firstp;
    firstp.x = 0;
    firstp.y = 0;
    firstp.score = -100000;
    sortPoints.insert(sortPoints.begin(),firstp);
    for (int row = 0; row < LocalLength; row++)
        for (int col = 0; col < LocalLength; col++)
        {
            if (nowchess[row][col] != 0)    //保证得到点位为空
            {
                continue;
            }

            CPoint tranp;
            tranp.x = col;
            tranp.y = row;
            tranp.score = calchess[row][col];

            //比较插入
            int old_count = sortPoints.size();
            for(int i=0;i<old_count;i++){
                if(tranp.score>sortPoints.at(i).score){
                    sortPoints.insert(sortPoints.begin()+i,tranp);
                    break;
                }
            }
        }
    sortPoints.pop_back();

    vector<CPoint> maxPoints;
    // 从评分中找出最大分数的位置
    for(int i=0;i<sortPoints.size();i++){
        if(sortPoints[i].score==sortPoints[0].score || maxPoints.size()<4)
            maxPoints.push_back(sortPoints[i]);
    }
/*
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
*/

    return maxPoints;
}

CPoint AIdeep::Select_Point(vector<CPoint> vPoints)
{
    // 从评分中找出最大分数的位置
    int maxScore = vPoints[0].score;
    vector<CPoint> maxPoints;

    for(int i=0;i<vPoints.size();i++){
        CPoint tranp;
        tranp.x = vPoints[i].x;
        tranp.y = vPoints[i].y;
        tranp.score = vPoints[i].score;
        if(vPoints[i].score>maxScore){
            maxPoints.clear();
            maxScore = vPoints[i].score;
            maxPoints.push_back(tranp);
        }else if(vPoints[i].score==maxScore){
            maxPoints.push_back(tranp);
        }
    }

    // 随机落子，如果有多个点的话
    srand((unsigned)time(0));
    int index = rand() % maxPoints.size();
    CPoint pointPair = maxPoints.at(index);
    return pointPair;
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

