//
// Created by Chen Wang on 2022/4/18.
//
#include "a.h"

int main (int argc,char* argv []){
//    if (argc != 4 ) {
//        throw logic_error("Incorrect Number of Argument!");
//    }
//    string arg1 =  argv[1];         //运行函数名 A_h1 A_h2 IDA_h2 其中之一
//    string arg2 =  argv[2];         //输入文件路径 input.txt
//    string arg3 =  argv[3];         //目标文件路径 target.txt
    string arg1="A_h2";
    string arg2="input06.txt";
    string arg3="target06.txt";
    arg2 = "../../data/" + arg2;
    arg3 = "../../data/" + arg3;

    if(arg1 == "A_h1"){
        ofstream output_A_h1;
        output_A_h1.open("../../digital/output/output_A_h1.txt", ios::out | ios::app ); //追加写
        if(!output_A_h1.is_open()){
            throw logic_error("open output_A_h1.txt Failed!");
        }
        cout <<"Computing "<<arg1<< " "<<arg2 <<" "<< arg3 <<endl;
        //读取源、目标文件中的矩阵
        vector<vector<int>> sourceMatrix = ReadFile(arg2);
        vector<vector<int>> targetMatrix = ReadFile(arg3);
        clock_t start,end;
        start = clock();
        A_h1(sourceMatrix,targetMatrix);
        end = clock();
        cout <<double(end-start)/CLOCKS_PER_SEC<<endl;
        WriteFile(output_A_h1,g_goalState);
        output_A_h1 <<double(end-start)/CLOCKS_PER_SEC<<endl;
        output_A_h1.close();

    } else if (arg1 == "A_h2"){
        ofstream output_A_h2;
        output_A_h2.open("../../digital/output/output_A_h2.txt", ios::out | ios::app ); //追加写
        if(!output_A_h2.is_open()){
            throw logic_error("open output_A_h2.txt Failed!");
        }
        cout <<"Computing "<<arg1<< " "<<arg2 <<" "<< arg3 <<endl;
        //读取源、目标文件中的矩阵
        vector<vector<int>> sourceMatrix = ReadFile(arg2);
        vector<vector<int>> targetMatrix = ReadFile(arg3);
        clock_t start,end;
        start = clock();
        A_h2(sourceMatrix,targetMatrix);
        end = clock();
        cout <<double(end-start)/CLOCKS_PER_SEC<<endl;
        WriteFile(output_A_h2,g_goalState);
        output_A_h2 <<double(end-start)/CLOCKS_PER_SEC<<endl;
        output_A_h2.close();
    } else if (arg1 == "IDA_h1"){
        ofstream output_IDA_h1;
        output_IDA_h1.open("../../digital/output/output_IDA_h1.txt", ios::out | ios::app ); //追加写
        if(!output_IDA_h1.is_open()){
            throw logic_error("open output_IDA_h1.txt Failed!");
        }
        cout <<"Computing "<<arg1<< " "<<arg2 <<" "<< arg3 <<endl;
        //读取源、目标文件中的矩阵
        vector<vector<int>> sourceMatrix = ReadFile(arg2);
        vector<vector<int>> targetMatrix = ReadFile(arg3);
        clock_t start,end;
        start = clock();
        A_h2(sourceMatrix,targetMatrix);
        end = clock();
        cout <<double(end-start)/CLOCKS_PER_SEC<<endl;
        WriteFile(output_IDA_h1,g_goalState);
        output_IDA_h1 <<double(end-start)/CLOCKS_PER_SEC<<endl;
        output_IDA_h1.close();
    } else if (arg1 == "IDA_h2"){
        ofstream output_IDA_h2;
        output_IDA_h2.open("../../digital/output/output_IDA_h2.txt", ios::out | ios::app ); //追加写
        if(!output_IDA_h2.is_open()){
            throw logic_error("open output_IDA_h2.txt Failed!");
        }
        cout <<"Computing "<<arg1<< " "<<arg2 <<" "<< arg3 <<endl;
        //读取源、目标文件中的矩阵
        vector<vector<int>> sourceMatrix = ReadFile(arg2);
        vector<vector<int>> targetMatrix = ReadFile(arg3);
        clock_t start,end;
        start = clock();
        A_h2(sourceMatrix,targetMatrix);
        end = clock();
        cout <<double(end-start)/CLOCKS_PER_SEC<<endl;
        WriteFile(output_IDA_h2,g_goalState);
        output_IDA_h2 <<double(end-start)/CLOCKS_PER_SEC<<endl;
        output_IDA_h2.close();
    }else{
        __throw_invalid_argument("Arguments must be one of A_h1 A_h2 IDA_h1 IDA_h2!");
    }
    cout<<"Normal End of Execution."<<endl;
    return 0;
}

