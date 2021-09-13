#include<iostream>
#include<list>
#include<queue>
#include<stack>
#include<algorithm>
#include<iostream>
#include<fstream>
#include<istream>
#include"E:\Pool_Birds\Projects_for_C++\heap\heap.h"
using namespace std;

/*将cost看作路程*/
const double MAXCOST=20000;

/*用于作为“图”顶点数据结构，表示城市信息*/
struct PosNode
{
    string name;    //城市名称
    double code;    //城市代码
    bool operator==(PosNode node)
    {
        return(code==node.code);
    }
};

/*班次信息*/
struct ShiftNode
{
    string train_code;          //列车行驶代码
    int start,end;              //起点站，终点站在顶点数组中对应的下标
    string s_time,e_time;       //发车时间与到车时间
    double distance;            //两地之间的距离
};


/*记录边的信息，用于记录道路信息*/
struct PathData
{
    int start,dest;
    double cost;
    /*类型转换函数，隐式转换，可以避免写重载函数的麻烦
    用于与double类型比较，参考网址：https://www.cnblogs.com/dishengAndziyu/p/10914348.html*/
    operator double()const{return cost;}
};


/*边结点，用于记录单向道路信息*/
struct Edgecode
{
    int dest;                                       //终点下标
    double cost;                                    //权值
    operator int(){return dest;}
};

/*说实话，上面两个结点信息有些重复，但是完成了为了复用图的函数，应该增加*/

template<class T>
class Graph
{
    
    T* VA;                                              //顶点数组指针
    list<Edgecode> *HL;                                 //边链表数组指针
    int sizeV, sizeE;                                   //顶点，边的个数
    int maxV;                                           //顶点数组空间长度
    vector<ShiftNode> vec_s;                            //用于储存列车信息；
    double GetCost(int si, int dj)const;                //按起点下标和终点下标读取相应边的权值
public:
    Graph(int n=100):sizeV(0), sizeE(0), maxV(n)        //构造函数
    {
        VA=new T[n];
        HL=new list<Edgecode>[n];
    } 
    ~Graph()
    {
        delete [] VA;
        delete [] HL;
    }
    int Empty()const{return(sizeV);}
    int Full()const{return(sizeV==maxV);}
    int SizeV()const{return(sizeV);}
    int SizeE()const{return(sizeE);}


    double GetCost(const T&v1, const T&v2)const;                //按起点和终点，读取相应边的权值


    int FindNode(const T&v)const;                               //返回相应顶点的下标
    bool FindNode(T &v, int pos);                               //判断相应下标是否存在该顶点
    double FindNode(string name)const;                          //根据相应的结点的城市名返回其对应的代码值
    string FindNode(double code)const;                          //根据相应的结点的代码值返回其对应的城市


    bool InsertV(const T&v);                                    //插入顶点
    bool InsertE(const T&v1, const T&v2, double weigh=MAXCOST);         //插入相应边
    bool DeleteV(const T&v);
    bool DeleteE(const T&v1, const T&v2);
    void ReadGraph(const char *filename);                       //从相应文件中读取图
    void WriteGraph(const char *filename);                      //向相应文件中写入图
    int InDegree(int i)const;                                  //得到结点的入度
    int OutDegree(int i)const;                                 //得到结点的出度
    void Read_Train_Info(const char *filename);                 //从文件中加载列车信息
    void Write_Train_Info(const char *filename);                //向文件中写入列车信息
    void Train_Info_To_Screen();                                //在屏幕上显示班次信息
    


    /*重载输入符*/
    template<class U>
    friend ostream& operator<<(ostream &ostr, const Graph<U>& g);
    /*重载输出符*/
    template<class U>
    friend istream& operator>>(istream &istr, Graph<U> &g);
    


    /*适用于图的堆排序*/
    void BuildHeap(PathData *E, int size)const;
    void PercolateDown(PathData *E, int pos, int size)const;



    /*迪克特斯拉算法，最短路径，源点到其他顶点的最短路径*/
    bool Dijkstra(const T&v, PathData *E, double *D, int *P, int nv)const;
    bool Dijkstra(string name, PathData*E, double *D, int *p, int nv)const;
    bool Dijkstra(double code, PathData*E, double *D, int *p, int nv)const;
    /*一对顶点之间的最短路径*/
    int MinPath(const T&sv, const T&ev, vector<int> &vec)const;
    int MinPath(const string sv, const string ev, vector<int> &vec)const;
    int MinPath(const double sv, const double ev, vector<int> &vec)const;
    /*弗洛伊德算法，最短路径，所有顶点对之间的最短路径*/
    void Floyd(double **P, int **D)const;


