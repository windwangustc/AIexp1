/***
 * 1. 车间1:有7名工人
 工人1:senior
 工人2:senior
 工人3:junior
 工人4:junior
 工人5:junior
 工人6:junior
 工人7:junior
 1. 每个工人每周必须休息2天或2天以上
 2. 每个工人每周不可以连续休息3天(不考虑跨周情况)
 3. 周六周天也需要有人值班，即一周7天每天都要安排工人值班
 4. 由于车间规模较大，需要每天安排至少 4 个人值班
 5. 每天至少要有一名级别为 senior 的工人值班
 其中工人1和工人4，工人2和工人3，工人3和工人6不想在同一天工作。
 */
#include <iostream>
#include <vector>
using namespace std;
#define Senior 1
#define Junior 0
#define SUCCESS 1
#define FAILED 0

//enum WEEKDAYS {Mon=0,Tue,Wed,Thu,Fri,Sat,Sun};

class Workers{
    int workerID;        //工人序号
    int title;           //senior or junior
    int workedDays[7]={}; //上班为1，休息为0
    //下面信息均由workedDays[7]算出。也可以根据需要看是否需要固定这些信息。
    //int workedDays;      //本周已工作的天数
    //int restedDays;      //目前为止，本周已经连续休息的天数 初始值目前设为0，但可能有问题
    //int lastWorkedDay;   //最后一次工作是在哪天

public:
    //构造函数，可按需求修改
    Workers(int WorkerID,int Title) : workerID(WorkerID),title(Title) {}
    int getID() const{ return this->workerID;}
    int getTitle() const{ return this->title;}
    //打印工人信息
    void showWorkersInfo(){
        cout<<"工人ID：" << workerID << " title：" << title <<"\n";
        cout<<"工作日信息：" ;
        for(int workedDay : workedDays)
            cout<< workedDay << " " ;
        cout<<endl;
    }
    //获取本周已工作的天数
    int getWorkedDays() const{
        int sum=0;
        for(int workedDay : workedDays)
            sum+=workedDay;
        return sum;
    }
    //获取本周最后一天工作的那天， 周一～周日返回1～7，未工作返回0
    int getlastWorkedDay() const{
        for(int i=6;i>=0;i--){
            if(workedDays[i]==1)
                return i+1;
        }
        return 0;
    }
    //目前为止，本周已经连续休息的天数
    //也就是最大连续0的个数
    int getRestedDays() const{
        int max0=0,max1=0;//存放最大连续串的个数
        int zero=0,one=0;//0和1的计数器
        for(int i=0;i<7;i++){
            if(workedDays[i]==0){
                zero++;
                if(zero>max0) max0=zero;//将连续0串的最大值存放在变量max0中
                if(one>max1) max1=one;//将连续1串的最大值存放在变量max1中
                one=0;//将1的计数器清0
            }
            if(workedDays[i]==1){
                one++;
                if(zero>max0) max0=zero;
                if(one>max1) max1=one;
                zero=0;//将0的将计数器清0
            }
        }
        return max0;
    }
    //是否连续休息了三天，每次修改上班信息后，都需要判断
    bool isRestedTooMany () const{return this->getRestedDays() >= 3; }
    //判断某位工人休息时间是否大于2天
    bool isEnoughRest () const{
        if(this->getWorkedDays() > 5 ) return false;
        else return true;
    }
    //在某天上班
    void goWorkAt(int day){
        workedDays[day-1]=1;
    }
    //取消在某天上班
    void cancelWorkAt(int day){
        workedDays[day-1]=0;
    }

    //friend class Schedule;
};

class Schedule{
    vector<vector<int>> table;    //第一行代表周一,第j列代表工人j是否值班，值班为1，否则为0
    int days[7]={};       //每周几的值班工人数
public:
    //构造函数，可按需求修改
    explicit Schedule(vector<vector<int>> Table) : table(std::move(Table)) {}
    int getTableValue(int day,int worker){ return this->table[day-1][worker-1];}
    int getWorkerNumAt(int day){return this->days[day-1];}
    //打印排班表
    void showTable() const{
        cout << "排班表 :" <<endl;
        for(int i=0; i < table.size(); i++){
            cout << "周" << i+1 <<" : " ;
            for (int j = 0; j < table[0].size(); ++j){
                cout << table[i][j] << " ";
            }
            cout << "\n";
        }
    }
    //车间是否每天都有人4人及以上值班
    bool isEnoughWorkersEveryday() const{
        for(int day : days){
            if(day<4)
                return false;
        }
        return true;
    }
    //车间在某天是否有4人以上值班
    bool isEnoughWorkersAtDay(int day) const{
        if(days[day-1] < 4){return false;}
        return true;
    }
    //检查车间在某天是否Senior工人值班
    bool isSeniorOnDuty(int day,int SeniorID1,int SeniorID2) const{
        if(this->table[day-1][SeniorID1-1] == 1 || this->table[day-1][SeniorID2-1] == 1)
            return true;
        return false;
    }
    //检查整周是否有冲突工人
    bool notConflict() const{
        // 其中工人1和工人4，工人2和工人3，工人3和工人6不想在同一天工作。
        for(int i=0; i < table.size(); i++){
            if(table[i][0]*table[i][3]==1 || table[i][1]*table[i][2]==1 || table[i][3]*table[i][5]==1 )
                return false;
        }
        return true;
    }
    //安排某名工人在某天上班
    void setWorkerAt(int worker,int day){
        this->table[day-1][worker-1] = 1;
        this->days[day-1] += 1;
    }
    //取消某名工人在某天上班
    void cancelWorkerAt(int worker,int day){
        this->table[day-1][worker-1] = 0;
        this->days[day-1] -=1;
    }

    //friend class Workers;
};

//安排某位工人在某天上班
int ArrangeWork(Workers &p,Schedule &s,int day){
    //检查是否已经在这天上班了
    if(s.getTableValue(day,p.getID()) == 1)
        return FAILED;
    p.goWorkAt(day);
    s.setWorkerAt(p.getID(),day);
    return SUCCESS;
}

//取消某位工人在某天上班
int CancelWork(Workers &p,Schedule &s,int day){
    //检查是否已经在这天休息了
    if(s.getTableValue(day,p.getID()) == 0)
        return FAILED;
    p.cancelWorkAt(day);
    s.cancelWorkerAt(p.getID(),day);
    return SUCCESS;
}

int main(){
    Workers worker1(1,Senior);
    Workers worker2(2,Senior);
    Workers worker3(3,Junior);
    Workers worker4(4,Junior);
    Workers worker5(5,Junior);
    Workers worker6(6,Junior);
    Workers worker7(7,Junior);
    vector<vector <int> > table(7 ,vector<int>(7));   // 7x7 数组
    Schedule schedule(table);
    //test
    ArrangeWork(worker1,schedule,1);
    ArrangeWork(worker1,schedule,3);
    worker1.showWorkersInfo();
    schedule.showTable();
    CancelWork(worker1,schedule,1);
    ArrangeWork(worker1,schedule,4);
    worker1.showWorkersInfo();
    schedule.showTable();
    return 0;
}
