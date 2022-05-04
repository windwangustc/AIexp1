/***
 * Author:Chen Wang PE20060014
 * Last Modified Date:2022.5.4
 * Problem Description:
 车间1:有7名工人
 工人1:senior 工人2:senior 工人3:junior 工人4:junior 工人5:junior 工人6:junior 工人7:junior
 1. 每个工人每周必须休息2天或2天以上
 2. 每个工人每周不可以连续休息3天(不考虑跨周情况)
 3. 周六周天也需要有人值班，即一周7天每天都要安排工人值班
 4. 由于车间规模较大，需要每天安排至少 4 个人值班
 5. 每天至少要有一名级别为 senior 的工人值班
 其中工人1和工人4，工人2和工人 3，工人3和工人6不想在同一天工作。

 车间2:有10名工人
 工人1:senior 工人2:senior 工人3:junior 工人4:junior 工人5:junior 工人6:junior 工人7:junior 工人8:senior 工人9:junior 工人10:senior
 1. 每个工人每周必须休息2天或2天以上
 2. 每个工人每周不可以连续休息3天(不考虑跨周情况)
 3. 周六周天也需要有人值班，即一周7天每天都要安排工人值班
 4. 由于车间规模较大，需要每天安排至少 5 个人值班
 5. 每天至少要有一名级别为 senior 的工人值班
 其中工人1和工人5，工人2和工人 6，工人8和工人10不想在同一天工作。
 */
#include <iostream>
#include <array>
#include <iomanip>
#include <fstream>
#include <ctime>
using namespace std;
#define Work 1
#define NotWork 0

#define Senior 1
#define Junior 0

#define MAXW_NUM1 7
#define MAXW_NUM2 10
namespace CSProblem1 {

//工人结构体
    struct Workers {
        int ID;             //序号
        int Title;          //Senior or Junior
        //构造函数
        Workers(int id, int title) : ID(id), Title(title) {}
    };

    array<array<int, MAXW_NUM1>, MAXW_NUM1> g_workSchedule = {};     //全局工作表，g_workSchedule[i][j]=1 表示工人i在周(j+1)上班
    array<array<int, MAXW_NUM1>, MAXW_NUM1> g_conflictsTable = {};   //全局工人冲突表 g_conflictsTable[i][j] = g_conflictsTable[j][i] = 1 表示冲突

//打印工作表
    void printArray(const array<array<int, MAXW_NUM1>, MAXW_NUM1> a) {
        cout << "      ";
        for (int i = 0; i < 7; i++) {
            cout << setw(8) << "周" << i + 1 << " ";
        }
        cout << endl;
        for (int i = 0; i < MAXW_NUM1; i++) {
            cout << setw(8) << "工人" << i+1 << ":";
            for (auto x: a[i])
                cout << setw(8) << x;
            cout << endl;
        }
    }

//Constraint 1 , 工人在星期 Day 前是否已经工作了5天以上
    bool isTooManyWorkDays(int workerID, int day) {
        int sum = 0;
        for (int i = 0; i <= day; i++) {
            sum += g_workSchedule[workerID][i];
        }
        return sum > 5;
    }

//Constraint 2 , 工人在星期 Day 前是否已经连续休息了3天
    bool isTooManyRestDays(int workerID, int day) {
        //也就是最大连续0的个数
        int max0 = 0;//存放最大连续串的个数
        int zero = 0;//0的计数器
        for (int i = 0; i <= day; i++) {
            if (g_workSchedule[workerID][i] == 0) {
                zero++;
                if (zero > max0) max0 = zero;//将连续0串的最大值存放在变量max0中
            }
            if (g_workSchedule[workerID][i] == 1) {
                if (zero > max0) max0 = zero;
                zero = 0;//将0的将计数器清0
            }
        }
        return max0 >= 3;  //休息3天及以上 返回true
    }

// Constraint 3,4 , 在day当天是否有4人及以上上班
    bool isEnoughWorkers(int workerID, int day) {
        int sum = 0;
        for (int i = 0; i <= workerID; ++i)
            if (g_workSchedule[i][day] == Work)
                sum++;
        if (sum + MAXW_NUM1 - workerID - 1 < 4)    // 该天不足4人工作，由于是按顺序安排工人的，在workerID之后的工人，暂时也算做已上班
            return false;                        // 工人不足
        return true;
    }

// Constraint 5 , 每天都需要有senior工人值班
    bool isSeniorAbsent(int day) {
        if (g_workSchedule[0][day] == NotWork && g_workSchedule[1][day] == NotWork)
            return true;            //没有Senior值班
        else
            return false;
    }

// Constraint 6 , 是否有冲突工人，有冲突返回1
    bool isConflictExists(int workerID, int day) {
        if (g_workSchedule[workerID][day] == NotWork)
            return false;   // workerID没上班
        else {
            for (int i = 0; i < workerID; i++)         //查找冲突表
                if (g_workSchedule[i][day] == Work && g_conflictsTable[i][workerID] == 1)
                    return true;
            return false;
        }
    }

//检查上述所有约束
    bool isAllConstraintsSatisfied(int workerID, int day) {
        if (isTooManyWorkDays(workerID, day) || isTooManyRestDays(workerID, day) || !isEnoughWorkers(workerID, day) ||
            isSeniorAbsent(day) || isConflictExists(workerID, day))
            return false;
        else
            return true;
    }

