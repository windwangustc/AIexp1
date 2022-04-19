#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

/*A_h1 A_h2 IDA_h2 4个函数，分别代表A* 和 迭代A* 及2种启发函数*/
void A_h1(const vector<vector<int> > &start, const vector<vector<int> > &target);
void A_h2(const vector<vector<int> > &start, const vector<vector<int> > &target);
void IDA_h1(const vector<vector<int> > &start, const vector<vector<int> >&target);
void IDA_h2(const vector<vector<int> > &start, const vector<vector<int> > &target);
vector<vector<int>> ReadFile(const char* FileName);
int CountMisplacedStars(const vector<vector<int>> &source, const vector<vector<int>> &target);

int main (int argc,char* argv []){
    //测试读取txt数据并打印输出
    vector<vector<int>> SourceMatrix = ReadFile("../data/input00.txt");
    vector<vector<int>> TargetMatrix = ReadFile("../data/target00.txt");
    for(int i=0;i<SourceMatrix.size();i++){
        for (int j = 0; j < SourceMatrix[0].size(); ++j) {
            cout<<SourceMatrix[i][j]<<" ";
        }
        cout<<endl;
    }
    for(int i=0;i<TargetMatrix.size();i++){
        for (int j = 0; j < TargetMatrix[0].size(); ++j) {
            cout<<TargetMatrix[i][j]<<" ";
        }
        cout<<endl;
    }
    //测试输出错位的星球数
    cout<<"Misplaced Stars = "<<CountMisplacedStars(SourceMatrix,TargetMatrix)<<endl;
    return 0;
}

/*读取txt文件内的矩阵，返回一个int[5][5]型的变量*/
vector<vector<int>> ReadFile(const char* FileName){
    vector<vector<int>> sourceMatrix{};  //返回数组
    int row = 5;
    int count = 0;// 行数计数器
    string tmp;   // 暂存文件内单行的字符
    ifstream fileStream;
    fileStream.open(FileName, ios::in);    //ios::in 以只读的方式读取文件
    if (fileStream.fail()) {
        //文件打开失败:返回0
        throw logic_error("Read File Failed");
    }else{
        while (getline(fileStream, tmp, '\n')){     //读取一行
            //cout<<tmp<<std::endl;
            vector<int> tmpV{};
            istringstream is(tmp);      //分割每行字符串
            for(int i=0;i<row;i++){
                string str_tmp;
                is>>str_tmp;
                tmpV.push_back(stoi(str_tmp));
            }
            sourceMatrix.push_back(tmpV);
            count++;
        }
        fileStream.close();
    }
    return sourceMatrix;
}

//计算错位的星球数，用于启发式函数h1(n)
int CountMisplacedStars(const vector<vector<int>> &source, const vector<vector<int>> &target){
    int count=0;
    //遍历比较source和target不同的数目即可
    for(int i=0;i<source.size();i++){
        for (int j = 0; j < source[0].size(); ++j) {
            if(source[i][j] != target[i][j]){
                count ++;
            }
        }
    }
    return count;
}