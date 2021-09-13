#include<iostream>
#include<fstream>
#include<istream>
#include"E:\Pool_Birds\Projects_for_C++\heap\heap.h"
#include<queue>
#include<stack>
#include<list>
#include"graph.h"
using namespace std;


/*根据顶点元素，返回相应结点，若没有对应结点，这返回-1*/
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


/*返回相应下标的结点*/
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


/*插入顶点至数组尾*/
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


/*插入边结点*/
template<class T>
bool Graph<T>::InsertE(const T&v1, const T&v2, double w)
{
    int si, dj;                                         //si为边始点，dj为边终点
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


/*私有函数，通过边的两个结点的下标获得权，出错则返回0*/
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


/*公有函数，通过边的两个结点获得权，出错则返回0*/
template<class T>
double Graph<T>::GetCost(const T&v1, const T&v2)const
{
    int si, dj;                                         //si为边始点，dj为边终点
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
    /*遍历所有边，删除所有与si顶点连接的顶点*/
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
    /*遍历所有边，使dest大于si的边，统统减一*/
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


//从相应文件中读取图
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


//向相应文件中写入图
template<class T>
void Graph<T>::WriteGraph(const char *filename)
{
    ofstream os(filename, ios_base::out);
    if(!os)
    {
        cout<<"cannot open file to write\n";
        exit(1);
    }
    os<<(*this);
    os.close();
}     


/*广度遍历*/
template<class T>
void Graph<T>::BFS_nrec(list<T> &ls)const
{
    bool *visted= new bool[sizeV];
    for(int i=0; i<sizeV; i++)
    {
        visted[i]=0;
    }
    for(int i=0; i<sizeV; i++)
    {
        if(visted[i]==0)
        {
            BFS_nrec(ls, i, visted);
        }
    }
    delete [] visted;
}


template<class T>
void Graph<T>::BFS_nrec(list<T> &ls, int pos, bool *visited)const
{
    if(pos<0||pos>sizeV)
    {
        return;
    }
    queue<int> q;
    q.push(pos);
    visited[pos]=1;
    list<Edgecode>::iterator itr;
    while(!q.empty())
    {
        pos=q.front();
        q.pop();
        ls.push_back(VA[pos]);
        itr=HL[pos].begin();
        for(;itr!=HL[pos].end();itr++)
        {
            if(visited[(*itr).dest]==0)
            {
                q.push((*itr).dest);
                visited[(*itr).dest]=1;
            }
        }
    }
}

template<class T>
void Graph<T>::BFS(list<T> &L, const T&v)
{
    int pos=FindNode(v);
    if(v==-1)
    {
        return;
    }
    bool *visited=new bool[Sizev];
    for(int i=0;i<sizev;i++)
        visited[i]=0;
    queue<int> q;
    q.push(pos);
    visited[pos]=1;
    list<Edgecode>::iterator first,end;
    while(!q.empty())
    {
        pos=q.pop();
        L.push_back(pos);
        first=HL[pos].begin();
        end=HL[pos].end();
        for(;first!=end;first++)
        {
            if(visited[(*first).dest]==0)
            {
                q.push_back((*first).dest);
                visited[(*first).dest];
            }
        }
    }
    delete [] visited;
}

/*广度遍历的递归算法不存在，除非修改数据结构*/
template<class T>
void Graph<T>::DFS_rec(list<T>&l, int pos, bool *visited)
{
    if(pos<0||pos>=sizev)
    {
        return;
    }
    l.push_back(VA[pos]);
    visited[pos]=1;
    list<Edgecode>::iterator first,end;
    first=HL[pos].begin();
    end=HL[pos].end();
    for(;first!=end;first++)
    {
        if(visited[(*first).dest]==0)
        {
            DFS(L,(*first).dest,visited);
        }
    }
}

/*输出列表*/
void Display_ls(list<char> ls)
{    list<char>::iterator itr=ls.begin();
    for(;itr!=ls.end();itr++)
    {
        cout<<(*itr)<<"  ";
    }
    cout<<endl;
}


/*深度优先遍历*/
template<class T>
void Graph<T>::DFS_rec(list<T> &ls)const
{
    bool *visted= new bool[sizeV];
    for(int i=0; i<sizeV; i++)
    {
        visted[i]=0;
    }
    for(int i=0; i<sizeV; i++)
    {
        if(visted[i]==0)
        {
            DFS_rec(ls, i, visted);
        }
    }
    delete [] visted;
}


template<class T>
void Graph<T>::DFS_rec(list<T> &ls, int pos, bool *visited)const
{
    if(pos<0||pos>sizeV)
    {
        return;
    }
    visited[pos]=1;
    list<Edgecode>::iterator itr;
    ls.push_back(VA[pos]);
    for(itr=HL[pos].begin();itr!=HL[pos].end();itr++)
    {
        if(visited[(*itr).dest]==0)
        {
            DFS_rec(ls, (*itr).dest, visited);
        }
    }
}


template<class T>
void Graph<T>::DFS_nrec(list<T> &ls)const
{
    
    bool *visted= new bool[sizeV];
    for(int i=0; i<sizeV; i++)
    {
        visted[i]=0;
    }
    for(int i=0; i<sizeV; i++)
    {
        if(visted[i]==0)
        {
            DFS_nrec(ls, i, visted);
        }
    }
    delete [] visted;
}


template<class T>
void Graph<T>::DFS_nrec(list<T> &ls, int pos, bool *visited)const
{
    if(pos<0||pos>sizeV)
    {
        return;
    }
    stack<int> s;
    s.push(pos);
    visited[pos]=1;
    list<Edgecode>::iterator itr;
    while(!s.empty())
    {
        pos=s.top();
        s.pop();
        ls.push_back(VA[pos]);
        for(itr=HL[pos].end();itr!=HL[pos].begin();itr--)
        {
            if(visited[(*itr).dest]==0)
            {
                visited[(*itr).dest]=1;
                s.push((*itr).dest);
            }
        }
        if(visited[(*itr).dest]==0)
            {
                visited[(*itr).dest]=1;
                s.push((*itr).dest);
            }
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


/*向下的堆排序*/
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


/*普里姆算法，最小生成树，用pathdata存储最短路径信息*/
template<class T>
bool Graph<T>::Prim(const T&v, PathData* E, int ne)const
{
    int i,s,j;
    double cost;
    int ns;
    PathData temp;
    s=FindNode(v);
    if(s==-1||s>sizeV)
    {
        cerr<<"Cannot Prim because of fault T"<<endl;
        return(0);
    }
    PathData item;
    int id=0;
    for(i=0;i<=ne;i++)
    {
        //是小于等于ne的原因是，要保证最后一个元素的相关
        if(i!=s)
        {
            /*将s的所有边加入候选边*/
            item.start=s;
            item.dest=i;
            cost=GetCost(s, i);
            item.cost=(cost==0?MAXCOST:cost);
            E[id++]=item;
        }
    }
    int count=0;
    BuildHeap(E, ne);                  //建堆以取得最小的权
    for(i=0;i<ne;i++)
    {
        if(E[0]<MAXCOST)
        {
            count++;
        }
        ns=E[0].dest;
        for(j=1;j<ne-i;j++)
        {
            cost=GetCost(ns, E[j].dest);
            cost=(cost==0?MAXCOST:cost);
            if(E[j]>cost)
            {
                E[j].start=ns;
                E[j].cost=cost;
            }
        }
        temp=E[0];
        E[0]=E[ne-1-i];
        E[ne-1-i]=temp;
        PercolateDown(E, 0, ne-i-1);
    }
    return (count==ne?1:0); 
}


/*克鲁斯卡算法，将最小生成树信息储存到Pathdata中*/
template<class T>
bool Graph<T>::Kruskal(PathData *E, int ne)const
{
    Heap<PathData> H;
    PathData temp;
    int *DS=new int[sizeV];
    if(ne>sizeV)
    {
        cout<<"Cannot Kruskal because of \"ne\""<<endl;
        return 0;
    }
    int i,j;
    for(i=0;i<sizeV;i++)
    {
        DS[i]=-1;
    }
    list<Edgecode>::iterator itr;
    for(i=0;i<sizeV;i++)
    {
        itr=HL[i].begin();
        for(;itr!=HL[i].end();itr++)
        {
            temp.start=i;
            temp.dest=(*itr).dest;
            temp.cost=(*itr).cost;
            H.Insert(temp);
        }
    }
    int id=0;
    while(!H.Empty())
    {
        /*i,j用于储存根的下标*/
        H.DeleteMin(temp);
        i=temp.start;
        /*下列是该算法精髓之处*/
        while(DS[i]>=0)
        {
            i=DS[i];
        }
        j=temp.dest;
        while(DS[j]>=0)
        {
            j=DS[j];
        }
        if(i!=j)
        {
            if(i<j)
            {
                DS[i]+=DS[j];
                DS[j]=i;
            }
            else
            {
                DS[j]+=DS[i];
                DS[i]=j;
            }
            E[id++]=temp;
        }
    }
    delete [] DS;
    return(id==ne?1:0);
}


/*迪克特斯拉算法，最短路径，用double *P，与int *D存储信息*/
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


/*弗洛伊德算法，最短路径，将最短路径信息储存到二维数组D，与P中*/
template<class T>
void Graph<T>::Floyd(double **D, int **P)const
{
    /*D用来存放各个权值的和，P用来存放每个顶点经过什么顶点的信息*/
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
    for(v=0;v<sizeV;v++)
    {
        for(w=v+1;w<sizeV;w++)
        {
            cout<<v<<"--"<<w<<" "<<"weight"<<D[v][w];
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
    }

}


/*打印路径信息*/
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


template<class T>
void Graph<T>::Print_path(double *P, int *p)const
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
    for(int i=0;i<sizeV;i++)
    {
        if(p[i]!=-1)
        {
            cout<<P[i]<<":\t"<<VA[r];
            j=i;
            while(p[j]!=-1)
            {
                cout<<"->"<<VA[j];
                j=p[j];
            }
            cout<<endl;
        }
    }
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
                cout<<i<<"--"<<j<<" : "<<cost<<":\t"<<i;
                /*这个位置有问题*/
                while(P[i][j]!=j)
                {
                    cout<<"->"<<P[i][j];
                    i=P[i][j];
                }
                i=temp;
                cout<<"->"<<j<<endl;
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
            cout<<i<<"--"<<j<<" : "<<cost<<":\t"<<i;
            while(P[i][j]!=i)
            {
                cout<<"->"<<P[i][j];
                i=P[i][j];
            }
            cout<<"->"<<j<<endl;
            i=temp;
        }
    }
}


/*拓扑排序*/
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


/*打印拓扑排序*/
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


/*根据下标，得到结点的入度*/
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


/*根据下标，得到该结点的出度*/
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


/*关键路径，VE用于存放最早发生时间，VL用于存放最迟发生时间*/
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


/*打印关键路径*/
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
                    /*打印路径信息*/
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


int main()
{
    
    Graph<char> g;
    list<char> ls;
    char filename[]={"graph_test_5.txt"};   
    g.ReadGraph(filename);
    int *p=new int[g.SizeV()];
    double *d=new double[g.SizeV()];
    int size=g.SizeV();
    // size=g.SizeV();
    // cout<<g;
    // g.DeleteV('C');
    // g.DFS_nrec(ls);
    // Display_ls(ls);
    double **p_=new double*[size];
    int **d_=new int*[size];
    double *VE=new double [size];
    double *VL=new double [size];
    // for(int i=0;i<size;i++)
    // {
    //     p_[i]=new double[size];
    //     d_[i]=new int[size];
    // }
    // for(int i=0;i<g.SizeV();i++)
    // {
    //     p[i]=-1;
    // }
    // cout<<g;
    // cout<<"indegree:\t"<<g.InDegree(0)<<endl;
    // cout<<"outdegree:\t"<<g.OutDegree(0)<<endl;
    cout<<g;
    if(g.TopSort(p, g.SizeV()))
    {
        cout<<"TopSort:"<<endl;
        g.Print_top(p);
    }
    cout<<"<<<<<<<<<<<<<<<"<<endl;
    g.CriticalPath(VE,VL,size);
    g.Print_CriticalPath(VE,VL,p);
    // g.InsertV('a');
    // g.InsertV('b');
    // g.InsertV('c');
    // g.InsertE('a', 'b', 100);
    // cout<<g;
    // cout<<g.Getcost('a', 'b');
    PathData *E=new PathData[g.SizeV()-1];
    //cout<<g;
    // if(g.Prim('A',E,g.SizeV()-1))
    // {
    //     cout<<"Prim: "<<endl;
    //     g.Print_path(E,g.SizeV()-1);
    // }
    // if(g.Kruskal(E, g.SizeV()-1))
    // {
    //     cout<<"Kruskal:"<<endl;
    //     g.Print_path(E,g.SizeV()-1);
    // }
    // if(g.Dijkstra('A',E,d,p,g.SizeV()))
    // {
    //     cout<<"Djkstra: "<<endl;
    //     g.Print_path(d,p);
    //     g.Print_path(E,g.SizeV()-1);
    // }
    // g.Floyd(p_,d_);
    // g.Print_path(p_,d_);
    //g.DFS_rec(ls);
    //Display_ls(ls);
    //ls.clear();
    //g.DFS_nrec(ls);
    //Display_ls(ls);
    getchar();
    return 0;
}