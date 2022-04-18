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

/*读取txt文件内的矩阵，返回一个int[5][5]型的变量*/
vector<vector<int>> ReadFile(const char* FileName)
{
    vector<vector<int>> matrixALL{};  //返回数组
    int row = 5;
    int count = 0;// 行数计数器
    string tmp;   // 暂存文件内单行的字符
    ifstream fileStream;
    fileStream.open(FileName, ios::in);    //ios::in 以只读的方式读取文件
    if (fileStream.fail()) {
        //文件打开失败:返回0
        throw logic_error("Read File Failed");
    }else{
        while (getline(fileStream, tmp, '\n'))//读取一行
        {
            //cout<<tmp<<std::endl;
            vector<int> tmpV{};
            istringstream is(tmp);      //分割每行字符串
            for(int i=0;i<row;i++){
                string str_tmp;
                is>>str_tmp;
                tmpV.push_back(stoi(str_tmp));
            }
            matrixALL.push_back(tmpV);
            count++;
        }
        fileStream.close();
    }
    return matrixALL;
}

int main (int argc,char* argv []){
    //测试读取txt数据并打印输出
    vector<vector<int>> matrixALL = ReadFile("../data/input00.txt");
    cout<<matrixALL.size()<<matrixALL[0].size()<<endl;
    for(int i=0;i<matrixALL.size();i++){
        for (int j = 0; j < matrixALL[0].size(); ++j) {
            cout<<matrixALL[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
