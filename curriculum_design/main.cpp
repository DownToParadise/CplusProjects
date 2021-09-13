#include<iostream>
#include<iomanip>
#include<string>
#include"graph.h"
using namespace std;

Graph<PosNode> g;
static char c;


/*��Ҫ���ڹ˿�ϵͳ����ѯ����*/
char Search()
{
    int size=g.SizeV();
    double **p=new double*[size];
    int **d=new int*[size];
    for(int i=0;i<=size;i++)
    {
        p[i]=new double[size];
        d[i]=new int[size];
    }
    cout<<"��ѯ��Ӧ�ص��밴----------1"<<endl;
    cout<<"��ѯ��Ӧ�г��밴----------2"<<endl;
    cout<<"��ʾ�����г��밴----------3"<<endl;
    cout<<"�������˵��밴------------5"<<endl;
    cout<<"�����밴-----------------0"<<endl;
    string sv,ev;
    PosNode city,city_;
    cin>>c;
    system("cls");
    switch(c)
    {
    case '1':
        cout<<"�����������\t";
        cin>>city.name;
        cout<<"\n������Ŀ�ĵ�\t";
        cin>>city_.name;
        city.code=g.FindNode(city.name);
        city_.code=g.FindNode(city_.name);
        g.Floyd(p,d);
        cout<<"�Ƽ��г�·��"<<endl;
        g.Print_path(p,d,g.FindNode(city),g.FindNode(city_));
        cout<<"�н��г�����"<<endl;
        g.Train(city, city_);
        /* ����ط���û���� */
        break;
    case '2':
        
        break;
        
    case '3':
        g.Train_Info_To_Screen();
        break;
    }
    
    
    return false; 
}

char Search_Flight()
{
   return false; 
}
/* ���ڹ�����Ա������г���Ϣ */
char Master_Train_Info()
{
    string train_code;
    cout<<"�޸��г���Ϣ�밴-------1"<<endl;
    cout<<"�����г���Ϣ�밴-------2"<<endl;
    cout<<"�������˵��밴---------5"<<endl;
    cout<<"�˳��밴---------------0"<<endl;
    cin>>c;
    switch (c)
    {
    case '1':
        cout<<"�������г�����\t";
        cin>>train_code;
        if(!g.Search_Shifts(train_code))
        {
            cout<<"���г�������\n\n";
            cout<<"�Ƿ���Ҫ�½��г���Ϣ"<<endl;
            cout<<"\t\t��Ҫ�밴-------1"<<endl;
            cout<<"\t\t�����밴-------0"<<endl;
            cin>>c;
            switch (c)
            {
            case '1':
                if(g.Add_Shift(train_code))
                {
                    cout<<"���ӳɹ�"<<endl;
                }
                break;
            default:
                c='0';
                break;
            }
        }
        else
        {
            if(g.Change_Shift(train_code))
            {
                cout<<"�޸ĳɹ�"<<endl;
                system("pause"); 
            }
        }
        system("cls");
        break;
    case '2':
        cout<<"�������½��г�����\t";
        cin>>train_code;
        if(g.Search_Shifts(train_code))
        {
            cout<<"�г��Ѿ�����"<<endl;
            break;
        }
        if(g.Add_Shift(train_code))
        {
            cout<<"���ӳɹ�"<<endl;
        }
        break;
    
    default:
        break;
    }
    
    return '0';
}


