#include<list>
#include<iostream>
using namespace std;


template<class T>
class Tree
{
    T *NA;
    list<int> *HL;
    int root;
    int sizeN,sizeC;
    int maxN;
public:
    Tree(int n=100):root(-1),sizeN(0),sizeC(0),maxN(n)
    {
        NA= new T[n];
        HL= new list<int>[n];
    }
    ~Tree()
    {
        delete [] NA;
        delete [] HL;
    }
    bool Empty()const{return(sizeN==0);}                 //判空
    bool Full()const{return(sizeN==maxN);}               //判满
    int SizeN()const{return(sizeN);}                     //返回节点数
    int SizeC()const{return(sizeC);}                     //返回孩子结点的数目
    int FindNode(const T&v)const;                        //取结点的下标
    bool FindNode(T &v, int pos)const;                   //取结点，并返回该结点

    bool InsertN(T& node);                              //插入结点
    bool InsertC(T& parent, T& child);                  //插入孩子结点

    void ReadTree(const char * filename);               //从文件中读取输的的数据
    void WriteTree(const char * filename);              //把树的文件写入文件中
    void BFS_nrec(list<T> &L)const;                          //树的广度优先遍历，层次遍历
    void DFS_rec(list<T> &ls)const;
    void DFS_rec(list<T> &L, int t)const;                   //树的深度优先遍历，前序遍历
    void DFS_nrec(list<T> &ls)const;                            //树的深度优先遍历
    void PFS_rec(list<T> &ls, int t)const;                      //树的后根遍历，类似中序遍历
    void PFS_rec(list<T> &ls)const;
    void PFS_nrec(list<T> &ls)const;                            //树的后根遍历，类似中序遍历
                                                                //先遍历子树，再遍历根结点
    template<class U>
    friend ostream &operator<<(ostream &os, Tree<U>&t);         //重载输出运算符
    template<class U>
    friend istream &operator>>(istream &is, Tree<U> &t);        //重载输入运算符

};


/*根据元素值寻找结点，并返回结点的下标*/
template<class T>
int Tree<T>::FindNode(const T&node)const
{
    for(int i=0;i<sizeN;i++)
    {
        if(NA[i]==node)
        {
            return(i);
        }
    }
    cout<<"can't find this node"<<endl;
    return(-1);
}


/*根据下标寻找结点，并将值存储在Node中*/
template<class T>
bool Tree<T>::FindNode(T&Node, int pos)const
{
    if(pos<0 || pos>=sizeN)
    {
        cout<<"pos is illeagal"<<endl;
        return(0);
    }
    Node=NA[pos];
    return 1;
}


/*插入元素*/
template<class T>
bool Tree<T>::InsertN(T&node)
{
    if(sizeN==maxN)
    {
        cout<<"The array is Full"<<endl;
        return(0);
    }
    NA[sizeN]=node;
    sizeN++;
    return 1;
}


/*插入孩子结点*/
template<class T>
bool Tree<T>::InsertC(T& parent, T&child)
{
    int pi=FindNode(parent), ci=FindNode(child);
    if(pi==-1)
    {
        cout<<"non-exsist this parent node";
        return(0);
    }
    if(ci==-1)
    {
        cout<<"non-exsist this child node";
        return(0);
    }
    HL[pi].push_back(ci);
    sizeC++;
    return(1);
}


template<class T>
void Tree<T>::ReadTree(const char *filename)
{
    ifstream fin;
    fin.open(filename);
}


/*广度优先遍历，非递归算法*/
template<class T>
void Tree<T>::BFS_nrec(list<T> &ls)const
{
    if(sizeN==0)
    {
        cout<<"tree is empty"<<endl;
        exit(1);
    }
    queue<int> q;
    q.push(root);
    int pos;
    list<int>::iterator itr;
    while(!q.empty())
    {
        pos=q.front();
        q.pop();
        ls.push_back(NA[pos]);
        itr=HL[pos].begin();
        for(;itr!=HL[pos].end();itr++)
        {
            q.push(*itr);
        }
    }
}


