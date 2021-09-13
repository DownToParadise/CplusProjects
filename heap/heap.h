#ifndef HEAP_H_
#define HEAP_H_
#include<vector>
#include"bitree.h"
#include<iostream>
using namespace std;


/*该堆使用线性结构，向量，表现树形结构，小根堆*/
template<class T>
class Heap
{
    vector<T> vec;                                          //使用向量储存堆
    int size;                                               //表示元素个数
    void BuildHeap(void);                                   //把向量容器调整成堆
    void PercolateDown(int pos);                            //向下调整
    void PercolateUp();                                     //向上调整
public:
    Heap(int max=100):vec(0),size(0){}                      //建空堆
    Heap(const vector<T> & vec);                            //用向量创建堆对象
    bool Empty(void)const{return(size==0);}                 //检测堆是否为空
    int Size(void){return(size);}                           //返回堆的个数 

    void Insert(T& item);                                    //堆插入
    T Top(void)const {return(vec[0]);}                      //返回堆的首元素
    void DeleteMin(void);                                   //删除堆首元素
    void DeleteMin(T& item);                                //从堆中删除该元素，并返回改元数的指针
    T DeleteMin_r(T item);                                  //默认删除堆顶元素
                                                            
    BTNode<T> *Transform_BT(void);                          //将vec转化成二叉树
    void Clear(void) {size=0;}
    
    //template<class T> friend ostream&operator << (ostream &os, const Heap<T>&heap);                       //输出结点


};

/*向下调整，根据参数位置调整树*/
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
    int item;
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
    int it;
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
    item=vec[0];       //由于item是元素的引用，所以对Item的修改也会对外界变量产生影响
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
    item=vec[0];         //由于item是元素的引用，所以对Item的修改也会对外界变量产生影响
    vec[0]=vec[size-1];
    vec.pop_back();
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

#endif

