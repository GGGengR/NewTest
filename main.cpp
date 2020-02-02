#include <iostream>
#include <fstream>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ctime>
#define MAX_CAPACITY 300  // 假定飞机最大载客量为300
#define TOTAL_AIRLINE 5
#define ALL_CAPACITY MAX_CAPACITY*TOTAL_AIRLINE
#define ADMIN_NAME "admin"
#define ADMIN_ID 123456

using namespace std;

// 某航次航班
struct FlightInfo {
  int flight_id;                                // 航班编号，从1开始，到TOTAL_AIRLINE为止
  string flight_time_leave;                     // 航班出发时间，格式为‘20200101’
  string flight_time_arrive;                    // 航班抵达时间，格式为‘20200101’
  string flight_city_leave;                     // 航班出发城市，
  string flight_city_arrive;                    // 航班抵达城市，
  int flight_price;                             // 航班票价，
  float flight_discount;                        // 航班折扣，
  int remain_tickets;                           // 该航班余票数
};

// 某个乘客的信息
struct PassengerInfo {
    string passenger_name;   //乘客姓名
    int passenger_id;        // 乘客id
    int ticket_number;
    string sign;   // 该乘客购买票数
};

void passenger();//乘客界面
void admin();//管理员界面
void post();//注册
void passenger_flight_check();//查看乘客航班信息
void flight_recommend(string city_leave,string city_arrive);//航班推荐跳转
void recommend(FlightInfo flightinfo[TOTAL_AIRLINE],string city_leave,string city_arrive);//航班推荐算法
void passenger_flight_add();//订票
void passenger_flight_return();//退票
void admin_flight_info_input();//航班信息输入
void admin_flight_info_modify();//航班信息修改
void admin_passenger_info_check();//查看乘客信息
void admin_flight_info_check();//查看航班信息
void admin_flight_passenger_info_check();//航班乘客表
void admin_passenger_flight_info_check();//乘客航班表

void menu()         //主菜单
{
    int ID,passenger_num,i,j;
    string name;
    ifstream infile;
    while(true)
    {
        system("PAUSE");
        system("cls");
        printf("您好，欢迎使用飞机订票系统！\n\n");
        printf("*************************************************\n");
        printf("* 使用说明：                                    *\n");
        printf("* 本程序所有输入均为整数                        *\n");
        printf("* 可供选择的航次编号为1-%d, 每架次最大载客量为%d*\n", TOTAL_AIRLINE,MAX_CAPACITY);
        printf("*************************************************\n");
        printf("   乘客登录，请输入1；\n   管理员登陆，请输入2；\n   乘客注册,请输入3；\n   退出系统，请输入0;\n");
        cin >> j ;
        switch(j)
        {
        case 1:{
            cout <<"请输入姓名和ID：";
            cin >>name >> ID;
            infile.open("E:\\PassengerInfo.txt");
            infile >> passenger_num;
            PassengerInfo passengerinfo[passenger_num];
            for(i=0;i<passenger_num;i++)
            {
                infile >> passengerinfo[i].passenger_name >> passengerinfo[i].passenger_id >> passengerinfo[i].ticket_number ;
                if(name==passengerinfo[i].passenger_name&& passengerinfo[i].passenger_id==ID)
                {
                    infile.close();
                    passenger();
                    break;
                }
            }
            infile.close();
            cout <<"没有用户信息，请注册！"<<endl;
            break;}
        case 2:{
            cout <<"请输入姓名和ID：";
            cin >>name >> ID;
            if (name == ADMIN_NAME && ID == ADMIN_ID)
            {
                admin();
                break;
            }else
            {
                cout<< "管理员用户名密码有误，请重新输入";
                break;
            }
        }
        case 3:
            post();
            break;
        case 0:
            exit(0);
        }
    }
}

