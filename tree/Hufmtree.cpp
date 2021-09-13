#include<iostream>
#include<vector>
#include"bitree.h"
#include"heap.h"
using namespace std;

/*HufmNode结点定义*/
template<class T>
struct HufmNode
{
    BTNode<T> *t;
    int operator < (const HufmNode &h){return(t->data<h.t->data);}
    int operator <= (const HufmNode &h){return(t->data<=h.t->data);}
    int operator > (const HufmNode &h){return(t->data>h.t->data);}
    int operator + (const HufmNode &h){return(t->data+h.t->data);}
};


/*建立哈夫曼树*/
template<class T>
BTNode<T> *MakeHufmTree(T*pa, int n)
{
    HufmNode<T> hf;
    BTNode<T> *t,*left,*right;
    vector<HufmNode<T> > vec;
    Heap<HufmNode<T> > H(vec);
    int i=0;
    for(;i<n;i++)
    {
        t=GetBTNode(pa[i]);
        hf.t=t;
        H.Insert(hf);
    }
    for(i=1;i<n;i++)
    {
        H.DeleteMin(hf);
        left=hf.t;
        H.DeleteMin(hf);
        right=hf.t;
        t=GetBTNode(left->data+right->data, left, right);
        hf.t=t;
        H.Insert(hf);
    }
    H.DeleteMin(hf);
    t=hf.t;
    return(t);
}


/*采用前序遍历的方法求出叶子结点的编码*/
template<class T>
void Allcode(BTNode<T> *&t, vector<int> code, int pl=0)
{
    if(t!=NULL)                                                                                                                     
    {
        if(t->left==NULL && t->right==NULL)
        {
            for(int i=1; i<=pl; i++)
            {
                t->code.push_back(code[i]);
            }
        }
        else
        {
            pl++;
            if(t->left)
            {
                code[pl]=0;
                Allcode(t->left, code, pl);
            }
            if(t->right)
            {
                code[pl]=1;
                Allcode(t->right, code, pl);
            }
            pl--;
        }
    }
}


/*输出向量*/
template<class T>
void Display_(vector<T> vec)
{
    if(vec.size()==0)
    {
        cerr<<"code is falut"<<endl;
        return;
    }
    vector<int>::iterator itr=vec.begin();
    //vector<T>::iterator itr=vec.begin();
    for(;itr!=vec.end();itr++)
    {
        cout<<*itr;
    }
    cout<<endl;
}


/*利用前序遍历输出Hufmtree*/
template<class T>
void OutputCodePreorder(BTNode<T> *bt)
{
    if(bt==NULL)
    {
        return;
    }
    if(bt->left==NULL && bt->right==NULL)
    {
        cout<<"\""<<bt->data<<"\""<<"'s Hufmcode is ";
        Display_(bt->code);
    }
    else
    {
        if(bt->left)
        {
            OutputCodePreorder(bt->left);
        }
        if(bt->right)
        {
            OutputCodePreorder(bt->right);
        }
    }
    
}


int main()
{
    int a[]={15,8,10,21,6,19,3};
    //char ch[]={'a','b','c','d','e'};
    
    int size=7;
    int size_2=5;
    vector<int> vec{a,a+size};
    //BTNode<char> *ct=MakeHufmTree(ch, size_2);
    BTNode<int> *t=MakeHufmTree(a, size);
    cout<<"The Hufmtree is :"<<endl;
    PrintTree(t);
    //PrintTree(ct);
    Allcode(t, vec);
    OutputCodePreorder(t);
    getchar();
    return 0;
}