    /*打印路径信息*/
    void Print_path(PathData *E, int ne) const; 
    void Print_path(double *D, int *P , int n=10000, int e=10000) const;  
    void Print_path(double **P, int **D, int n=10000 )const;
    void Print_path(double **P, int **D, int s, int v);   


    /*拓扑排序*/
    bool TopSort(int *t,int nv)const;
    bool TopSort(list<T>& l)const;              


    /*打印拓扑排序*/
    bool Print_top(int *t)const;
    bool Print_top(list<int> &l)const;


    /*关键路径*/
    void CriticalPath(double *VE,double *VL,int nv)const;


    /*打印关键路径*/
    void Print_CriticalPath(double *VE, double *VL,int *p=NULL);
    int Get_Top_Index(int*p,int pos)const;

    /* 其他功能 */

    /*检查列车代码是否存在*/
    bool Search_Shifts(string code);  
    /* 修改列车信息 */
    bool Change_Shift(string code);
    /* 增加列车信息 */
    bool Add_Shift(string code);
    /* 修改城市信息 */
    bool Change_City(string name);
    /* 修改道路信息 */
    bool Change_Edge(PosNode &v1, PosNode &v2);
    /* 打印最佳列车信息*/
    void Train(PosNode &v1, PosNode &v2);
};


/*重载输入符*/
template<class T>
istream& operator>>(istream& is, Graph<T>& g)
{
    string s;//char s[50];
    int n;
    int n2;
    double w;
    T v1,v2;
    is>>s>>n;
    for(int i=0;i<n;i++)
    {
        is>>v1;
        g.InsertV(v1);
    }
    is>>s>>n2;
    for(int i=0;i<n2;i++)
    {
        is>>v1>>v2>>w;
        g.InsertE(v1, v2, w);
    }
    return is;
}


/*重载输出符*/
template<class T>
ostream& operator<<(ostream &os,const Graph<T> &g)
{
    os<<"<Verteis>:\t"<<g.sizeV<<endl;
    for(int i=0;i<g.sizeV;i++)
    {
        os<<g.VA[i]<<endl;
    }
    os<<"<Edges>:  \t"<<g.sizeE<<endl;
    for(int i=0;i<g.sizeV;i++)
    {
        //os<<i<<'-'<<g.VA[i].name<<":";
        list<Edgecode >::iterator itr=g.HL[i].begin();
        for(;itr!=g.HL[i].end();itr++)
        {
            os<<g.VA[i]<<' '<<g.VA[(*itr).dest]<<' '<<(*itr).cost<<endl;
        }
    }
    return os;
}

ostream& operator<<(ostream &os,PosNode &node)
{
    os<<node.name<<' '<<"-"<<' '<<node.code;
    return os;
}

istream& operator>>(istream &is,PosNode &node)
{
    static char a;
    is>>node.name>>a>>node.code;
    return is;
}

/*通过元素本身查找元素的下标*/
template<class T>
int Graph<T>::FindNode(const T&v)const
{
    for(int i=0;i<sizeV;i++)
    {
        if(VA[i]==v)
        {
            return i;
        }
    }
    return(-1);
}


/*通过下标查询是否在顶点序列中*/
template<class T>
bool Graph<T>::FindNode(T &v, int pos)
{
    if(pos<0||pos>=sizeV)
    {
        cerr<<"pos illegal"<<endl;
        return(0);
    }
    v=VA[pos];
    return(1);
}


/*通过城市名字寻找结点，并返回其对应的代码值*/
template<class T>
double Graph<T>::FindNode(string name)const
{
    if(name.size()==0)
    {
        return(0);
    }
    for(int i=0;i<sizeV;i++)
    {
        if(VA[i].name==name)
        {
            return VA[i].code;
        }
    }
    return(0);
}