void  passenger()               //乘客界面
{
    int i;
    while(true)
    {
        system("PAUSE");
        system("cls");
        printf("1.查询机票信息\n");
        printf("2.订票\n");
        printf("3.退票\n");
        printf("0.退出订票系统\n");
        cin >> i;
        switch(i)
        {
        case 1:
            passenger_flight_check();
            break;
        case 2:
            passenger_flight_add();
            break;
        case 3:
            passenger_flight_return();
            break;
        case 0:
            menu();
        }
    }
}

void passenger_flight_check()       //查询机票信息
{
    int flight_num,i,j,k=0;
    string city_leave,city_arrive;
    FlightInfo flightinfo;
    bool sign=true;
    ifstream infile;
    infile.open("E:\\FlightInfo.txt");
    cout << "按航班编号查询请按   1    "<<endl;
    cout << "按出发和抵达地点查询请按    2   "<< endl;
    cin >> j;
    if (j==1)
    {
        cout << "请输入查询的航班：" <<endl;
        cin >> flight_num;
        for(i=0;i<TOTAL_AIRLINE;i++)
        {
            infile >> flightinfo.flight_id >> flightinfo.flight_time_leave >> flightinfo.flight_time_arrive >> flightinfo.flight_city_leave
            >> flightinfo.flight_city_arrive >> flightinfo.flight_price >> flightinfo.flight_discount >> flightinfo.remain_tickets ;
            if(flight_num==flightinfo.flight_id)
                {
                    sign=false;
                    cout <<flightinfo.flight_id <<" "<< flightinfo.flight_time_leave <<" "<< flightinfo.flight_time_arrive <<" "<< flightinfo.flight_city_leave
                    <<" "<< flightinfo.flight_city_arrive <<" "<< flightinfo.flight_price <<" "<< flightinfo.flight_discount <<" "<< flightinfo.remain_tickets <<endl;
                    break;
                }
        }
        infile.close();
        if (sign)
        {
            cout << "未查到航班编号为 "<<flight_num<<"的航班。"<<endl;
        }
        else if(flightinfo.remain_tickets==0)
            flight_recommend(flightinfo.flight_city_leave,flightinfo.flight_city_arrive );
    }
    else if (j== 2)
    {
        cout << "请输入出发地点和抵达地点：" <<endl;
        cin >> city_leave>>city_arrive;
        for(i=0;i<TOTAL_AIRLINE;i++)
        {
            infile >> flightinfo.flight_id >> flightinfo.flight_time_leave >> flightinfo.flight_time_arrive >> flightinfo.flight_city_leave
            >> flightinfo.flight_city_arrive >> flightinfo.flight_price >> flightinfo.flight_discount >> flightinfo.remain_tickets ;
            if(city_leave==flightinfo.flight_time_leave && city_arrive==flightinfo.flight_time_arrive)
                {
                    sign=false;
                    cout <<flightinfo.flight_id << flightinfo.flight_time_leave << flightinfo.flight_time_arrive << flightinfo.flight_city_leave
                    << flightinfo.flight_city_arrive << flightinfo.flight_price << flightinfo.flight_discount << flightinfo.remain_tickets ;
                    k+=flightinfo.remain_tickets;
                }
        }
        infile.close();
        if (sign || k==0)
        {
            cout << "未查到出发地点为 "<<city_leave<<"，到达地点为"<<city_arrive<<"的航班。或无票"<<endl;
            flight_recommend(flightinfo.flight_city_leave,flightinfo.flight_city_arrive );
        }
    }
    else
        cout << "您的输入有误！请重新输入。"<<endl;
}

