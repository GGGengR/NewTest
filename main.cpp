#include <iostream>
#include <fstream>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ctime>
#define MAX_CAPACITY 300  // �ٶ��ɻ�����ؿ���Ϊ300
#define TOTAL_AIRLINE 5
#define ALL_CAPACITY MAX_CAPACITY*TOTAL_AIRLINE
#define ADMIN_NAME "admin"
#define ADMIN_ID 123456

using namespace std;

// ĳ���κ���
struct FlightInfo {
  int flight_id;                                // �����ţ���1��ʼ����TOTAL_AIRLINEΪֹ
  string flight_time_leave;                     // �������ʱ�䣬��ʽΪ��20200101��
  string flight_time_arrive;                    // ����ִ�ʱ�䣬��ʽΪ��20200101��
  string flight_city_leave;                     // ����������У�
  string flight_city_arrive;                    // ����ִ���У�
  int flight_price;                             // ����Ʊ�ۣ�
  float flight_discount;                        // �����ۿۣ�
  int remain_tickets;                           // �ú�����Ʊ��
};

// ĳ���˿͵���Ϣ
struct PassengerInfo {
    string passenger_name;   //�˿�����
    int passenger_id;        // �˿�id
    int ticket_number;
    string sign;   // �ó˿͹���Ʊ��
};

void passenger();//�˿ͽ���
void admin();//����Ա����
void post();//ע��
void passenger_flight_check();//�鿴�˿ͺ�����Ϣ
void flight_recommend(string city_leave,string city_arrive);//�����Ƽ���ת
void recommend(FlightInfo flightinfo[TOTAL_AIRLINE],string city_leave,string city_arrive);//�����Ƽ��㷨
void passenger_flight_add();//��Ʊ
void passenger_flight_return();//��Ʊ
void admin_flight_info_input();//������Ϣ����
void admin_flight_info_modify();//������Ϣ�޸�
void admin_passenger_info_check();//�鿴�˿���Ϣ
void admin_flight_info_check();//�鿴������Ϣ
void admin_flight_passenger_info_check();//����˿ͱ�
void admin_passenger_flight_info_check();//�˿ͺ����

void menu()         //���˵�
{
    int ID,passenger_num,i,j;
    string name;
    ifstream infile;
    while(true)
    {
        system("PAUSE");
        system("cls");
        printf("���ã���ӭʹ�÷ɻ���Ʊϵͳ��\n\n");
        printf("*************************************************\n");
        printf("* ʹ��˵����                                    *\n");
        printf("* ���������������Ϊ����                        *\n");
        printf("* �ɹ�ѡ��ĺ��α��Ϊ1-%d, ÿ�ܴ�����ؿ���Ϊ%d*\n", TOTAL_AIRLINE,MAX_CAPACITY);
        printf("*************************************************\n");
        printf("   �˿͵�¼��������1��\n   ����Ա��½��������2��\n   �˿�ע��,������3��\n   �˳�ϵͳ��������0;\n");
        cin >> j ;
        switch(j)
        {
        case 1:{
            cout <<"������������ID��";
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
            cout <<"û���û���Ϣ����ע�ᣡ"<<endl;
            break;}
        case 2:{
            cout <<"������������ID��";
            cin >>name >> ID;
            if (name == ADMIN_NAME && ID == ADMIN_ID)
            {
                admin();
                break;
            }else
            {
                cout<< "����Ա�û���������������������";
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

void  passenger()               //�˿ͽ���
{
    int i;
    while(true)
    {
        system("PAUSE");
        system("cls");
        printf("1.��ѯ��Ʊ��Ϣ\n");
        printf("2.��Ʊ\n");
        printf("3.��Ʊ\n");
        printf("0.�˳���Ʊϵͳ\n");
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

void passenger_flight_check()       //��ѯ��Ʊ��Ϣ
{
    int flight_num,i,j,k=0;
    string city_leave,city_arrive;
    FlightInfo flightinfo;
    bool sign=true;
    ifstream infile;
    infile.open("E:\\FlightInfo.txt");
    cout << "�������Ų�ѯ�밴   1    "<<endl;
    cout << "�������͵ִ�ص��ѯ�밴    2   "<< endl;
    cin >> j;
    if (j==1)
    {
        cout << "�������ѯ�ĺ��ࣺ" <<endl;
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
            cout << "δ�鵽������Ϊ "<<flight_num<<"�ĺ��ࡣ"<<endl;
        }
        else if(flightinfo.remain_tickets==0)
            flight_recommend(flightinfo.flight_city_leave,flightinfo.flight_city_arrive );
    }
    else if (j== 2)
    {
        cout << "����������ص�͵ִ�ص㣺" <<endl;
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
            cout << "δ�鵽�����ص�Ϊ "<<city_leave<<"������ص�Ϊ"<<city_arrive<<"�ĺ��ࡣ����Ʊ"<<endl;
            flight_recommend(flightinfo.flight_city_leave,flightinfo.flight_city_arrive );
        }
    }
    else
        cout << "���������������������롣"<<endl;
}

void flight_recommend(string city_leave,string city_arrive)         //�����Ƽ���ת
{
    int i=0;
    FlightInfo flightinfo[TOTAL_AIRLINE];
    ifstream infile;
    infile.open("E:\\FlightInfo.txt");
    cout << "Ϊ���Ƽ���������Ϊ "<<city_leave<<"�ִ����Ϊ "<<city_arrive<<"������ת�˺��ࣺ"<<endl;
    for(i=0;i<TOTAL_AIRLINE;i++)
    {
        infile >> flightinfo[i].flight_id >> flightinfo[i].flight_time_leave >> flightinfo[i].flight_time_arrive >> flightinfo[i].flight_city_leave
        >> flightinfo[i].flight_city_arrive >> flightinfo[i].flight_price >> flightinfo[i].flight_discount >> flightinfo[i].remain_tickets ;
    }
    infile.close();
    recommend(flightinfo,city_leave,city_arrive);
}

void recommend(FlightInfo flightinfo[TOTAL_AIRLINE],string city_leave,string city_arrive)           //�ݹ�ʵ�ֺ����Ƽ��㷨
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

void passenger_flight_add()     //��Ʊ
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
    cout << "�������������������ID��";
    cin  >> passenger_name >>passenger_id;
    cout << "��������ѡ���ĺ����ţ�";
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
        cout <<passenger_name<<",δ�ҵ�������Ϊ" << flight_num <<"�ĺ�����Ϣ" << endl;
    }
    else
    {
        cout  <<passenger_name<<"��ϲ������Ʊ�ɹ���"<<endl;
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
            passenger_name <<" "<< passenger_id <<" "<<"δ��Ʊ"<< endl;
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

void passenger_flight_return()   //��Ʊ
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
    cout << "���������Ķ�����ţ�";
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
            passenger[k].sign="����Ʊ";
        }
        k++;
    }
    infile.close();
    if(sign)
    {
        cout <<"δ�鵽�˱����Ϣ" <<endl;
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
    cout  <<passenger_name<<"���ã���Ʊ�ɹ���"<<endl;
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

void admin()                    //����Ա����
{
    int i;
    while(true)
    {
        system("PAUSE");
        system("cls");
        printf("1.���뺽����Ϣ\n");
        printf("2.�޸ĺ�����Ϣ\n");
        printf("3.�鿴������Ϣ\n");
        printf("4.�鿴�˿���Ϣ\n");
        printf("5.�鿴����˿ͱ�\n");
        printf("6.�鿴�˿ͺ�����Ϣ\n");
        printf("0.�˳�����ϵͳ\n");
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

void admin_flight_info_input()   // ���뺽����Ϣ
{
    int i = 0 ;
    FlightInfo flightinfo[TOTAL_AIRLINE];
    cout <<"�����뺽����  ����ʱ��  �ִ�ʱ��  ��������  �ִ����  ����Ʊ��  �����ۿ�  ������Ʊ\n" <<endl;
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

void admin_flight_info_check()      //�鿴������Ϣ
{
    int i=0;
    FlightInfo flightinfo[TOTAL_AIRLINE];
    ifstream infile;
    infile.open("E:\\FlightInfo.txt");
    cout <<"������  ����ʱ��  �ִ�ʱ��  ��������  �ִ����  ����Ʊ��  �����ۿ�  ������Ʊ" <<endl;
    for(i=0;i<TOTAL_AIRLINE;i++)
    {
        infile >> flightinfo[i].flight_id >> flightinfo[i].flight_time_leave >> flightinfo[i].flight_time_arrive >> flightinfo[i].flight_city_leave >> flightinfo[i].flight_city_arrive >> flightinfo[i].flight_price >> flightinfo[i].flight_discount >> flightinfo[i].remain_tickets ;
        cout << flightinfo[i].flight_id <<" "<< flightinfo[i].flight_time_leave <<" "<< flightinfo[i].flight_time_arrive <<" "<<
         flightinfo[i].flight_city_leave <<" "<< flightinfo[i].flight_city_arrive <<" "<< flightinfo[i].flight_price <<" "<<
          flightinfo[i].flight_discount <<" "<< flightinfo[i].remain_tickets << endl;
    }
    infile.close();
}

void admin_flight_info_modify()     //�޸ĺ�����Ϣ
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
    cout <<"������Ҫ�޸ĵĺ����ţ�";
    cin  >>flight_num;
    for(i=0;i<TOTAL_AIRLINE&&sign;i++)
    {
        if (flightinfo[i].flight_id == flight_num)
        {
            cout <<"�����뺽����  ����ʱ��  �ִ�ʱ��  ��������  �ִ����  ����Ʊ��  �����ۿ�  ������Ʊ\n" <<endl;
            cin >> flightinfo[i].flight_id >> flightinfo[i].flight_time_leave >> flightinfo[i].flight_time_arrive >> flightinfo[i].flight_city_leave >>
            flightinfo[i].flight_city_arrive >> flightinfo[i].flight_price >> flightinfo[i].flight_discount >> flightinfo[i].remain_tickets;
            sign = false;
        }
    }
    infile.close();
    if (sign)
    {
        cout <<"δ�ҵ�������Ϊ" << flight_num <<"�ĺ�����Ϣ" << endl;
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

void admin_passenger_info_check()      //�鿴�˿���Ϣ��
{
    int i=0,passenger_num;
    ifstream infile;
    infile.open("E:\\PassengerInfo.txt");
    infile >> passenger_num;
    PassengerInfo passengerinfo[passenger_num];
    cout <<"�˿����� �˿�ID ��Ʊ����" <<endl;
    for(i=0;i<passenger_num;i++)
    {
        infile >> passengerinfo[i].passenger_name >> passengerinfo[i].passenger_id >> passengerinfo[i].ticket_number ;
        cout << passengerinfo[i].passenger_name <<" "<< passengerinfo[i].passenger_id <<" "<< passengerinfo[i].ticket_number << endl;
    }
    infile.close();
}

void admin_flight_passenger_info_check()    //�鿴����˿ͱ�
{
    int flight_num,passenger_id,order=1,k=0;
    string passenger_name,passenger_sign;
    FlightInfo flightinfo0;
    ifstream infile;
    infile.open("E:\\FlightPassengerInfo.txt");
    cout << "��������Ҫ��ѯ�ĺ��ࣺ" ;
    cin >> flight_num;
    while(infile.peek()!=EOF)
    {
        infile >> order >> flightinfo0.flight_id >> flightinfo0.flight_time_leave >> flightinfo0.flight_time_arrive >>
        flightinfo0.flight_city_leave >> flightinfo0.flight_city_arrive >> flightinfo0.flight_price >> passenger_name >> passenger_id >>passenger_sign;
        infile.get();
        if (flightinfo0.flight_id==flight_num && passenger_sign!="����Ʊ")
        {
            cout << "�˿�����: "<<passenger_name <<" �˿�ID��"<<passenger_id<<endl;
            k++;
        }
    }
    cout <<"���� "<<flight_num<<" ���� "<<k<<" ���˿ͣ�"<<endl;
    infile.close();
}

void admin_passenger_flight_info_check()        //�鿴�˿ͺ�����Ϣ
{
    int passenger_num,passenger_id,order=1,k=0;
    string passenger_name,passenger_sign,name;
    FlightInfo flightinfo[TOTAL_AIRLINE],flightinfo0;
    ifstream infile;
    infile.open("E:\\FlightPassengerInfo.txt");
    cout << "��������Ҫ��ѯ�ĳ˿�ID��" ;
    cin >> passenger_num;
    while(infile.peek()!=EOF)
    {
        infile >> order >> flightinfo0.flight_id >> flightinfo0.flight_time_leave >> flightinfo0.flight_time_arrive >>
        flightinfo0.flight_city_leave >> flightinfo0.flight_city_arrive >> flightinfo0.flight_price >> passenger_name >> passenger_id >>passenger_sign;
        infile.get();
        if (passenger_id==passenger_num&&passenger_sign!="����Ʊ")
        {
            name=passenger_name;
            cout << "������: "<<flightinfo0.flight_id <<" �������ʱ�䣺"<<flightinfo0.flight_time_leave<<" ����ִ�ʱ�䣺"<< flightinfo0.flight_time_arrive
            <<" ��������ص�: "<< flightinfo0.flight_city_leave <<" ����ִ�ص㣺"<< flightinfo0.flight_city_arrive <<" ����Ʊ�ۣ�"<< flightinfo0.flight_price <<endl;
            k++;
        }
    }
    cout <<"�˿� "<<name<<" ���� "<<k<<" �γ��к��࣡"<<endl;
    infile.close();
}


void post()      //ע��
{
    string name;
    int ID,passenger_num,i;
    bool sign=true;
    cout << "��ӭע��ɻ���Ʊϵͳ��\n" <<endl;
    cout << "��������������  ID  \n"  <<endl;
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
            cout << "�û��Ѵ��ڣ�" << endl;
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