/*通过城市代码寻找结点，并返回其对应的城市名*/
template<class T>
string Graph<T>::FindNode(double code)const
{
    if(code<=0)
    {
        return(0);
    }
    for(int i=0;i<sizeV;i++)
    {
        if(VA[i].code==code)
        {
            return VA[i].name;
        }
    }
    return(0);
}


/*插入结点*/
template<class T>
bool Graph<T>::InsertV(const T&v)
{
    if(sizeV>=maxV)
    {
        cerr<<"space full"<<endl;
        return 0;
    }
    VA[sizeV]=v;
    sizeV++;
    return(1);
}


/*???????*/
template<class T>
bool Graph<T>::InsertE(const T&v1, const T&v2, double w)
{
    int si, dj;                                         //si??????dj??????
    si=FindNode(v1);
    dj=FindNode(v2);
    if(si==-1||dj==-1||si==dj)
    {
        cerr<<"Insert Edgecode Fault"<<endl;
        return(0);
    }
    Edgecode e;
    e.dest=dj;
    e.cost=w;
    HL[si].push_back(e);
    sizeE++;
    return 1;
}


/*得到权值*/
template<class T>
double Graph<T>::GetCost(int si, int dj)const
{
    if(si<0||si>=sizeV||dj<0||dj>=sizeV)
    {
        cout<<"si or dj illegal"<<endl;
        return(0);
    }
    list<Edgecode>::iterator itr=HL[si].begin();
    for(;itr!=HL[si].end();itr++)
    {
        if((*itr).dest==dj)
        {
            return (*itr).cost;
        }
    }
    //cout<<"cannnot find cost "<<endl;
    return(0);
}


/*得到权值*/
template<class T>
double Graph<T>::GetCost(const T&v1, const T&v2)const
{
    int si, dj;                                         //si??????dj??????
    si=FindNode(v1);
    dj=FindNode(v2);
    if(si==-1||dj==-1)
    {
        cerr<<"GET COST FALIURE"<<endl;
        return(0);
    }
    list<Edgecode>::iterator itr=HL[si].begin();
    for(;itr!=HL[si].end();itr++)
    {
        if((*itr).dest==dj)
        {
            return (*itr).cost;
        }

    }
    cerr<<"GET COST FALIURE"<<endl;
    return(0);
}

/*删除顶点*/
template<class T>
bool Graph<T>::DeleteV(const T&v)
{
    int si=FindNode(v);
    if(si==-1)
    {
        cout<<"Cannot find the vertex"<<endl;
        return 0;
    }
    int size=HL[si].size();
    for(int i=si; i<sizeV-1; i++)
    {
        VA[i]=VA[i+1];
        HL[i]=HL[i+1];
    }
    sizeV--;
    HL[sizeV].clear();
    sizeE=sizeE-size;
    list<Edgecode>::iterator itr;
    for(int i=0;i<sizeV;i++)
    {
        for(itr=HL[i].begin(); itr!=HL[i].end(); itr++)
        {
            if((*itr).dest==si)
            {
                HL[i].erase(itr);
                sizeE--;
                break;
            }
        }
    }
    for(int i=0;i<sizeV;i++)
    {
        for(itr=HL[i].begin(); itr!=HL[i].end(); itr++)
        {
            if((*itr).dest>si)
            {
                (*itr).dest--;
            }
        }
    }
    cout<<"Delete Success"<<endl;
    return 1;
}


//删除其中一个结点
template<class T>
bool Graph<T>::DeleteE(const T&v1, const T&v2)
{
    int si=FindNode(v1);
    int dj=FindNode(v2);
    if(si==-1||dj==-1||si==dj)
    {
        cerr<<"Insert Edgecode Fault"<<endl;
        return(0);
    }
    list<Edgecode>::iterator itr;
    for(itr=HL[si].begin();itr!=HL[si].end();itr++)
    {
        if((*itr).dest==dj)
        {
            HL[si].erase(itr);
            sizeE--;
            return(1);
        }
    }
    return(0);
}


//读取内容
template<class T>
void Graph<T>::ReadGraph(const char *filename)
{
    ifstream is(filename, ios_base::in);
    if(!is)
    {
        cout<<"cannot open file to read\n";
        exit(1);
    }
    
    is>>(*this);
    is.close();
}


//将内容输出
template<class T>
void Graph<T>::WriteGraph(const char *filename)
{
    ofstream os(filename/* , ios_base::out */);
    if(!os)
    {
        cout<<"cannot open file to write\n";
        exit(1);
    }
    
    os<<(*this);
    os.close();
}     


