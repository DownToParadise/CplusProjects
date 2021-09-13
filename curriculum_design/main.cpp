#include<iostream>
#include<iomanip>
#include<string>
#include"graph.h"
using namespace std;

Graph<PosNode> g;
static char c;


/*主要用于顾客系统，咨询作用*/
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
    cout<<"查询对应地点请按----------1"<<endl;
    cout<<"查询对应列车请按----------2"<<endl;
    cout<<"显示所有列车请按----------3"<<endl;
    cout<<"返回主菜单请按------------5"<<endl;
    cout<<"返回请按-----------------0"<<endl;
    string sv,ev;
    PosNode city,city_;
    cin>>c;
    system("cls");
    switch(c)
    {
    case '1':
        cout<<"请输入出发地\t";
        cin>>city.name;
        cout<<"\n请输入目的地\t";
        cin>>city_.name;
        city.code=g.FindNode(city.name);
        city_.code=g.FindNode(city_.name);
        g.Floyd(p,d);
        cout<<"推荐行车路径"<<endl;
        g.Print_path(p,d,g.FindNode(city),g.FindNode(city_));
        cout<<"行进列车如下"<<endl;
        g.Train(city, city_);
        /* 这个地方还没有做 */
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
/* 用于工作人员管理火车列车信息 */
char Master_Train_Info()
{
    string train_code;
    cout<<"修改列车信息请按-------1"<<endl;
    cout<<"增添列车信息请按-------2"<<endl;
    cout<<"返回主菜单请按---------5"<<endl;
    cout<<"退出请按---------------0"<<endl;
    cin>>c;
    switch (c)
    {
    case '1':
        cout<<"请输入列车代码\t";
        cin>>train_code;
        if(!g.Search_Shifts(train_code))
        {
            cout<<"该列车不存在\n\n";
            cout<<"是否需要新建列车信息"<<endl;
            cout<<"\t\t需要请按-------1"<<endl;
            cout<<"\t\t不需请按-------0"<<endl;
            cin>>c;
            switch (c)
            {
            case '1':
                if(g.Add_Shift(train_code))
                {
                    cout<<"增加成功"<<endl;
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
                cout<<"修改成功"<<endl;
                system("pause"); 
            }
        }
        system("cls");
        break;
    case '2':
        cout<<"请输入新建列车代码\t";
        cin>>train_code;
        if(g.Search_Shifts(train_code))
        {
            cout<<"列车已经存在"<<endl;
            break;
        }
        if(g.Add_Shift(train_code))
        {
            cout<<"增加成功"<<endl;
        }
        break;
    
    default:
        break;
    }
    
    return '0';
}


/* 主要用于工作人员管理城市信息 */
char Master_City_Info()
{
    string name;
    PosNode city,city_;
    Edgecode edge;
    double cost;
    cout<<"管理城市信息请按-------1"<<endl;
    cout<<"管理道路信息请按-------2"<<endl;
    cout<<"返回主菜单请按---------5"<<endl;
    cout<<"退出请按---------------0"<<endl;
    cin>>c;
    system("cls");
    switch (c)
    {
    case '1':
        cout<<"增加城市信息-----1"<<endl;
        cout<<"修改城市信息-----2"<<endl;
        cout<<"删除城市信息-----3"<<endl;
        cout<<"退出请按---------0"<<endl;
        cin>>c;
        system("cls");
        switch (c)
        {
        case '1':
            cout<<"请输入城市名称\t"<<endl;
            cin>>city.name;
            cout<<"请输入城市代码\t"<<endl;
            cin>>city.code;
            if(g.FindNode(city)==-1)
            {
                if(g.InsertV(city))
                {
                    cout<<"添加成功"<<endl;
                }
            }
            else
            {
                cout<<"城市已存在"<<endl;
            }
            break;
        case '2':
            cout<<"请输入要修改城市名称\t"<<endl;
            cin>>name;
            if(g.Change_City(name))
            {
                cout<<"修改成功"<<endl;
            }
            break;
        case '3':
            cout<<"请输入要删除城市名称\t"<<endl;
            cin>>city.name;
            cout<<"请输入要删除城市代码\t"<<endl;
            cin>>city.code;
            if(g.DeleteV(city));
            break;
        default:
            break;
        }

        break;
    case '2':
        cout<<"增加道路信息请按-------1"<<endl;
        cout<<"修改道路信息请按-------2"<<endl;
        cout<<"删除道路信息请按-------2"<<endl;
        cout<<"返回主菜单请按---------5"<<endl;
        cout<<"退出请按---------------0"<<endl;
        cin>>c;
        switch (c)
        {
        case '1':
            cout<<"请输入起点城市\t"<<endl;
            cin>>city.name;
            city.code=g.FindNode(city.name);
            cout<<"请输入终点城市\t"<<endl;
            cin>>city_.name;
            city_.code=g.FindNode(city_.name);
            cout<<"请输入城市之间路程\t"<<endl;
            cin>>cost;
            g.InsertE(city, city_, cost);
            g.InsertE(city_, city, cost);
            break;
        case '2':
            cout<<"请输入起点城市\t"<<endl;
            cin>>city.name;
            city.code=g.FindNode(city.name);
            cout<<"请输入终点城市\t"<<endl;
            cin>>city_.name;
            city_.code=g.FindNode(city_.name);
            if(g.Change_Edge(city,city_))
            {
                cout<<"修改成功"<<endl;
            }

        case '3':
            cout<<"请输入起点城市\t"<<endl;
            cin>>city.name;
            city.code=g.FindNode(city.name);
            cout<<"请输入终点城市\t"<<endl;
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
    string str="交通咨询系统";
    char filename[]="city_info.txt";  
    g.ReadGraph(filename);
    //g.WriteGraph("test.txt");
    g.Read_Train_Info("shift_info.txt");
    g.Write_Train_Info("test.txt");
    cout<<setiosflags(ios::right)<<setw(45)<<"交通咨询系统"<<endl;
    cout<<setiosflags(ios::right)<<setw(55)<<"顾客查询------------------请按1"<<endl;
    cout<<setiosflags(ios::right)<<setw(55)<<"工作人员------------------请按2"<<endl;
    cout<<setiosflags(ios::right)<<setw(55)<<"退出系统------------------请按0"<<endl;
    cin>>c;
    system("cls");
    switch (c)
    {
    case '1':
        c=Search();
        cout<<"返回请按----0"<<endl;
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
        cout<<"管理火车信息请按--------1"<<endl;
        cout<<"管理城市信息请按--------2"<<endl;
        cout<<"返回主菜单请按----------5"<<endl;
        cout<<"返回请按----------------0"<<endl;
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