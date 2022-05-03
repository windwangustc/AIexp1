/***
 * Author:Chen Wang PE20060014
 * Last Modified Date:2022.5.4
 * Problem Description:
 车间1:有7名工人
 工人0:senior 工人1:senior 工人2:junior 工人3:junior 工人4:junior 工人5:junior 工人6:junior
 1. 每个工人每周必须休息2天或2天以上
 2. 每个工人每周不可以连续休息3天(不考虑跨周情况)
 3. 周六周天也需要有人值班，即一周7天每天都要安排工人值班
 4. 由于车间规模较大，需要每天安排至少 4 个人值班
 5. 每天至少要有一名级别为 senior 的工人值班
 其中工人0和工人3，工人1和工人2，工人2和工人5不想在同一天工作。
 */
#include <iostream>
#include <array>
#include <iomanip>

#define MAXW_NUM 7
#define Work 1
#define NotWork 0

#define Senior 1
#define Junior 0

using namespace std;
//工人结构体
struct Workers{
    int ID;             //序号
    int Title;          //Senior or Junior
    //构造函数
    Workers(int id,int title):ID(id),Title(title){}
};

array<array<int,MAXW_NUM>,MAXW_NUM>  g_workSchedule ={};     //全局工作表，g_workSchedule[i][j]=1 表示工人i在周(j+1)上班
array<array<int,MAXW_NUM>,MAXW_NUM>  g_conflictsTable ={};   //全局工人冲突表 g_conflictsTable[i][j] = g_conflictsTable[j][i] = 1 表示冲突

//打印工作表
void printArray(const array<array<int,MAXW_NUM>,MAXW_NUM> a){
    cout <<"      ";
    for (int i = 0 ;i<7;i++){
        cout <<setw(8)<<"周" << i+1 << " ";
    }
    cout<<endl;
    for (int i = 0 ;i<MAXW_NUM;i++){
        cout<<setw(8)<<"工人" << i << ":";
        for(auto x : a[i])
            cout <<setw(8) <<x ;
        cout<<endl;
    }
}

//Constraint 1 , 工人在星期 Day 前是否已经工作了5天以上
bool isTooManyWorkDays(int workerID,int day){
    int sum=0;
    for(int i=0;i<=day;i++){
        sum+=g_workSchedule[workerID][i];
    }
    return sum > 5;
}

//Constraint 2 , 工人在星期 Day 前是否已经连续休息了3天
bool isTooManyRestDays(int workerID,int day){
    //也就是最大连续0的个数
    int max0=0;//存放最大连续串的个数
    int zero=0;//0的计数器
    for(int i=0;i<=day;i++){
        if(g_workSchedule[workerID][i] == 0){
            zero++;
            if(zero>max0) max0=zero;//将连续0串的最大值存放在变量max0中
        }
        if(g_workSchedule[workerID][i] == 1){
            if(zero>max0) max0=zero;
            zero=0;//将0的将计数器清0
        }
    }
    return max0 >= 3;  //休息3天及以上 返回true
}

// Constraint 3,4 , 在day当天是否有4人及以上上班
bool isEnoughWorkers (int workerID,int day){
    int sum = 0;
    for(int i = 0; i <= workerID ; ++i)
        if(g_workSchedule[i][day] == Work)
            sum++;
    if(sum + MAXW_NUM - workerID - 1 < 4)    // 该天不足4人工作，由于是按顺序安排工人的，在workerID之后的工人，暂时也算做已上班
        return false;                        // 工人不足
    return true;
}

// Constraint 5 , 每天都需要有senior工人值班
bool isSeniorAbsent(int day){
    if(g_workSchedule[0][day] == NotWork && g_workSchedule[1][day] == NotWork)
        return true;            //没有Senior值班
    else
        return false;
}

// Constraint 6 , 是否有冲突工人，有冲突返回1
bool isConflictExists(int workerID,int day){
    if(g_workSchedule[workerID][day] == NotWork)
        return false;   // workerID没上班
    else{
        for(int i = 0; i < workerID; i++)         //查找冲突表
            if(g_workSchedule[i][day] == Work && g_conflictsTable[i][workerID] == 1)
                return true;
        return false;
    }
}

//检查上述所有约束
bool isAllConstraintsSatisfied(int workerID,int day){
    if (isTooManyWorkDays(workerID,day) || isTooManyRestDays(workerID,day) || !isEnoughWorkers(workerID,day) || isSeniorAbsent(day) || isConflictExists(workerID,day))
        return false;
    else
        return true;
}

int RecursiveSearch(int workerID,int day){
    //递归出口，排到周日结束
    if(day >= 7 ){
        printArray(g_workSchedule);
        return 1;
    }
    for (auto i = NotWork; i<=Work ;i++){
        g_workSchedule[workerID][day] = i ;
        //检查约束
        if(isAllConstraintsSatisfied(workerID,day)){
            //所有约束满足， 安排下一个工人或者下一天
            int result = 0;
            workerID == MAXW_NUM - 1 ? result = RecursiveSearch (0,day+1) : result = RecursiveSearch(workerID+1,day);
            if(result==1)
                return result;   //如果能找到解返回1
        }
        //否则进入下一个循环， 也就是 remove var from assignment
    }
    return 0;
}

int main(){
    //写入conflict的工人
    g_conflictsTable[0][3] = g_conflictsTable[3][0] = 1;
    g_conflictsTable[1][2] = g_conflictsTable[2][1] = 1;
    g_conflictsTable[2][5] = g_conflictsTable[5][2] = 1;
    //Workers workers[MAXW_NUM] ={{0,Senior},{1,Senior},{2,Junior},{3,Junior},{4,Junior},{5,Junior},{6,Junior}};
    //递归搜索
    if(RecursiveSearch(0,0))
        cout<< "该 CSP 问题有解。程序正常结束。"<<endl;
}