void flight_recommend(string city_leave,string city_arrive)         //航班推荐跳转
{
    int i=0;
    FlightInfo flightinfo[TOTAL_AIRLINE];
    ifstream infile;
    infile.open("E:\\FlightInfo.txt");
    cout << "为您推荐出发城市为 "<<city_leave<<"抵达城市为 "<<city_arrive<<"的其他转乘航班："<<endl;
    for(i=0;i<TOTAL_AIRLINE;i++)
    {
        infile >> flightinfo[i].flight_id >> flightinfo[i].flight_time_leave >> flightinfo[i].flight_time_arrive >> flightinfo[i].flight_city_leave
        >> flightinfo[i].flight_city_arrive >> flightinfo[i].flight_price >> flightinfo[i].flight_discount >> flightinfo[i].remain_tickets ;
    }
    infile.close();
    recommend(flightinfo,city_leave,city_arrive);
}

void recommend(FlightInfo flightinfo[TOTAL_AIRLINE],string city_leave,string city_arrive)           //递归实现航线推荐算法
{
    int i;
    for(i=0;i<TOTAL_AIRLINE;i++)
    {
        if(city_leave==flightinfo[i].flight_city_leave && flightinfo[i].flight_city_arrive==city_arrive && flightinfo[i].remain_tickets!=0)
            cout << flightinfo[i].flight_id<<"->"<<flightinfo[i].flight_city_arrive<<endl;
        if(city_leave==flightinfo[i].flight_city_leave &&flightinfo[i].flight_city_arrive!=city_arrive && flightinfo[i].remain_tickets!=0)
        {
            cout << flightinfo[i].flight_city_leave<<"-" <<flightinfo[i].flight_id<<"->"<<flightinfo[i].flight_city_arrive<<"---";
            recommend(flightinfo,flightinfo[i].flight_city_arrive,city_arrive);
        }
    }
}

void passenger_flight_add()     //订票
{
    int i=0,j=0,flight_num,passenger_id,passenger_num;
    string passenger_name;
    bool sign = true;
    FlightInfo flightinfo[TOTAL_AIRLINE];
    time_t now = time(0);
    ifstream infile;
    ofstream outfile,outfile1;
    infile.open("E:\\FlightInfo.txt");
    for(i=0;i<TOTAL_AIRLINE;i++)
    {
        infile >> flightinfo[i].flight_id >> flightinfo[i].flight_time_leave >> flightinfo[i].flight_time_arrive >> flightinfo[i].flight_city_leave
        >> flightinfo[i].flight_city_arrive >> flightinfo[i].flight_price >> flightinfo[i].flight_discount >> flightinfo[i].remain_tickets ;
    }
    cout << "请输入您的姓名与身份ID：";
    cin  >> passenger_name >>passenger_id;
    cout << "请输入您选定的航班编号：";
    cin  >> flight_num;
    for(i=0;i<TOTAL_AIRLINE&&sign;i++)
    {
        if (flightinfo[i].flight_id == flight_num&& flightinfo[i].remain_tickets>0)
        {
            j=i;
            flightinfo[i].remain_tickets -=1;
            sign = false;
        }
    }
    infile.close();
    if (sign)
    {
        cout <<passenger_name<<",未找到航班编号为" << flight_num <<"的航班信息" << endl;
    }
    else
    {
        cout  <<passenger_name<<"恭喜您，订票成功！"<<endl;
        outfile.open("E:\\FlightInfo.txt");
        for(i=0;i<TOTAL_AIRLINE;i++)
        {
            outfile << flightinfo[i].flight_id <<" "<< flightinfo[i].flight_time_leave <<" "<< flightinfo[i].flight_time_arrive <<" "<<
            flightinfo[i].flight_city_leave <<" "<< flightinfo[i].flight_city_arrive <<" "<< flightinfo[i].flight_price <<" "<<
            flightinfo[i].flight_discount <<" "<< flightinfo[i].remain_tickets << endl;
        }
        outfile.close();
        outfile1.open("E:\\FlightPassengerInfo.txt",ios::app);
        outfile1 << now <<" "<< flightinfo[j].flight_id <<" "<< flightinfo[j].flight_time_leave <<" "<< flightinfo[j].flight_time_arrive <<" "<<
            flightinfo[j].flight_city_leave <<" "<< flightinfo[j].flight_city_arrive <<" "<< flightinfo[j].flight_price <<" "<<
            passenger_name <<" "<< passenger_id <<" "<<"未退票"<< endl;
        outfile1.close();
        infile.open("E:\\PassengerInfo.txt");
        infile >> passenger_num;
        PassengerInfo passengerinfo[passenger_num];
        for(i=0;i<passenger_num;i++)
        {
            infile >> passengerinfo[i].passenger_name >> passengerinfo[i].passenger_id >> passengerinfo[i].ticket_number ;
            if(passenger_id==passengerinfo[i].passenger_id)
                passengerinfo[i].ticket_number++;
        }
        infile.close();
        outfile.open("E:\\PassengerInfo.txt");
        outfile << passenger_num <<endl;;
        for(i=0;i<passenger_num;i++)
        {
            outfile << passengerinfo[i].passenger_name <<" "<< passengerinfo[i].passenger_id <<" "<< passengerinfo[i].ticket_number <<endl;
        }
        outfile.close();
    }
}