template<class T>
void Graph<T>::Read_Train_Info(const char *filename)
{
    ifstream is(filename);
    if(!is)
    {
        cout<<"cannot open train_info.txt to read"<<endl;
        exit(1);
    }
    string start,end;
    string notice;
    ShiftNode item;
    PosNode item_p;
    double item_d;
    int size;
    is>>notice;
    is>>size;
    for(int i=0;i<size;i++)
    {
        is>>item.train_code;
        is>>start>>end;
        item_p.name=start;
        item_p.code=FindNode(item_p.name);
        item.start=FindNode(item_p);
        item_p.name=end;
        item_p.code=FindNode(item_p.name);
        item.end=FindNode(item_p);
        is>>item.s_time>>item.e_time;
        vec_s.push_back(item);  
    }
}


template<class T>
void Graph<T>::Write_Train_Info(const char* filename)
{
    ofstream os(filename);
    
    if(!os)
    {
        cout<<"cannot open train_info.txt to write"<<endl;
        exit(1);
    }
    string notice="<shifts_num>";
    vector<ShiftNode>::iterator itr=vec_s.begin();
    os<<notice<<'\t'<<vec_s.size()<<endl;
    for(;itr!=vec_s.end();itr++)
    {
        os<<(*itr).train_code<<' '
        <<VA[(*itr).start].name<<' '
        <<VA[(*itr).end].name<<' '
        <<(*itr).s_time<<' '
        <<(*itr).e_time;
        os<<endl;
    }
}

template<class T>
void Graph<T>::Train_Info_To_Screen()
{
    ostream &os=cout;
    if(!os)
    {
        cout<<"cannot open train_info.txt to write"<<endl;
        exit(1);
    }
    string notice="列车列表";
    vector<ShiftNode>::iterator itr=vec_s.begin();
    os<<notice<<'\t'<<vec_s.size()<<endl;
    for(;itr!=vec_s.end();itr++)
    {
        os<<(*itr).train_code<<' '
        <<VA[(*itr).start]<<' '
        <<VA[(*itr).end]<<' '
        <<(*itr).s_time<<' '
        <<(*itr).e_time;
        os<<endl;
    }
}

/*建堆*/
template<class T>
void Graph<T>::BuildHeap(PathData *E, int size)const
{
    for(int i=size/2-1;i>=0;i--)
    {
        PercolateDown(E,i,size);
    }
}


/*向下调整为堆，第一个元素为最小值*/
template<class T>
void Graph<T>::PercolateDown(PathData *E, int pos, int size)const
{
    int p=pos;
    int c=p*2+1;
    PathData temp=E[pos];
    while(c<size)
    {
        if(E[c]>E[c+1]&&(c+1)<size)
        {
            c++;
        }
        if(temp>E[c])
        {
            E[p]=E[c];
            p=c;
            c=2*p+1;
        }
        else
        {
            break;
        }    
    }
    E[p]=temp;
}


/*用于求给定源点到其他顶点的最短路径*/
template<class T>
bool Graph<T>::Dijkstra(const T&v, PathData *E, double *P, int *D, int nv)const
{
    int i,s,j;
    double cost;
    int ns;
    int id=0;
    int count=0;
    int ne=nv-1;
    PathData temp;
    s=FindNode(v);
    if(s==-1||s>sizeV)
    {
        cerr<<"Cannot Prim because of fault \"vertiex\""<<endl;
        return(0);
    }
    P[s]=0;
    D[s]=-1;
    for(i=0;i<=ne;i++)
    {
        if(i!=s)
        {
            temp.start=s;
            temp.dest=i;
            cost=GetCost(s,i);
            temp.cost=(cost==0?MAXCOST:cost);
            E[id++]=temp;
            P[i]=cost;
            D[i]=(cost==0?-1:s);
        }
    }
    BuildHeap(E, ne);
    for(i=0;i<ne;i++)
    {
        if(E[0]<MAXCOST)
        {
            count++;
        }
        ns=E[0].dest;
        for(j=1;j<ne-i;j++)
        {
            cost=GetCost(ns,E[j].dest);
            cost=(cost==0?MAXCOST:cost);
            if(E[j]>(E[0].cost+cost))
            {
                E[j].cost=E[0].cost+cost;
                E[j].start=ns;
                P[E[j].dest]=E[0].cost+cost;
                D[E[j].dest]=ns;
            }
        }
        temp=E[0];
        E[0]=E[ne-i-1];
        E[ne-i-1]=temp;
        PercolateDown(E, 0, ne-i-1);
    }
    return (count==ne?1:0);
}