/****************************************************************************/
vector<vector<int>> ReadFile(const string& FileName)
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
 * @Description 启发式函数h1 比较错位的星球数
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
int h2(const vector<vector<int>> &sourceMatrix, const vector<vector<int>> &targetMatrix)
/***
 * @Description 启发式函数h2
 *              h2 = 棋盘除黑洞外每个点的 min( M,T1,T2,T3,T4) 加和
 *              其中对于 source 的点 a 到 target 的点 b ，
 *              M = ManhattanDistance(a,b)
 *              Ti = ManhattanDistance(a，虫洞i) + ManhattanDistance(虫洞1,i)
 *              上述h2是最简单的松弛解，因此为可采纳的启发式函数
 * @param sourceMatrix
 * @param targetMatrix
 * @return 棋盘除黑洞外每个点的 min( M,T1,T2,T3,T4) 加和
 */
{
    int sum=0;
    Coordinate tunnel1={0,2};
    Coordinate tunnel2={2,0};
    Coordinate tunnel3={4,2};
    Coordinate tunnel4={2,4};
    Coordinate tmp_source;
    Coordinate tmp_target;

    for(int i=0;i<sourceMatrix.size();i++){
        for (int j = 0; j < sourceMatrix[0].size(); ++j){
            int srcVal = sourceMatrix[i][j];
            tmp_source.x = i;
            tmp_source.y = j;
            if (srcVal >= 0){
                tmp_target = g_targetCoordinates[srcVal];
                int M = ManhattanDistance(tmp_source,tmp_target);
                int T1 = 1+ManhattanDistance(tmp_source,tunnel1)+ ManhattanDistance(tunnel1,tmp_target);
                int T2 = 1+ManhattanDistance(tmp_source,tunnel2)+ ManhattanDistance(tunnel2,tmp_target);
                int T3 = 1+ManhattanDistance(tmp_source,tunnel3)+ ManhattanDistance(tunnel3,tmp_target);
                int T4 = 1+ManhattanDistance(tmp_source,tunnel4)+ ManhattanDistance(tunnel4,tmp_target);
                vector<int> tmpV;
                tmpV.push_back(M);
                tmpV.push_back(T1);
                tmpV.push_back(T2);
                tmpV.push_back(T3);
                tmpV.push_back(T4);
                //取最小距离
                sum += *min_element(tmpV.begin(),tmpV.end());
            }
        }
    }
    return sum;
}

