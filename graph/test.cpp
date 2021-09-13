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


/*广度遍历的递归算法不存在，除非修改数据结构*/


/*输出列表*/
void Display_ls(list<char> ls)
{
    list<char>::iterator itr=ls.begin();
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