template<class T>
bool Graph<T>::Dijkstra(string name, PathData*E, double *D, int *p, int nv)const
{
    T v;
    v.name=name;
    v.code=FindNode(name);
    return Dijkstra(v,E,D,p,nv);
}

template<class T>
bool Graph<T>::Dijkstra(double code, PathData*E, double *D, int *p, int nv)const
{
    T v;
    v.code=code;
    v.name=FindNode(code);
    return Dijkstra(v,E,D,p,nv);
}

/*用于搜索所有顶点对之间的最短路径*/
template<class T>
void Graph<T>::Floyd(double **D, int **P)const
{
    int v,w,k;
    double cost;
    for(v=0;v<sizeV;v++)
    {
        for(w=0;w<sizeV;w++)
        {
            cost=GetCost(v,w);
            cost=(cost==0?MAXCOST:cost);
            D[v][w]=cost;
            P[v][w]=w;
        }
    }
    for(k=0;k<sizeV;k++)
    {
        for(v=0;v<sizeV;v++)
        {    
            for(w=0;w<sizeV;w++)
            {
                if(D[v][w]>D[v][k]+D[k][w])
                {
                    D[v][w]=D[v][k]+D[k][w];
                    P[v][w]=P[v][k];
                }
            }
        }
    }
    /* for(v=0;v<sizeV;v++)
    {
        for(w=v+1;w<sizeV;w++)
        {
            cout<<v<<"--"<<w<<" "<<""<<D[v][w];
            cout<<" path:"<<v;
            k=P[v][w];
            while(k!=w)
            {
                cout<<"->"<<k;
                k=P[k][w];
            }
            cout<<"->"<<w<<endl;
        }
        cout<<endl;
    } */
}


/*打印路径从pathdata数据结构中打印数据*/
template<class T>
void Graph<T>::Print_path(PathData *E, int ne) const
{
    if(ne>sizeV)
    {
        cout<<"Cannot pahtdat because of \"ne\""<<endl;
        return;
    }
    int size=ne;
    for(int i=size-1;i>=0;i--)
    {
        cout<<'('<<VA[E[i].start]<<" , "<<VA[E[i].dest]<<" , "<<E[i].cost<<")  "<<endl;;
    }
}


/*打印边结点信息*/
template<class T>
void Graph<T>::Print_path(double *P, int *p, int s, int e)const
{
    int size=sizeV;
    int j,r;
    for(int i=0;i<sizeV;i++)
    {
        if(p[i]==-1)
        {
            r=i;
        }
    }
    if(s<1000||e<1000)
    {
        if(p[s]!=-1)
        {
            cout<<P[s]<<":\t"<<VA[s].name;
            j=s;
            while(p[j]!=-1)
            {
                cout<<" -> "<<VA[j].name;
                j=p[j];
            }
            cout<<endl;
        }
    }
    for(int i=0;i<sizeV;i++)
    {
        if(p[i]!=-1)
        {
            cout<<P[i]<<":\t"<<VA[r].name;
            j=i;
            while(p[j]!=-1)
            {
                cout<<" -> "<<VA[j].name;
                j=p[j];
            }
            cout<<endl;
        }
    }
}

template<class T>
void Graph<T>::Print_path(double **D, int **P, int i, int j)
{
    double cost;
    cost=D[i][j];
    cout<<VA[i].name<<" -- "<<VA[j].name<<" : "<<cost<<"km";
    cout<<"费用："<<(cost/100)*39<<" 元"<<":\t"<<VA[i].name;
    while(P[i][j]!=j)
    {
        cout<<" -> "<<VA[P[i][j] ].name;
        i=P[i][j];
    }
    cout<<" -> "<<VA[j].name<<endl;
}