void passenger_flight_return()   //退票
{
    int i=0,k=0,passenger_id,flight_id,order_num,passenger_num;
    long order[ALL_CAPACITY];
    string passenger_name,passenger_sign;
    bool sign = true;
    PassengerInfo passenger[ALL_CAPACITY];
    FlightInfo flightinfo[TOTAL_AIRLINE],flightinfo1[ALL_CAPACITY];
    ifstream infile;
    ofstream outfile;
    infile.open("E:\\FlightPassengerInfo.txt");
    cout << "请输入您的订单编号：";
    cin  >> order_num;
    while(infile.peek()!=EOF)
    {
        infile >> order[k] >> flightinfo1[k].flight_id >> flightinfo1[k].flight_time_leave >> flightinfo1[k].flight_time_arrive >>
        flightinfo1[k].flight_city_leave >> flightinfo1[k].flight_city_arrive >> flightinfo1[k].flight_price
        >> passenger[k].passenger_name >> passenger[k].passenger_id >>passenger[k].sign;
        if (order[k] == order_num)
        {
            sign = false;
            flight_id=flightinfo1[k].flight_id;
            passenger_id=passenger[k].passenger_id;
            passenger[k].sign="已退票";
        }
        k++;
    }
    infile.close();
    if(sign)
    {
        cout <<"未查到此编号信息" <<endl;
    }
    else
    {
        outfile.open("E:\\FlightPassengerInfo.txt");
        for(i=0;i<k-1;i++)
        {
            outfile << order[i] <<" "<< flightinfo1[i].flight_id <<" "<< flightinfo1[i].flight_time_leave <<" "<< flightinfo1[i].flight_time_arrive <<" "<<
            flightinfo1[i].flight_city_leave <<" "<< flightinfo1[i].flight_city_arrive <<" "<< flightinfo1[i].flight_price <<" "<<
            passenger[i].passenger_name <<" "<< passenger[i].passenger_id <<" "<<passenger[i].sign<< endl;
        }
        outfile.close();
    infile.open("E:\\FlightInfo.txt",ios::in);
    for(i=0;i<TOTAL_AIRLINE;i++)
    {
        infile >> flightinfo[i].flight_id >> flightinfo[i].flight_time_leave >> flightinfo[i].flight_time_arrive >> flightinfo[i].flight_city_leave >>
         flightinfo[i].flight_city_arrive >> flightinfo[i].flight_price >> flightinfo[i].flight_discount >> flightinfo[i].remain_tickets ;
        if( flightinfo[i].flight_id == flight_id )
            flightinfo[i].remain_tickets +=1;
    }
    infile.close();
    cout  <<passenger_name<<"您好，退票成功！"<<endl;
    outfile.open("E:\\FlightInfo.txt",ios::out);
    for(i=0;i<TOTAL_AIRLINE;i++)
    {
        outfile << flightinfo[i].flight_id <<" "<< flightinfo[i].flight_time_leave <<" "<< flightinfo[i].flight_time_arrive <<" "<<
        flightinfo[i].flight_city_leave <<" "<< flightinfo[i].flight_city_arrive <<" "<< flightinfo[i].flight_price <<" "<<
        flightinfo[i].flight_discount <<" "<< flightinfo[i].remain_tickets << endl;
    }
    outfile.close();
    infile.open("E:\\PassengerInfo.txt");
        infile >> passenger_num;
        PassengerInfo passengerinfo[passenger_num];
        for(i=0;i<passenger_num;i++)
        {
            infile >> passengerinfo[i].passenger_name >> passengerinfo[i].passenger_id >> passengerinfo[i].ticket_number ;
            if(passenger_id==passengerinfo[i].passenger_id)
                passengerinfo[i].ticket_number--;
        }
        infile.close();
        outfile.open("E:\\PassengerInfo.txt");
        outfile << passenger_num <<endl;;
        for(i=0;i<passenger_num;i++)
        {
            outfile << passengerinfo[i].passenger_name <<" "<< passengerinfo[i].passenger_id <<" "<< passengerinfo[i].ticket_number <<endl;
        }
        outfile.close();
    }
}