    int RecursiveSearch(int workerID, int day) {
        //递归出口，排到周日结束
        if (day >= 7) {
            printArray(g_workSchedule);
            return 1;
        }
        //棋盘涂色，每个坐标 只有 work or not 两种颜色
        for (auto i = NotWork; i <= Work; i++) {
            g_workSchedule[workerID][day] = i;
            //检查约束
            if (isAllConstraintsSatisfied(workerID, day)) {
                //所有约束满足， 安排下一个工人或者下一天
                int result = 0;
                workerID == MAXW_NUM1 - 1 ? result = RecursiveSearch(0, day + 1) : result = RecursiveSearch(workerID + 1,
                                                                                                           day);
                if (result == 1)
                    return result;   //如果能找到解返回1
            }
            //否则进入下一个循环， 也就是 remove var from assignment
        }
        return 0;
    }
}
namespace CSProblem2 {
//工人结构体
    struct Workers {
        int ID;             //序号
        int Title;          //Senior or Junior
        //构造函数
        Workers(int id, int title) : ID(id), Title(title) {}
    };

    array<array<int, 7>, MAXW_NUM2> g_workSchedule = {};     //全局工作表，g_workSchedule[i][j]=1 表示工人i在周(j+1)上班
    array<array<int, MAXW_NUM2>, MAXW_NUM2> g_conflictsTable = {};   //全局工人冲突表 g_conflictsTable[i][j] = g_conflictsTable[j][i] = 1 表示冲突

//打印工作表
    void printArray(const array<array<int, 7>, MAXW_NUM2> a) {
        cout << "      ";
        for (int i = 0; i < 7; i++) {
            cout << setw(8) << "周" << i + 1 << " ";
        }
        cout << endl;
        for (int i = 0; i < MAXW_NUM2; i++) {
            cout << setw(8) << "工人" << i + 1 << ":";
            for (auto x: a[i])
                cout << setw(8) << x;
            cout << endl;
        }
    }

//Constraint 1 , 工人在星期 Day 前是否已经工作了5天以上
    bool isTooManyWorkDays(int workerID, int day) {
        int sum = 0;
        for (int i = 0; i <= day; i++) {
            sum += g_workSchedule[workerID][i];
        }
        return sum > 5;
    }

//Constraint 2 , 工人在星期 Day 前是否已经连续休息了3天
    bool isTooManyRestDays(int workerID, int day) {
        //也就是最大连续0的个数
        int max0 = 0;//存放最大连续串的个数
        int zero = 0;//0的计数器
        for (int i = 0; i <= day; i++) {
            if (g_workSchedule[workerID][i] == 0) {
                zero++;
                if (zero > max0) max0 = zero;//将连续0串的最大值存放在变量max0中
            }
            if (g_workSchedule[workerID][i] == 1) {
                if (zero > max0) max0 = zero;
                zero = 0;//将0的将计数器清0
            }
        }
        return max0 >= 3;  //休息3天及以上 返回true
    }

// Constraint 3,4 , 在day当天是否有5人及以上上班
    bool isEnoughWorkers(int workerID, int day) {
        int sum = 0;
        for (int i = 0; i <= workerID; ++i)
            if (g_workSchedule[i][day] == Work)
                sum++;
        if (sum + MAXW_NUM2 - workerID - 1 < 5)    // 该天不足5人工作，由于是按顺序安排工人的，在workerID之后的工人，暂时也算做已上班
            return false;                        // 工人不足
        return true;
    }

// Constraint 5 , 每天都需要有senior工人值班
    bool isSeniorAbsent(int day) {
        //if(g_workSchedule[0][day] == NotWork && g_workSchedule[1][day] == NotWork)
        if (g_workSchedule[0][day] == NotWork && g_workSchedule[1][day] == NotWork &&
            g_workSchedule[7][day] == NotWork && g_workSchedule[9][day] == NotWork)
            return true;            //没有Senior值班
        else
            return false;
    }

// Constraint 6 , 是否有冲突工人，有冲突返回1
    bool isConflictExists(int workerID, int day) {
        if (g_workSchedule[workerID][day] == NotWork)
            return false;   // workerID没上班
        else {
            for (int i = 0; i < workerID; i++)         //查找冲突表
                if (g_workSchedule[i][day] == Work && g_conflictsTable[i][workerID] == 1)
                    return true;
            return false;
        }
    }

//检查上述所有约束
    bool isAllConstraintsSatisfied(int workerID, int day) {
        if (isTooManyWorkDays(workerID, day) || isTooManyRestDays(workerID, day) || !isEnoughWorkers(workerID, day) ||
            isSeniorAbsent(day) || isConflictExists(workerID, day))
            return false;
        else
            return true;
    }