template<class T>
void Graph<T>::Print_path(double **D, int **P, int n)const
{ 
    int i,j;
    double cost;
    int temp;
    if(n>sizeV)
    {
        for(i=0;i<sizeV;i++)
        {
            temp=i;
            cout<<"The \'"<<VA[i]<<'\''<<" to others vertices"<<endl;
            for(j=0;j<sizeV;j++)
            {
                if(i==j)
                {
                    continue;
                }
                cost=D[i][j];
                cout<<VA[i].name<<" -- "<<VA[j].name<<" : "<<cost<<":\t"<<VA[i].name;
                while(P[i][j]!=j)
                {
                    cout<<" -> "<<VA[P[i][j] ].name;
                    i=P[i][j];
                }
                i=temp;
                cout<<" -> "<<VA[j].name<<endl;
            }
        }
    }
    else
    {
        i=n;
        temp=i;
        cout<<"The \'"<<VA[i]<<'\''<<" to others vertices"<<endl;
        for(j=0;j<sizeV;j++)
        {
            cost=D[i][j];
            cout<<VA[i].name<<"--"<<VA[j].name<<" : "<<cost<<":\t"<<VA[i].name;
            while(P[i][j]!=i)
            {
                cout<<" -> "<<VA[P[i][j] ].name;
                i=P[i][j];
            }
            cout<<" -> "<<VA[j].name<<endl;
            i=temp;
        }
    }
}


/*????????*/
template<class T>
bool Graph<T>::TopSort(int *t,int nv)const
{
    int i,j,id;
    int *ID=new int [nv];
    queue<int> Q;
    for(i=0;i<nv;i++)
    {
        ID[i]=InDegree(i);
        if(ID[i]==0)
        {
            Q.push(i);
        }
    }
    list<Edgecode>::iterator itr;
    id=0;
    while(!Q.empty())
    {
        i=Q.front();
        Q.pop();
        t[id++]=i;
        itr=HL[i].begin();
        for(;itr!=HL[i].end();itr++)
        {
            j=(*itr).dest;
            ID[j]--;
            if(ID[j]==0)
            {
                Q.push(j);
            }
        }
    }
    delete [] ID;
    if(id==nv)
    {
        return 1;
    }
    return 0;
}


/*???????????*/
template<class T>
bool Graph<T>::Print_top(int *t)const
{
    if(t==NULL)
    {
        cout<<"Cannot Print Top_Sort Because Of Adress NULL"<<endl;
        return 0;
    }
    int i=0;
    cout<<VA[t[i]];
    i++;
    for(;i<sizeV;i++)
    {
        cout<<"->"<<VA[t[i]];
    }
    cout<<endl;
    return 1;
}


/*一个函数的入度*/
template<class T>
int Graph<T>::InDegree(int n)const
{
    if(n>sizeV||n<0)
    {
        cout<<"Cannot output indegree becaue of fault \'n\'"<<endl;
        return 0;
    }
    int i,j;
    int count=0;
    j=i=0;
    list<Edgecode>::iterator itr;
    for(i=0;i<sizeV;i++)
    {
        itr=HL[i].begin();
        for(;itr!=HL[i].end();itr++)
        {
            if((*itr).dest==n)
            {
                count++;
            }
        }
    }
    return count;
}     


/*输出顶点的出度*/
template<class T>
int Graph<T>::OutDegree(int n)const
{
    if(n>sizeV||n<0)
    {
        cout<<"Cannot output outdegree becaue of fault \'n\'"<<endl;
        return 0;
    }
    list<Edgecode>::iterator itr=HL[n].begin();
    int count=0;
    for(;itr!=HL[n].end();itr++)
    {
        count++;
    }
    return count;
}


/*???·????VE?????????緢?????VL???????????????*/
template<class T>
void Graph<T>::CriticalPath(double *VE,double *VL,int nv)const
{
    if(nv>sizeV||nv<0)
    {
        cout<<"Cannot CrticalPath Because Of Fault \"nv\""<<endl;
        return ;
    }
    int i,j,k;
    double min,max,cost;
    min=max=0;
    int *top=new int(sizeV);
    if(TopSort(top, sizeV))
    {
        VE[top[0]]=0;
        for(k=1;k<sizeV;k++)
        {
            max=0;
            j=top[k];
            for(i=0;i<sizeV;i++)
            {
                cost=GetCost(i,j);
                if(cost!=0&&(VE[i]+cost)>max)
                {
                    max=VE[i]+cost;
                }
            }
            VE[j]=max;
        }
        VL[top[sizeV-1]]=VE[top[sizeV-1]];
        for(k=sizeV-2;k>=0;k--)
        {
            min=MAXCOST;
            i=top[k];
            for(j=sizeV-1;j>=0;j--)
            {
                cost=GetCost(i,j);
                if(cost!=0&&(VL[j]-cost)<min)
                {
                    min=VL[j]-cost;
                }
            }
            VL[i]=min;
        }
    }

}