void admin()                    //管理员界面
{
    int i;
    while(true)
    {
        system("PAUSE");
        system("cls");
        printf("1.输入航班信息\n");
        printf("2.修改航班信息\n");
        printf("3.查看航班信息\n");
        printf("4.查看乘客信息\n");
        printf("5.查看航班乘客表\n");
        printf("6.查看乘客航班信息\n");
        printf("0.退出管理系统\n");
        cin >> i ;
        switch(i)
        {
        case 1:
            admin_flight_info_input();
            break;
        case 2:
            admin_flight_info_modify();
            break;
        case 3:
            admin_flight_info_check();
            break;
        case 4:
            admin_passenger_info_check();
            break;
        case 5:
            admin_flight_passenger_info_check();
            break;
        case 6:
            admin_passenger_flight_info_check();
            break;
        case 0:
            menu();
        }
    }
}

void admin_flight_info_input()   // 输入航班信息
{
    int i = 0 ;
    FlightInfo flightinfo[TOTAL_AIRLINE];
    cout <<"请输入航班编号  出发时间  抵达时间  出发城市  抵达城市  航班票价  航班折扣  航班余票\n" <<endl;
    for(i=0;i<TOTAL_AIRLINE;i++)
    {
        cin >> flightinfo[i].flight_id >> flightinfo[i].flight_time_leave >> flightinfo[i].flight_time_arrive >> flightinfo[i].flight_city_leave >>
        flightinfo[i].flight_city_arrive >> flightinfo[i].flight_price >> flightinfo[i].flight_discount >> flightinfo[i].remain_tickets;
    }
    ofstream outfile;
    outfile.open("E:\\FlightInfo.txt");
    for(i=0;i<TOTAL_AIRLINE;i++)
    {
        outfile << flightinfo[i].flight_id <<" "<< flightinfo[i].flight_time_leave <<" "<< flightinfo[i].flight_time_arrive <<" "<<
        flightinfo[i].flight_city_leave <<" "<< flightinfo[i].flight_city_arrive <<" "<< flightinfo[i].flight_price <<" "<<
         flightinfo[i].flight_discount <<" "<< flightinfo[i].remain_tickets << endl;
    }
    outfile.close();
}

