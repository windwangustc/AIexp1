//
// Created by Chen Wang on 2022/4/18.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <queue>
#include <time.h>

using namespace std;
#define ENABLE_DEBUG 1

#define JUMP_POS1_I 0
#define JUMP_POS1_J 2
#define JUMP_POS2_I 4
#define JUMP_POS2_J 2
#define JUMP_POS3_I 2
#define JUMP_POS3_J 0
#define JUMP_POS4_I 2
#define JUMP_POS4_J 4

/*A_h1 A_h2 IDA_h2 4个函数，分别代表A* 和 迭代A* 及2种启发函数*/
void A_h1(const vector<vector<int> > &start, const vector<vector<int> > &target);
void A_h2(const vector<vector<int> > &start, const vector<vector<int> > &target);
void IDA_h1(const vector<vector<int> > &start, const vector<vector<int> >&target);
void IDA_h2(const vector<vector<int> > &start, const vector<vector<int> > &target);

int CountMisplacedStars(const vector<vector<int>> &sourceMatrix, const vector<vector<int>> &targetMatrix);
void Print_Path(struct SearchStates *goal);
vector<vector<int>> ReadFile(const char* FileName);

enum Actions{U,D,L,R};      //四种操作
int State_Trans(const vector<vector<int> > old_state, vector<vector<int>> &new_state,Actions action);


//描述当前状态信息的结构体
struct SearchStates{
    int cost;       //cost=g+h
    int depth;      //当前走的步数，也就是g
    int action;
    struct SearchStates* previousState;     //指向上一个状态
    vector<vector<int>> stateMatrix;

    //重载<运算符，用于优先队列，cost小的优先
    bool operator < (const SearchStates &r) const{
        return this->cost > r.cost;
    }
    SearchStates(int c, int d,int a,struct SearchStates* p, vector<vector<int>> m): cost(c), depth(d), action(a), previousState(p), stateMatrix(m) {}
};
//用于A*的优先队列
priority_queue<SearchStates> StatesQueue;

int main (int argc,char* argv []){
    //读取源、目标文件中的矩阵
    vector<vector<int>> sourceMatrix = ReadFile("../data/input02.txt");
    vector<vector<int>> targetMatrix = ReadFile("../data/target02.txt");
    cout<<"Misplaced Stars = "<<CountMisplacedStars(sourceMatrix,targetMatrix)<<endl;
    A_h1(sourceMatrix,targetMatrix);


}

/****************************************************************************/
vector<vector<int>> ReadFile(const char* FileName)
/***
 * @Description 读取input.txt内表示的矩阵
 * @param FileName
 * @return 返回一个input.txt内的矩阵，本实验中为5x5的矩阵
 */
{
    vector<vector<int>> readMatrix{};
    int col = 5;            //本实验为5x5矩阵，限定col=5
    int count = 0;
    string tmp;
    ifstream fileStream;
    fileStream.open(FileName, ios::in);
    if (fileStream.fail()) {
        throw logic_error("Read File Failed");
    }else{
        //读取一行
        while (getline(fileStream, tmp, '\n')){
            vector<int> tmpV{};
            istringstream is(tmp);          //分割后推入vector
            for(int i=0; i < col; i++){
                string str_tmp;
                is>>str_tmp;
                tmpV.push_back(stoi(str_tmp));
            }
            readMatrix.push_back(tmpV);
            count++;
        }
        fileStream.close();
    }
    return readMatrix;
}

/****************************************************************************/
int CountMisplacedStars(const vector<vector<int>> &sourceMatrix, const vector<vector<int>> &targetMatrix)
/***
 * @Description 比较错位的星球数
 * @param sourceMatrix
 * @param targetMatrix
 * @return 错位的星球数量
 */
{
    int count=0;
    // 遍历比较不同的位置数即可
    for(int i=0; i < sourceMatrix.size(); i++){
        for (int j = 0; j < sourceMatrix[0].size(); ++j) {
            if(sourceMatrix[i][j] != targetMatrix[i][j]){
                count ++;
            }
        }
    }
    return count;
}