template<class T>
int Graph<T>::Get_Top_Index(int*top,int pos)const
{
    if(pos>=sizeV||pos<0)
    {
        cout<<"Cannot get index"<<endl;
        return -1;
    }
    for(int i=0;i<sizeV;i++)
    {
        if(top[i]==pos)
        {
            return i;
        }
    }
    return -1;
}


/*??????·??*/
template<class T>
void Graph<T>::Print_CriticalPath(double *VE, double *VL,int *top)
{
    if(VE==NULL||VL==NULL)
    {
        cout<<"Cannot print because of address NULL"<<endl;
        return;
    }
    int i,j;
    int d;
    queue<int> q;
    vector<int> vec;
    vec.push_back(0);
    q.push(top[0]);
    cout<<"The earliest time:\t"<<endl;
    for(i=0;i<sizeV;i++)
    {
        cout<<"ve( "<<top[i]<<" )"<<":"<<VE[top[i]]<<endl;
    }
    cout<<"The latest time:"<<endl;
    for(i=0;i<sizeV;i++)
    {
        cout<<"ve( "<<top[i]<<" )"<<":"<<VL[top[i]]<<endl;
    }
    T vi,vj;
    for(j=0;j<sizeV;j++)
    {
        for(i=0;i<sizeV;i++)
        {
            FindNode(vj,j);
            FindNode(vi,i);
            if(GetCost(i,j)!=0)
            {
                cout<<"<"<<vi<<","<<vj<<">"<<"----"<<
                VL[j]-VE[i]-GetCost(i,j)<<endl;
                if((VL[j]-VE[i]-GetCost(i,j))==0)
                {
                    if((d=Get_Top_Index(top,j))!=-1)
                    {
                        vec.push_back(d);
                    }
                }
            }
        }
    }
    
    sort(vec.begin(),vec.end());
    vector<int>::iterator itr=vec.begin();
    cout<<"The Criticalpath is:\n";
    cout<<top[(*itr)];
    itr++;
    for(;itr!=vec.end();itr++)
    {
        cout<<"--"<<top[*itr];
    }
    cout<<endl;
}


/*一对顶点之间的最短路径*/
template<class T>
int Graph<T>::MinPath(const T &sv, const T &ev, vector<int> &vec)const
{
    int si=FindNode(sv),id=FindNode(ev),dj=FindNode(ev);
    if(si==-1||dj==-1)
    {
        return -1;
    }
    bool *visted=new bool[SizeV()];
    for(int i=0;i<SizeV();i++)
    {
        /*并查集，已经查找过的元素设为的值为“1”*/
        visted[i]=0;
    }
    double mincost,cost;
    Heap<PathData> PQ;
    PathData item;
    item.start=si;
    item.dest=si;
    item.cost=0;
    PQ.Insert(item);
    vec.push_back(si);
    while (!PQ.Empty())
    {
        PQ.DeleteMin(item);
        dj=item.dest;
        mincost=item.cost;
        vec.push_back(dj);
        if(dj==id)
        {
            break;
        }
        if(visted[dj]==0)
        {
            visted[dj]=1;
            si=dj;
            for(dj=0;dj<SizeV();dj++)
            {
                cost=GetCost(si,dj);
                if(cost!=0&&visted[dj]==0)          //此处检验visited[dj]==0，是为了防止往回走，往回走是没有意义的
                {
                    item.dest=dj;
                    item.start=si;
                    item.cost=mincost+cost;
                    PQ.Insert(item);
                }
            }
        }
    }
    if(dj==id)
    {
        return mincost;
    }
    return 1;
}


template<class T>
int Graph<T>::MinPath(const string sv,const string ev, vector<int> &vec)const
{
    T v1,v2;
    v1.name=sv;
    v2.name=ev;
    v1.code=FindNode(sv);
    v2.code=FindNode(ev);
    return MinPath(v1,v2,vec);
}