void admin_flight_info_check()      //查看航班信息
{
    int i=0;
    FlightInfo flightinfo[TOTAL_AIRLINE];
    ifstream infile;
    infile.open("E:\\FlightInfo.txt");
    cout <<"航班编号  出发时间  抵达时间  出发城市  抵达城市  航班票价  航班折扣  航班余票" <<endl;
    for(i=0;i<TOTAL_AIRLINE;i++)
    {
        infile >> flightinfo[i].flight_id >> flightinfo[i].flight_time_leave >> flightinfo[i].flight_time_arrive >> flightinfo[i].flight_city_leave >> flightinfo[i].flight_city_arrive >> flightinfo[i].flight_price >> flightinfo[i].flight_discount >> flightinfo[i].remain_tickets ;
        cout << flightinfo[i].flight_id <<" "<< flightinfo[i].flight_time_leave <<" "<< flightinfo[i].flight_time_arrive <<" "<<
         flightinfo[i].flight_city_leave <<" "<< flightinfo[i].flight_city_arrive <<" "<< flightinfo[i].flight_price <<" "<<
          flightinfo[i].flight_discount <<" "<< flightinfo[i].remain_tickets << endl;
    }
    infile.close();
}

void admin_flight_info_modify()     //修改航班信息
{
    int i=0,flight_num;
    bool sign = true;
    FlightInfo flightinfo[TOTAL_AIRLINE];
    ifstream infile;
    ofstream outfile;
    infile.open("E:\\FlightInfo.txt");
    for(i=0;i<TOTAL_AIRLINE;i++)
    {
        infile >> flightinfo[i].flight_id >> flightinfo[i].flight_time_leave >> flightinfo[i].flight_time_arrive >> flightinfo[i].flight_city_leave >> flightinfo[i].flight_city_arrive >> flightinfo[i].flight_price >> flightinfo[i].flight_discount >> flightinfo[i].remain_tickets ;
    }
    cout <<"请输入要修改的航班编号：";
    cin  >>flight_num;
    for(i=0;i<TOTAL_AIRLINE&&sign;i++)
    {
        if (flightinfo[i].flight_id == flight_num)
        {
            cout <<"请输入航班编号  出发时间  抵达时间  出发城市  抵达城市  航班票价  航班折扣  航班余票\n" <<endl;
            cin >> flightinfo[i].flight_id >> flightinfo[i].flight_time_leave >> flightinfo[i].flight_time_arrive >> flightinfo[i].flight_city_leave >>
            flightinfo[i].flight_city_arrive >> flightinfo[i].flight_price >> flightinfo[i].flight_discount >> flightinfo[i].remain_tickets;
            sign = false;
        }
    }
    infile.close();
    if (sign)
    {
        cout <<"未找到航班编号为" << flight_num <<"的航班信息" << endl;
    }
    else
    {
        outfile.open("E:\\FlightInfo.txt");
        for(i=0;i<TOTAL_AIRLINE;i++)
        {
            outfile << flightinfo[i].flight_id <<" "<< flightinfo[i].flight_time_leave <<" "<< flightinfo[i].flight_time_arrive <<" "<<
            flightinfo[i].flight_city_leave <<" "<< flightinfo[i].flight_city_arrive <<" "<< flightinfo[i].flight_price <<" "<<
            flightinfo[i].flight_discount <<" "<< flightinfo[i].remain_tickets << endl;
        }
    }
    outfile.close();
}

void admin_passenger_info_check()      //查看乘客信息表
{
    int i=0,passenger_num;
    ifstream infile;
    infile.open("E:\\PassengerInfo.txt");
    infile >> passenger_num;
    PassengerInfo passengerinfo[passenger_num];
    cout <<"乘客姓名 乘客ID 订票数量" <<endl;
    for(i=0;i<passenger_num;i++)
    {
        infile >> passengerinfo[i].passenger_name >> passengerinfo[i].passenger_id >> passengerinfo[i].ticket_number ;
        cout << passengerinfo[i].passenger_name <<" "<< passengerinfo[i].passenger_id <<" "<< passengerinfo[i].ticket_number << endl;
    }
    infile.close();
}