/*输出列表*/
template<class T>
void Display(list<T> &ls)
{
    if(ls.size()==0)
    {
        cout<<"Donnt exsit element\n";
        return;
    }
    list<char>::iterator itr=ls.begin();
    for(;itr!=ls.end();itr++)
    {
        cout<<*itr;
    }
    cout<<endl;
}


/*深度遍历，递归方法*/
template<class T>
void Tree<T>::DFS_rec(list<T> &ls, int t)const
{
    if(t<0 || t>=sizeN)
    {
        return;
    }
    ls.push_back(NA[t]);
    list<int>::iterator itr=HL[t].begin();
    for(;itr!=HL[t].end();itr++)
    {
        DFS_rec(ls, *itr);
    }
}


/*深度遍历，加一个重载的原因是无法用root形成默认形参*/
template<class T>
void Tree<T>::DFS_rec(list<T> &ls)const
{
    DFS_rec(ls, root);
}


/*深度优先遍历，非递归方法*/
template<class T>
void Tree<T>::DFS_nrec(list<T> &ls)const
{
    if(sizeN==0)
    {
        cout<<"tree is empty"<<endl;
        return;
    }
    int pos=root;
    list<int>::iterator itr;
    stack<int> sta;
    sta.push(pos);
    while(!sta.empty())
    {
        pos=sta.top();
        sta.pop();
        ls.push_back(NA[pos]);
        if(HL[pos].begin()==HL[pos].end())
        {
            continue;
        }
        itr=HL[pos].end();
        for(itr--;itr!=HL[pos].begin();itr--)
        {
            sta.push(*itr);
        }
        sta.push(*itr);
    }
}


/*后根遍历，递归方法*/
template<class T>
void Tree<T>::PFS_rec(list<T> &ls, int t)const
{
    if(t<0 || t>=sizeN)
    {
        return;
    } 
    list<int>::iterator itr=HL[t].begin();
    for(;itr!=HL[t].end();itr++)
    {
        PFS_rec(ls, *itr);
    }
    ls.push_back(NA[t]);
}


/*后根遍历，递归方法，多一个重载的原因是无法进行root默认形参*/
template<class T>
void Tree<T>::PFS_rec(list<T> &ls)const
{
    PFS_rec(ls, root);
}


/*后根遍历，非递归方法*/
template<class T>
void Tree<T>::PFS_nrec(list<T> &ls)const
{
    if(sizeN==0)
    {
        cout<<"tree is empty"<<endl;
        return;
    }
    int pos=root;
    list<int>::iterator itr;
    stack<int> sta;
    stack<int> s;
    s.push(pos);
    sta.push(pos);
    while(!sta.empty())
    {
        pos=sta.top();
        sta.pop();
        if(HL[pos].begin()==HL[pos].end())
        {
            continue;
        }
        itr=HL[pos].end();
        for(itr--;itr!=HL[pos].begin();itr--)
        {
            sta.push(*itr);
            s.push(*itr);
        }
        sta.push(*itr);
        s.push(*itr);
    }
    while(!s.empty())
    {
        pos=s.top();
        s.pop();
        ls.push_back(NA[pos]);
    }
}


/*重载<<初始化树*/
template<class T>
istream& operator >>(istream &is, Tree<T>& t)
{
    char str[50];
    int n;
    T parent, child;
    is>>str>>n;
    is>>str>>parent;
    t.InsertN(parent);
    t.root=t.sizeN-1;
    is>>str;
    for(int i=1;i<n;i++)
    {
        is>>child;
        t.InsertN(child);
    }
    is>>str>>n;
    for(int i=0;i<n;i++)
    {
        is>>parent>>child;
        t.InsertC(parent, child);
    }
    return is;
}


/*树的输出重载运算符*/
template<class T>
ostream & operator<<(ostream &os, Tree<T> &t)
{
    for(int i=0;i<t.sizeN;i++)
    {
        os<<i<<'-'<<t.NA[i]<<":\t";
        list<int>::iterator itr=t.HL[i].begin();
        for(;itr!=t.HL[i].end();itr++)
        {
            os<<*itr<<'\t';
        }
        os<<endl;
    }
    return os;
}