/****************************************************************************/
void A_h1(const vector<vector<int> > &start, const vector<vector<int> > &target)
/***
 * @Description A*搜索，启发式函数为错位的星球数
 * @param start
 * @param target
 */
{
    Actions four_actions[4] = {U,D,L,R};
    int f = 0 + CountMisplacedStars(start,target);   //f = g + h

    SearchStates min_state(f,0,L, nullptr,start);
    SearchStates nextState(f, 0, L, nullptr, start);
    StatesQueue.push(min_state);
    int steps = 0;
    //tree search
    do{
        steps++;
        SearchStates* currentBest = nullptr;
        currentBest = (SearchStates*)malloc(sizeof(struct SearchStates));
        if(currentBest == nullptr){
            throw logic_error("Malloc Failed");
        }
        //获得当前最优
        *currentBest = StatesQueue.top();
        StatesQueue.pop();

        if (CountMisplacedStars(currentBest->stateMatrix, target) == 0){
            Print_Path(currentBest);
            return;
        }

        for(int k=0;k<4;k++){
            if(State_Trans(currentBest->stateMatrix, nextState.stateMatrix, four_actions[k]) == 1){
                f = currentBest->depth + 1 + CountMisplacedStars(nextState.stateMatrix, target);
                nextState.cost = f;
                nextState.depth = currentBest->depth + 1;
                nextState.action = four_actions[k];
                nextState.previousState = currentBest;
                StatesQueue.push(nextState);
                //cout << "Action: " << four_actions[k] << " Score: " << f << " Depth: " << nextState.depth << "\n" << endl;
            }
        }
    }while(!StatesQueue.empty());
}

// helper: stateMatrix transition. returns 1 when stateMatrix is actually changed, 0 when no change happens
int State_Trans(const vector<vector<int> > old_state, vector<vector<int>> &new_state,Actions action){
    new_state = old_state;
    int i_des=-1;int j_des=-1;
    int flag=0;

    // find where the ship is
    int i_pos=-1;int j_pos=-1;
    for(int i=0;i<old_state.size();i++){
        for (int j = 0; j < old_state[0].size(); ++j) {
            if(old_state[i][j] == 0){
                i_pos = i;
                j_pos = j;
            }
        }
    }

    // stateMatrix transition, note that unavailable place(black hole, edge) should be considered when selecting child node
    if(action!=L && action!=R && action!=U && action!=D){
        cout << "Not a legal action" << endl;
    }
        // we will calculate destination first(consider edge, then consider jump), then confirm whether destination is a black hole.
        // On the edge
        // these are illegal moves when on the edge
    else if(action==L && (j_pos==0&&i_pos!=2)){;}
    else if(action==R && (j_pos==4&&i_pos!=2)){;}
    else if(action==U && (i_pos==0&&j_pos!=2)){;}
    else if(action==D && (i_pos==4&&j_pos!=2)){;}

        // these are jump cases
    else if(i_pos==JUMP_POS1_I&&j_pos==JUMP_POS1_J&&action==U){
        i_des = JUMP_POS2_I;
        j_des = JUMP_POS2_J;
    }
    else if(i_pos==JUMP_POS2_I&&j_pos==JUMP_POS2_J&&action==D){
        i_des = JUMP_POS1_I;
        j_des = JUMP_POS1_J;
    }
    else if(i_pos==JUMP_POS3_I&&j_pos==JUMP_POS3_J&&action==L){
        i_des = JUMP_POS4_I;
        j_des = JUMP_POS4_J;
    }
    else if(i_pos==JUMP_POS4_I&&j_pos==JUMP_POS4_J&&action==R){
        i_des = JUMP_POS3_I;
        j_des = JUMP_POS3_J;
    }
        // normal case
    else{
        switch(action){
            case L:
                i_des = i_pos;
                j_des = j_pos-1;
                break;
            case R:
                i_des = i_pos;
                j_des = j_pos+1;
                break;
            case U:
                i_des = i_pos-1;
                j_des = j_pos;
                break;
            case D:
                i_des = i_pos+1;
                j_des = j_pos;
                break;
            default:
                break;
        }
    }

    // i_des, j_des calculated, check whether it is a black hole
    if(i_des<0){
        flag=0;
    }
    else if(old_state[i_des][j_des]<0){
        flag=0;
    }
    else{
        flag = 1;
        //switch des and pos
        //new_state[i_des][j_des] = 0;
        new_state[i_des][j_des] = old_state[i_pos][j_pos];
        new_state[i_pos][j_pos] = old_state[i_des][j_des];
    }
    return flag;
}

//helper: print the path
void Print_Path(struct SearchStates *goal){
    if(goal->previousState== nullptr){
        return;
    }
    Print_Path(goal->previousState);
    switch(goal->action){
        case L:
            cout << "L";
            break;
        case R:
            cout << "R";
            break;
        case U:
            cout << "U";
            break;
        case D:
            cout << "D";
            break;
    }
    if(goal->cost - goal->depth==0){
        cout << endl;
    }
    //递归free之前malloc的空间
    free(goal);
}