void admin_flight_passenger_info_check()    //查看航班乘客表
{
    int flight_num,passenger_id,order=1,k=0;
    string passenger_name,passenger_sign;
    FlightInfo flightinfo0;
    ifstream infile;
    infile.open("E:\\FlightPassengerInfo.txt");
    cout << "请输入您要查询的航班：" ;
    cin >> flight_num;
    while(infile.peek()!=EOF)
    {
        infile >> order >> flightinfo0.flight_id >> flightinfo0.flight_time_leave >> flightinfo0.flight_time_arrive >>
        flightinfo0.flight_city_leave >> flightinfo0.flight_city_arrive >> flightinfo0.flight_price >> passenger_name >> passenger_id >>passenger_sign;
        infile.get();
        if (flightinfo0.flight_id==flight_num && passenger_sign!="已退票")
        {
            cout << "乘客姓名: "<<passenger_name <<" 乘客ID："<<passenger_id<<endl;
            k++;
        }
    }
    cout <<"航班 "<<flight_num<<" 共有 "<<k<<" 名乘客！"<<endl;
    infile.close();
}

void admin_passenger_flight_info_check()        //查看乘客航班信息
{
    int passenger_num,passenger_id,order=1,k=0;
    string passenger_name,passenger_sign,name;
    FlightInfo flightinfo[TOTAL_AIRLINE],flightinfo0;
    ifstream infile;
    infile.open("E:\\FlightPassengerInfo.txt");
    cout << "请输入您要查询的乘客ID：" ;
    cin >> passenger_num;
    while(infile.peek()!=EOF)
    {
        infile >> order >> flightinfo0.flight_id >> flightinfo0.flight_time_leave >> flightinfo0.flight_time_arrive >>
        flightinfo0.flight_city_leave >> flightinfo0.flight_city_arrive >> flightinfo0.flight_price >> passenger_name >> passenger_id >>passenger_sign;
        infile.get();
        if (passenger_id==passenger_num&&passenger_sign!="已退票")
        {
            name=passenger_name;
            cout << "航班编号: "<<flightinfo0.flight_id <<" 航班出发时间："<<flightinfo0.flight_time_leave<<" 航班抵达时间："<< flightinfo0.flight_time_arrive
            <<" 航班出发地点: "<< flightinfo0.flight_city_leave <<" 航班抵达地点："<< flightinfo0.flight_city_arrive <<" 航班票价："<< flightinfo0.flight_price <<endl;
            k++;
        }
    }
    cout <<"乘客 "<<name<<" 共有 "<<k<<" 次出行航班！"<<endl;
    infile.close();
}


void post()      //注册
{
    string name;
    int ID,passenger_num,i;
    bool sign=true;
    cout << "欢迎注册飞机购票系统：\n" <<endl;
    cout << "请输入您的姓名  ID  \n"  <<endl;
    cin >> name >> ID;
    ifstream infile;
    infile.open("E:\\PassengerInfo.txt");
    infile >> passenger_num;
    PassengerInfo passengerinfo[passenger_num+1];
    for(i=0;i<passenger_num;i++)
    {
        infile >> passengerinfo[i].passenger_name >> passengerinfo[i].passenger_id >> passengerinfo[i].ticket_number ;
        if (ID==passengerinfo[i].passenger_id)
        {
            sign=false;
            cout << "用户已存在！" << endl;
        }
    }
    infile.close();
    if (sign)
    {
        ofstream outfile;
        outfile.open("E:\\PassengerInfo.txt");
        outfile << ++passenger_num <<endl;;
        passengerinfo[i].passenger_name=name;
        passengerinfo[i].passenger_id=ID;
        passengerinfo[i].ticket_number=0;
        for(i=0;i<passenger_num;i++)
        {
            outfile << passengerinfo[i].passenger_name <<" "<< passengerinfo[i].passenger_id <<" "<< passengerinfo[i].ticket_number <<endl;
        }
        outfile.close();
    }
}

int main()
{
    menu();
    return 0;
}