/* ��Ҫ���ڹ�����Ա���������Ϣ */
char Master_City_Info()
{
    string name;
    PosNode city,city_;
    Edgecode edge;
    double cost;
    cout<<"���������Ϣ�밴-------1"<<endl;
    cout<<"�����·��Ϣ�밴-------2"<<endl;
    cout<<"�������˵��밴---------5"<<endl;
    cout<<"�˳��밴---------------0"<<endl;
    cin>>c;
    system("cls");
    switch (c)
    {
    case '1':
        cout<<"���ӳ�����Ϣ-----1"<<endl;
        cout<<"�޸ĳ�����Ϣ-----2"<<endl;
        cout<<"ɾ��������Ϣ-----3"<<endl;
        cout<<"�˳��밴---------0"<<endl;
        cin>>c;
        system("cls");
        switch (c)
        {
        case '1':
            cout<<"�������������\t"<<endl;
            cin>>city.name;
            cout<<"��������д���\t"<<endl;
            cin>>city.code;
            if(g.FindNode(city)==-1)
            {
                if(g.InsertV(city))
                {
                    cout<<"��ӳɹ�"<<endl;
                }
            }
            else
            {
                cout<<"�����Ѵ���"<<endl;
            }
            break;
        case '2':
            cout<<"������Ҫ�޸ĳ�������\t"<<endl;
            cin>>name;
            if(g.Change_City(name))
            {
                cout<<"�޸ĳɹ�"<<endl;
            }
            break;
        case '3':
            cout<<"������Ҫɾ����������\t"<<endl;
            cin>>city.name;
            cout<<"������Ҫɾ�����д���\t"<<endl;
            cin>>city.code;
            if(g.DeleteV(city));
            break;
        default:
            break;
        }

        break;
    case '2':
        cout<<"���ӵ�·��Ϣ�밴-------1"<<endl;
        cout<<"�޸ĵ�·��Ϣ�밴-------2"<<endl;
        cout<<"ɾ����·��Ϣ�밴-------2"<<endl;
        cout<<"�������˵��밴---------5"<<endl;
        cout<<"�˳��밴---------------0"<<endl;
        cin>>c;
        switch (c)
        {
        case '1':
            cout<<"������������\t"<<endl;
            cin>>city.name;
            city.code=g.FindNode(city.name);
            cout<<"�������յ����\t"<<endl;
            cin>>city_.name;
            city_.code=g.FindNode(city_.name);
            cout<<"���������֮��·��\t"<<endl;
            cin>>cost;
            g.InsertE(city, city_, cost);
            g.InsertE(city_, city, cost);
            break;
        case '2':
            cout<<"������������\t"<<endl;
            cin>>city.name;
            city.code=g.FindNode(city.name);
            cout<<"�������յ����\t"<<endl;
            cin>>city_.name;
            city_.code=g.FindNode(city_.name);
            if(g.Change_Edge(city,city_))
            {
                cout<<"�޸ĳɹ�"<<endl;
            }

        case '3':
            cout<<"������������\t"<<endl;
            cin>>city.name;
            city.code=g.FindNode(city.name);
            cout<<"�������յ����\t"<<endl;
            cin>>city_.name;
            city_.code=g.FindNode(city_.name);
            g.DeleteE(city, city_);
            break;
        default:
            break;
        }
    default:
        break;
    }
    return '0';
}

int main()
{
    string str="��ͨ��ѯϵͳ";
    char filename[]="city_info.txt";  
    g.ReadGraph(filename);
    //g.WriteGraph("test.txt");
    g.Read_Train_Info("shift_info.txt");
    g.Write_Train_Info("test.txt");
    cout<<setiosflags(ios::right)<<setw(45)<<"��ͨ��ѯϵͳ"<<endl;
    cout<<setiosflags(ios::right)<<setw(55)<<"�˿Ͳ�ѯ------------------�밴1"<<endl;
    cout<<setiosflags(ios::right)<<setw(55)<<"������Ա------------------�밴2"<<endl;
    cout<<setiosflags(ios::right)<<setw(55)<<"�˳�ϵͳ------------------�밴0"<<endl;
    cin>>c;
    system("cls");
    switch (c)
    {
    case '1':
        c=Search();
        cout<<"�����밴----0"<<endl;
        cin>>c;
        system("cls");
        switch (c)
        {
        case '1':
            
            break;
        case '2':
            break;
        case '0':
            break;
        default:
            break;
        }
        break;
    case '2':
        cout<<"�������Ϣ�밴--------1"<<endl;
        cout<<"���������Ϣ�밴--------2"<<endl;
        cout<<"�������˵��밴----------5"<<endl;
        cout<<"�����밴----------------0"<<endl;
        cin>>c;
        system("cls");
        switch (c)
        {
        case '1':
            c=Master_Train_Info();
            break;
        case '2':
            c=Master_City_Info();
            break;
        case '0':
            break;
        default:
            break;
        };
        break;
    case '0':
        break;
    };
    g.WriteGraph("city_info.txt");
    g.Write_Train_Info("shift_info.txt");
    system("pause");
    return 0;
}