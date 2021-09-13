//#include"bitree.h"
#include<iostream>
#include<queue>
#include"AvlTree.h"
using namespace std;


template<class T>
AvlNode<T> *AvlTree<T>::FindNode(const T&key,AvlNode<T> *t)const
{
    if(!t)
    {
        //cerr<<"The pointer is invalid"<<endl;
        return NULL;
    }
    else
    {
        if(key<t->data)
        {
            FindNode(key,t->left);
        }
        else if (key>t->data)
        {
            FindNode(key,t->right);
        }
        else
        {
            return t;
        }   
    } 
    return NULL;
}


template<class T>
bool AvlTree<T>::Find(T&x)const
{
    return FindNode(x,root);
}

/*将树向左旋转*/
template<class T>
void AvlTree<T>::LL(AvlNode<T>*&t)
{
    AvlNode<T> *c=t->right;
    t->right=c->left;
    c->left=t;
    t->height=max(Height(t->left),Height(t->right))+1;
    c->height=max(Height(c->left),Height(c->right))+1;
    t=c;
}


/*将树向右旋转*/
template<class T>
void AvlTree<T>::RR(AvlNode<T> *&t)
{
    AvlNode<T> *c=t->left;
    t->left=c->right;
    c->right=t;
    t->height=max(Height(t->left),Height(t->right))+1;
    c->height=max(Height(c->left),Height(c->right))+1;
    t=c;
}


/*进行插入时，要进行旋转的结点，bf值符号不相同
先将符号统一，左子树存在符号不统一，先左后右*/
template<class T>
void AvlTree<T>::LR(AvlNode<T>*&t)
{
    LL(t->left);
    RR(t);
}


/*进行插入时，要进行旋转的结点，bf值符号不相同
先将符号统一，右子树存在符号不统一，先右后左*/
template<class T>
void AvlTree<T>::RL(AvlNode<T>*&t)
{
    RR(t->right);
    LL(t);
}


template<class T>
void AvlTree<T>::Insert(const T&x,AvlNode<T>*&t)
{
    if(!t)
    {
       t=new AvlNode<T>(x);
       size++;
    }
    else if (Find(x))
    {
        //cout<<"This node has exsisted"<<endl;
        return;
    }
    else if(x<t->data)
    {
        Insert(x,t->left);
        if(Height(t->left)-Height(t->right)==2)
        {
            if(x<t->left->data)
            {
                RR(t);
            }
            else
            {
                LR(t);
            }
            
        }
    }
    else if(x>t->data)
    {
        Insert(x,t->right);
        if(Height(t->right)-Height(t->left)==2)
        {
            if(x>t->right->data)
            {
                LL(t);
            }
            else
            {
                RL(t);
            }  
        }
    }
    t->height=max(Height(t->left),Height(t->right))+1;
}


/*清空平衡树*/
template<class T>
void AvlTree<T>::Clear(AvlNode<T> *&t)
{
    if(!t)
    {
        return;
    }
    Clear(t->left);
    Clear(t->right);
    free(t);
}


template<class T>
void AvlTree<T>::Gotoxy(Loc loc)
{
    static int indent=0,level=0;
    if(loc.y==0)
    {
        indent=0;
        level=0;
    }
    if(level!=loc.y)
    {
        cout<<endl;
        indent=0;
        level++;
    }
    cout.width(loc.x-indent);
    indent=loc.x;
}


/*打印平衡树的信息*/
template<class T>
void AvlTree<T>::PrintAvlTree(const AvlNode<T>* t,int w)
{
    Loc f,item;
    int level=0,off=w/2;//off为两个元素间的间隔
    queue<const AvlNode<T> *> avl_q;
    queue<Loc> loc_q;
    f.x=off;
    f.y=level;
    avl_q.push(t);
    loc_q.push(f);
    if(!t)
    {
        //cerr<<"The pointer is default"<<endl;
        return;
    }
    while(!avl_q.empty())
    {
        t=avl_q.front();
        avl_q.pop();
        item=loc_q.front();
        loc_q.pop();
        Gotoxy(item);
        cout<<t->data;
        if(item.y!=level)
        {
            level++;
            off=off/2;
        }
        if(t->left)
        {
            avl_q.push(t->left);
            f.x=item.x-off/2;
            f.y=level+1;
            loc_q.push(f);
        }
        if(t->right)
        {
            avl_q.push(t->right);
            f.x=item.x+off/2;
            f.y=level+1;
            loc_q.push(f);
        }
    }
    cout<<endl;
}


template<class T>
void AvlTree<T>::Update(const T&x)
{
    if(Find(x))
    {
        return;
    }
    else
    {
        Insert(x);
    }
}


int main()
{
    AvlTree<int> avl;
    for(int i=1;i<=12;i++)
    {
        if(i==3)
        {
           int a;
        }
        avl.Insert(i);
    }
    avl.PrintAvlTree(40);
    getchar();
    return 0;
}