/****************************************************************************/
void A_h1(const vector<vector<int> > &start, const vector<vector<int> > &target)
/***
 * @Description A*搜索，启发式函数为错位的星球数
 * @param start
 * @param target
 */
{
    //用于A*的优先队列
    priority_queue<SearchStates> StatesQueue;

    Actions four_actions[4] = {U,D,L,R};
    int f = 0 + CountMisplacedStars(start,target);   //f = g + h
    SearchStates firstState(f, 0, L, nullptr, start);
    SearchStates nextState(f, 0, L, nullptr, start);
    StatesQueue.push(firstState);
    //启发式函数为错位的星球数时，h(n) is admissible, using TREE-SEARCH
    //DFS-Search
    do{
        SearchStates* currentBest = nullptr;
        currentBest = (SearchStates*)malloc(sizeof(struct SearchStates));
        if(currentBest == nullptr){
            throw logic_error("Malloc Failed");
        }
        //获得当前最优
        *currentBest = StatesQueue.top();
        StatesQueue.pop();
        //错位星球数为零，找到了最优解
        if (CountMisplacedStars(currentBest->stateMatrix, target) == 0){
            g_goalState=currentBest;            //结果存入全局指针中用于打印结果
            PrintPath(currentBest);
            return;
        }
        //遍历检查UDLR四种操作是否合法，合法进队
        for(int k=0;k<4;k++){
            if(ChangeStates(currentBest->stateMatrix, nextState.stateMatrix, four_actions[k]) == SUCCESS){
                //更新耗散 f = g+h
                f = currentBest->depth + 1 + CountMisplacedStars(nextState.stateMatrix, target);
                nextState.cost = f;
                nextState.depth = currentBest->depth + 1;
                nextState.action = four_actions[k];
                nextState.previousState = currentBest;
                StatesQueue.push(nextState);
            }
        }
    }while(!StatesQueue.empty());
}

/****************************************************************************/
void A_h2(const vector<vector<int> > &start, const vector<vector<int> > &target)
/***
 * @Description A*搜索，启发式函数为h2
 * @param start
 * @param target
 */
{
    SaveCoordinates(target);
    //用于A*的优先队列
    priority_queue<SearchStates> StatesQueue;

    Actions four_actions[4] = {U,D,L,R};
    int f = 0 + h2(start,target);   //f = g + h
    SearchStates firstState(f, 0, L, nullptr, start);
    SearchStates nextState(f, 0, L, nullptr, start);
    StatesQueue.push(firstState);
    //启发式函数为错位的星球数时，h(n) is admissible, using TREE-SEARCH
    //DFS-Search
    do{
        SearchStates* currentBest = nullptr;
        currentBest = (SearchStates*)malloc(sizeof(struct SearchStates));
        if(currentBest == nullptr){
            throw logic_error("Malloc Failed");
        }
        //获得当前最优
        *currentBest = StatesQueue.top();
        StatesQueue.pop();
        //错位星球数为零，找到了最优解,h2也可用此函数判断
        if (CountMisplacedStars(currentBest->stateMatrix, target) == 0){
            g_goalState=currentBest;            //结果存入全局指针中用于打印结果
            PrintPath(currentBest);
            return;
        }
        //遍历检查UDLR四种操作是否合法，合法进队
        for(int k=0;k<4;k++){
            if(ChangeStates(currentBest->stateMatrix, nextState.stateMatrix, four_actions[k]) == SUCCESS){
                //更新耗散 f = g+h
                f = currentBest->depth + 1 + h2(nextState.stateMatrix, target);
                nextState.cost = f;
                nextState.depth = currentBest->depth + 1;
                nextState.action = four_actions[k];
                nextState.previousState = currentBest;
                StatesQueue.push(nextState);
            }
        }
    }while(!StatesQueue.empty());
}

