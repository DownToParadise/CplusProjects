#include<iostream>
#include"tree.h"
#include<list>
#include<fstream>
#include<istream>
#include<stack>
#include<queue>
using namespace std;


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


int main()
{
    char filename[]="treein.txt";
    char filename_out[]="treeout.txt";
    string str;
    ifstream is(filename, ios_base::in);
    ofstream of(filename_out, ios_base::out);
    if(!is)
    {
        cout<<"cannot open file to read\n";
        exit(1);
    }
    
    if(!of)
    {
        cout<<"cannot open file to write\n";
        exit(1);
    }

    Tree<char> t(20);
   // is>>t;
    is>>t;
    of<<t;
    cout<<t;
    is.close();
    of.close();
    list<char> ls;
    list<char> ls_;
    t.PFS_rec(ls);
    t.PFS_nrec(ls_);
    Display(ls);
    Display(ls_);
    getchar();
    return 0;
}