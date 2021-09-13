#include<iostream>
//#include"bitree.h"
using namespace std;

template<class T>
struct AvlNode
{
    T data;
    AvlNode *left,*right;
    int height;
    int bf;
    AvlNode(const T& item, AvlNode *l=0, AvlNode *r=0,int h=0):
        data(item),left(l),right(r),height(h){}
};


struct Loc
{
    int x,y;
};

template<class T>
class AvlTree
{
private:
    AvlNode<T> *root;
    int size;
    int Height(AvlNode<T> *t)const{return(t==NULL?-1:t->height);}
    void Insert(const T&x, AvlNode<T>*&t);
    AvlNode<T> *FindNode(const T&x,AvlNode<T> *t)const;
    int Max(int x1, int x2){return x1<x2?x2:x1;}

    void LL(AvlNode<T>*&t);
    void RR(AvlNode<T>*&t);
    void RL(AvlNode<T>*&t);
    void LR(AvlNode<T>*&t);

    void Clear(AvlNode<T> *&t);
    void PrintAvlTree(const AvlNode<T>* t,int screenwidth);
    void Gotoxy(Loc loc);
public:
    AvlTree(void):root(NULL),size(0){}
    AvlTree(const AvlTree<T> &bst);
    ~AvlTree(){Clear(root);}
    bool Find(const T&x)const{return(FindNode(x,root));}
    bool Find(T&x)const;
    bool Empty(void)const{return(size==0);}
    int Size(void){return(size);}
    void Clear(void){Clear(root);size=0;}
    void Update(const T&x);
    void Insert(const T&x){Insert(x,root);}
    void PrintAvlTree(int screenwidth){PrintAvlTree(root,screenwidth);}

    
};