template<class T>
int Graph<T>::MinPath(const double sv, const double ev, vector<int> &vec)const
{
    T v1,v2;
    v1.code=sv;
    v2.code=ev;
    v1.name=FindNode(sv);
    v2.name=FindNode(ev);
    return MinPath(v1,v2,vec);
}


template<class T>
bool Graph<T>::Search_Shifts(string code)
{
    vector<ShiftNode>::iterator itr=vec_s.begin();
    for(;itr!=vec_s.end();itr++)
    {
        if(code==(*itr).train_code)
        {
            return true;
        }
    }
    return false;
}

template<class T>
void Graph<T>::Train(PosNode &v1, PosNode &v2)
{
    
}

template<class T>
bool Graph<T>::Change_Shift(string code)
{
    string item;
    char c;
    PosNode temp;
    vector<ShiftNode>::iterator itr=vec_s.begin();
    for(;itr!=vec_s.end();itr++)
    {
        if(code==(*itr).train_code)
        {
            cout<<"修改列车代码请按-------1"<<endl;
            cout<<"修改始发站请按---------2"<<endl;
            cout<<"修改终点站请按---------3"<<endl;
            cout<<"修改发车时间请按-------4"<<endl;
            cout<<"修改到车时间请按-------5"<<endl;
            cout<<"按其他键退出"<<endl;
            cin>>c;
            switch (c)
            {
            case '1':
                cout<<"请输入新的列车代码\t";
                cin>>item;
                (*itr).train_code=item;
                break;
            case '2':
                cout<<"请输入新的始发站城市名称\t";
                cin>>temp.name;
                temp.code=FindNode(temp.name);
                (*itr).start=FindNode(temp);
                break;
            case '3':
                cout<<"请输入新的终点站城市名称\t";
                cin>>temp.name;
                temp.code=FindNode(temp.name);
                (*itr).end=FindNode(temp); 
                break; 
            case '4':
                cout<<"请输入新的发车时间\t";
                cin>>item;
                (*itr).s_time=item;
                break;
            case '5':
                cout<<"请输入新的到车时间\t";
                cin>>item;
                (*itr).e_time=item;
                break;
            default:
                break;
            }
            return true;
        }
    }
    return false;
}


template<class T>
bool Graph<T>::Add_Shift(string code)
{
    ShiftNode item;
    PosNode p;
    item.train_code=code;
    cout<<"请输入新的始发站城市名称\t";
    cin>>p.name;
    p.code=FindNode(p.name);
    item.start=FindNode(p);
    cout<<"请输入新的终点站城市名称\t";
    cin>>p.name;
    p.code=FindNode(p.name);
    item.end=FindNode(p);
    cout<<"请输入新的发车时间\t";
    cin>>item.s_time;
    cout<<"请输入新的到车时间\t";
    cin>>item.e_time;
    return true;
}

template<class T>
bool Graph<T>::Change_City(string name)
{
    PosNode pos;
    pos.name=name;
    pos.code=FindNode(name);
    int p=FindNode(pos);
    if(p==-1)
    {
        cout<<"该城市不存在"<<endl;
        return false;
    }
    cout<<"请输入新的城市名称\t";
    cin>>VA[p].name;
    cout<<"请输入新的城市代码\t";
    cin>>VA[p].code;
    return true;
}

template<class T>
bool Graph<T>::Change_Edge(PosNode &v1, PosNode &v2)
{
    char c;
    double cost;
    cout<<"修改道路起点城市请按--------1"<<endl;
    cout<<"修改道路终点城市请按--------2"<<endl;
    cout<<"修改道路城市间距离请按-------3"<<endl;
    cout<<"退出请按--------------------0"<<endl;
    DeleteE(v1,v2);
    DeleteE(v2,v1);
    switch (c)
    {
    case '1':
        cout<<"请输入新的起点城市名称\t";
        cin>>v1.name;
        break;
    case '2':
        cout<<"请输入新的起点城市名称\t";
        cin>>v2.name;
        break;
    case '3':
        cout<<"请输入新的道路里程\t";
        cin>>cost;
        break;
    default:
        break;
    }
    InsertE(v1,v2,cost);
    InsertE(v2,v1,cost);
    return true;
}