/****************************************************************************/
void IDA_h1(const vector<vector<int> > &start, const vector<vector<int> >&target)
/***
 * @Description IDA*搜索，启发式函数为错位的星球数。
 * @param start
 * @param target
 */
{
    //用于A*的优先队列
    priority_queue<SearchStates> StatesQueue;
    Actions four_actions[4] = {U,D,L,R};
    int f = 0 + CountMisplacedStars(start,target);   //f = g + h

    int currentDepth = f;
    int nextDepth = f;       //nextDepth 为上一轮拓展的结点中 最大的f
    int maxDepth = 128;
    //外层do-while迭代加深
    do{
        currentDepth = nextDepth;
        //清空优先队列
        while(!StatesQueue.empty()){
            StatesQueue.pop();
        }

        SearchStates firstState(f, 0, L, nullptr, start);
        SearchStates nextState(f, 0, L, nullptr, start);
        StatesQueue.push(firstState);

        //内层do-while和A*基本相同，加入depth判断即可
        //启发式函数为错位的星球数时，h(n) is admissible, using TREE-SEARCH
        //DFS-Search
        do{
            SearchStates* currentBest = nullptr;
            currentBest = (SearchStates*)malloc(sizeof(struct SearchStates));
            if(currentBest == nullptr){
                throw logic_error("Malloc Failed");
            }
            //获得当前最优
            *currentBest = StatesQueue.top();
            StatesQueue.pop();
            //错位星球数为零，找到了最优解
            if (CountMisplacedStars(currentBest->stateMatrix, target) == 0){
                g_goalState=currentBest;            //结果存入全局指针中用于打印结果
                PrintPath(currentBest);
                return;
            }
            if(currentBest->depth < currentDepth) {
                //遍历检查UDLR四种操作是否合法，合法进队
                for(int k=0;k<4;k++){
                    if(ChangeStates(currentBest->stateMatrix, nextState.stateMatrix, four_actions[k]) == SUCCESS){
                        //更新耗散 f = g+h
                        f = currentBest->depth + 1 + CountMisplacedStars(nextState.stateMatrix, target);
                        nextState.cost = f;
                        nextState.depth = currentBest->depth + 1;
                        nextState.action = four_actions[k];
                        nextState.previousState = currentBest;
                        StatesQueue.push(nextState);
                        //更新下一轮的迭代深度
                        if(f > nextDepth){
                            nextDepth = f;
                        }
                    }
                }
            }else{
                //超出深度限制，不做拓展
                break;
            }
        }while(!StatesQueue.empty());
    }while(currentDepth < maxDepth);
}

/****************************************************************************/
void IDA_h2(const vector<vector<int> > &start, const vector<vector<int> >&target)
/***
 * @Description IDA*搜索，启发式函数为h2
 * @param start
 * @param target
 */
{
    SaveCoordinates(target);
    //用于A*的优先队列
    priority_queue<SearchStates> StatesQueue;
    Actions four_actions[4] = {U,D,L,R};
    int f = 0 + h2(start,target);   //f = g + h

    int currentDepth = f;
    int nextDepth = f;       //nextDepth 为上一轮拓展的结点中 最大的f
    int maxDepth = 128;
    //外层do-while迭代加深
    do{
        currentDepth = nextDepth;
        //清空优先队列
        while(!StatesQueue.empty()){
            StatesQueue.pop();
        }

        SearchStates firstState(f, 0, L, nullptr, start);
        SearchStates nextState(f, 0, L, nullptr, start);
        StatesQueue.push(firstState);

        //内层do-while和A*基本相同，加入depth判断即可
        //启发式函数为错位的星球数时，h(n) is admissible, using TREE-SEARCH
        //DFS-Search
        do{
            SearchStates* currentBest = nullptr;
            currentBest = (SearchStates*)malloc(sizeof(struct SearchStates));
            if(currentBest == nullptr){
                throw logic_error("Malloc Failed");
            }
            //获得当前最优
            *currentBest = StatesQueue.top();
            StatesQueue.pop();
            //错位星球数为零，找到了最优解
            if (CountMisplacedStars(currentBest->stateMatrix, target) == 0){
                g_goalState=currentBest;            //结果存入全局指针中用于打印结果
                PrintPath(currentBest);
                return;
            }
            if(currentBest->depth < currentDepth) {
                //遍历检查UDLR四种操作是否合法，合法进队
                for(int k=0;k<4;k++){
                    if(ChangeStates(currentBest->stateMatrix, nextState.stateMatrix, four_actions[k]) == SUCCESS){
                        //更新耗散 f = g+h
                        f = currentBest->depth + 1 + h2(nextState.stateMatrix, target);
                        nextState.cost = f;
                        nextState.depth = currentBest->depth + 1;
                        nextState.action = four_actions[k];
                        nextState.previousState = currentBest;
                        StatesQueue.push(nextState);
                        //更新下一轮的迭代深度
                        if(f > nextDepth){
                            nextDepth = f;
                        }
                    }
                }
            }else{
                //超出深度限制，不做拓展
                break;
            }
        }while(!StatesQueue.empty());
    }while(currentDepth < maxDepth);
}

