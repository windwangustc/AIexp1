//
// Created by Chen Wang on 2022/4/18.
//
#ifndef EXP1_DIGITAL_H
#define EXP1_DIGITAL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <ctime>
#include <utility>
#include <algorithm>

#endif //EXP1_DIGITAL_H

using namespace std;
#define ENABLE_DEBUG 0
#define SUCCESS 1
#define FAILED 0

enum Actions{U,D,L,R};      //四种操作
struct Coordinate {
    int x;
    int y;
};
Coordinate g_targetCoordinates[26]; //棋盘坐标

//描述当前状态信息的结构体
struct SearchStates{
    int cost;       //cost=g+h
    int depth;      //当前走的步数，也就是g
    int action;     //记录当前状态是通过哪种状态到达的，回溯路径时需要
    struct SearchStates* previousState;     //指向上一个状态，回溯路径时需要
    vector<vector<int>> stateMatrix;        //当前的棋盘矩阵

    //重载<运算符，用于优先队列，cost小的优先
    bool operator < (const SearchStates &r) const{
        return this->cost > r.cost;
    }
    //构造函数
    SearchStates(int c, int d,int a,struct SearchStates* p, vector<vector<int>> m): cost(c), depth(d), action(a), previousState(p), stateMatrix(std::move(m)) {}
};
SearchStates *g_goalState;
//存储malloc的全局指针，用于运行结束后释放
vector<SearchStates*>g_HeapStorage;

/*A_h1 A_h2 IDA_h2 4个函数，分别代表A* 和 迭代A* 及2种启发函数*/
void A_h1(const vector<vector<int> > &start, const vector<vector<int> > &target);
void A_h2(const vector<vector<int> > &start, const vector<vector<int> > &target);
void IDA_h1(const vector<vector<int> > &start, const vector<vector<int> >&target);
void IDA_h2(const vector<vector<int> > &start, const vector<vector<int> > &target);

vector<vector<int>> ReadFile(const string& FileName);
/*启发式函数h1 = CountMisplacedStars */
int CountMisplacedStars(const vector<vector<int>> &sourceMatrix, const vector<vector<int>> &targetMatrix);
int h2(const vector<vector<int>> &sourceMatrix, const vector<vector<int>> &targetMatrix);
int ChangeStates(const vector<vector<int>>& old_state, vector<vector<int>> &new_state, Actions action);
void SaveCoordinates(const vector<vector<int>> &targetMatrix);
int ManhattanDistance(Coordinate A,Coordinate B);
void PrintPath(struct SearchStates *goalState);
void WriteFile(ofstream &fileStream,struct SearchStates *goalState);
