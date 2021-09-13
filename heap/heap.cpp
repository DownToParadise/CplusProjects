#include"heap.h"
#include"bitree.h"
#include<iostream>
#include<vector>
using namespace std;


/*向下调整*/
template<class T>
void Heap<T>::PercolateDown(int pos)
{
    //p表示当前节点
    int p=pos;
    //c表示其左右孩子
    int c=2*p+1;
    //T temp=vec[p];
    T temp=vec[p];
    while(c<size)
    {
        if(vec[c]>vec[c+1]&&c+1<size)
        {
            c++;
        }
        if(vec[p]<vec[c])
        {
            break;
        }
        else
        { 
            temp=vec[p];
            vec[p]=vec[c];
            vec[c]=temp;
            p=c;
            c=2*p+1;
        }
    }
    //vec[p]=temp;
}


/*向上调整*/
template<class T>
void Heap<T>::PercolateUp()
{
    T temp=vec[size-1];
    int p=size-1;
    int c=(p+1)/2-1;
    while(c>=0)
    {
        if(temp<vec[c])
        {
            vec[p]=vec[c];
            p=c;
            c=(p+1)/2-1;
        }
        else
        {
            break;
        } 
    }
    vec[p]=temp;
}


/*插入一个元素进入堆
能对0进行插入，但是无法用二叉树进行display，
原因可能是转换函数有些问题*/
template<class T>
void Heap<T>::Insert(T& item)
{
    vec.push_back(item);
    size++;
    PercolateUp();
}


/*删除顶上，最小结点*/
template<class T>
void Heap<T>::DeleteMin()
{
    if(size==0)
    {
        cerr<<"Heap empty"<<endl;
        exit(1);
    }
    vec[0]=vec[size-1];
    size--;
    PercolateDown(0);
}



template<class T>
T Heap<T>::DeleteMin_r(T item)
{
    if(size==0)
    {
        cerr<<"Heap empty"<<endl;
        exit(1);   
    }
    vec[0]=item;       //由于item是元素的引用，所以对Item的修改也会对外界变量产生影响
    vec[0]=vec[size-1];
    size--;
    PercolateDown(0);
    return item;
}


/*删除顶上结点，用通过引用返回该值*/
template<class T>
void Heap<T>::DeleteMin(T&item)
{
    if(size==0)
    {
        cerr<<"Heap empty"<<endl;
        exit(1);
    }
    vec[0]=item;       //由于item是元素的引用，所以对Item的修改也会对外界变量产生影响
    vec[0]=vec[size-1];
    size--;
    PercolateDown(0);
    // vector<T>::iterator itr;
    // T *p;
    // itr=find(vec.begin(), vec.end(), item);
    // if(itr==vec.end())
    // {
    //     cerr<<"No such element"<<endl;
    //     cerr<"Please tru again"<<endl;
    //     exit(1);
    // }
    // //vec.erase(itr);
    // for(int i=0;i<size;i++)
    // {
    //     if(vec[i]==item)
    //     {
    //         break;
    //     }
    // }
    // p=&vec[i];
    // vec.erase(itr);
}


/*析构函数，vec转化成小根堆*/
template<class T>
Heap<T>::Heap(const vector<T> &vec)
{
    size=vec.size();
    this->vec=vec;
    BuildHeap();
}


/*建立小根堆*/
template<class T>
void Heap<T>::BuildHeap()
{
    for(int i=size/2-1;i>=0;i--)
    {
        //fcout<<vec[i]<<endl;
        PercolateDown(i);
    }
}


/*将vec转化成二叉树*/
template<class T>
BTNode<T> *Heap<T>::Transform_BT(void)
{
    return Transform_nrec(vec);
}  



// /*输出vec*/
// template<class T>
// ostream & operator<<(ostream & os, const Heap<T> & heap)
// {
//     vector<T>::iterator itr=heap.vec.begin();
//     for(;itr!=heap.vec.end();itr++)
//     {
//         cout<<"*"<<*itr;
//     }
//     cout<<endl;
//     heap.vec.data();
//     return os;
// }