/****************************************************************************/
int ChangeStates(const vector<vector<int> >& old_state, vector<vector<int>> &new_state, Actions action)
/***
 * @Description 由某次操作 action 后生成新棋盘
 * @param old_state
 * @param new_state
 * @param action
 * @return 合法且操作成功返回1，否则返回0
 */
{
    new_state = old_state;
    int i_des=-1;int j_des=-1;

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

    if(action!=L && action!=R && action!=U && action!=D){return FAILED;}
    //越界检查
    else if(action==U && (i_pos==0&&j_pos!=2)){return FAILED;}
    else if(action==D && (i_pos==4&&j_pos!=2)){return FAILED;}
    else if(action==L && (j_pos==0&&i_pos!=2)){return FAILED;}
    else if(action==R && (j_pos==4&&i_pos!=2)){return FAILED;}

    //虫洞case
    else if(i_pos==0&&j_pos==2&&action==U){
        i_des = 4;
        j_des = 2;
    }else if(i_pos==4&&j_pos==2&&action==D){
        i_des = 0;
        j_des = 2;
    }else if(i_pos==2&&j_pos==0&&action==L){
        i_des = 2;
        j_des = 4;
    }else if(i_pos==2&&j_pos==4&&action==R){
        i_des = 2;
        j_des = 0;
    }
    //正常移动
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
    // 越界检查，黑洞检查
    if( (i_des<0||j_des<0) || (old_state[i_des][j_des]<0) ){
        return FAILED;
    }else{
        //swap positon
        new_state[i_des][j_des] = old_state[i_pos][j_pos];
        new_state[i_pos][j_pos] = old_state[i_des][j_des];
    }
    return SUCCESS;
}

/****************************************************************************/
void SaveCoordinates(const vector<vector<int>> &targetMatrix){
    for(int i=0;i<targetMatrix.size();i++){
        for (int j = 0; j < targetMatrix[0].size(); ++j) {
            if(targetMatrix[i][j] >= 0){
                g_targetCoordinates[targetMatrix[i][j]].x = i;
                g_targetCoordinates[targetMatrix[i][j]].y = j;
            }
        }
    }
}

/****************************************************************************/
int ManhattanDistance(Coordinate A,Coordinate B){
    return abs(A.x-B.x)+abs(A.y-B.y);
}

/****************************************************************************/
void PrintPath(struct SearchStates *goalState)
/***
* @Description 递归打印路径
* @param goalState
*/
{
    if(goalState->previousState == nullptr){
        return;
    }
    PrintPath(goalState->previousState);
    switch(goalState->action){
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
    if(goalState->cost - goalState->depth == 0){
        cout << ",";
    }
    //递归free之前malloc的空间
    //free(goalState);
}

/****************************************************************************/
void WriteFile(ofstream &fileStream,struct SearchStates *goalState){
    if(goalState->previousState == nullptr){
        return;
    }
    WriteFile(fileStream, goalState->previousState);
    switch(goalState->action){
        case L:
            fileStream << "L";
            break;
        case R:
            fileStream << "R";
            break;
        case U:
            fileStream << "U";
            break;
        case D:
            fileStream << "D";
            break;
    }
    if(goalState->cost - goalState->depth == 0){
        fileStream << ",";
    }
    //递归free之前malloc的空间
    free(goalState);
}