    int RecursiveSearch(int workerID, int day) {
        //递归出口，排到周日结束
        if (day >= 7) {
            printArray(g_workSchedule);
            return 1;
        }
        //棋盘涂色，每个坐标 只有 work or not 两种颜色
        for (auto i = NotWork; i <= Work; i++) {
            g_workSchedule[workerID][day] = i;
            //检查约束
            if (isAllConstraintsSatisfied(workerID, day)) {
                //所有约束满足， 安排下一个工人或者下一天
                int result = 0;
                workerID == MAXW_NUM2 - 1 ? result = RecursiveSearch(0, day + 1) : result = RecursiveSearch(workerID + 1,
                                                                                                           day);
                if (result == 1)
                    return result;   //如果能找到解返回1
            }
            //否则进入下一个循环， 也就是 remove var from assignment
        }
        return 0;
    }
}

int main(){
    //写入CSP1 conflict的工人
    CSProblem1::g_conflictsTable[0][3] = CSProblem1::g_conflictsTable[3][0] = 1;
    CSProblem1::g_conflictsTable[1][2] = CSProblem1::g_conflictsTable[2][1] = 1;
    CSProblem1::g_conflictsTable[2][5] = CSProblem1::g_conflictsTable[5][2] = 1;
    //Workers workers[MAXW_NUM] ={{0,Senior},{1,Senior},{2,Junior},{3,Junior},{4,Junior},{5,Junior},{6,Junior}};
    //递归搜索
    clock_t start1,end1;
    start1 = clock();
    if(CSProblem1::RecursiveSearch(0,0)){
        end1 = clock();
        cout <<" 运行时间： "<<double(end1-start1)/CLOCKS_PER_SEC<<endl;
        ofstream output1;
        output1.open("../output/output1.txt", ios::out | ios::trunc );  //删除写
        if(!output1.is_open()){
            throw logic_error("open output_A_h1.txt Failed!");
        }
        for(int i = 0; i<7;i++){
            for(int j = 0; j<7; j++){
                if(CSProblem1::g_workSchedule[j][i] == Work)
                    output1 << j+1 << " ";
            }
            output1<<endl;
        }
        output1.close();
        cout<< "CSP问题1有解。计算CSP问题2......"<<endl;
    }else{
        cout<< "CSP问题1无解。计算CSP问题2......"<<endl;
    }

    //写入CSP2 conflict的工人
    CSProblem2::g_conflictsTable[0][4] =  CSProblem2::g_conflictsTable[4][0] = 1;
    CSProblem2::g_conflictsTable[1][5] =  CSProblem2::g_conflictsTable[5][1] = 1;
    CSProblem2::g_conflictsTable[7][9] =  CSProblem2::g_conflictsTable[9][7] = 1;
    clock_t start2,end2;
    start2 = clock();
    //递归搜索
    if(CSProblem2::RecursiveSearch(0,0)){
        end2 = clock();
        cout <<" 运行时间： "<<double(end2-start2)/CLOCKS_PER_SEC<<endl;
        ofstream output2;
        output2.open("../output/output2.txt", ios::out | ios::trunc );  //删除写
        if(!output2.is_open()){
            throw logic_error("open output_A_h1.txt Failed!");
        }
        for(int i = 0; i<7;i++){
            for(int j = 0; j<10; j++){
                if(CSProblem2::g_workSchedule[j][i] == Work)
                    output2 << j+1 << " ";
            }
            output2<<endl;
        }
        output2.close();
        cout<< "CSP问题2有解。程序正常结束。"<<endl;
    }else{
        cout<< "CSP问题2无解。程序正常结束。"<<endl;
    }

    return 0;
}