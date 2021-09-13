#include"bitree.h"
#include<iostream>
using namespace std;
template<class T>
void PercolateDown(T*,int,int);
template<class T>
void Display(T*, int);


/*建堆*/
template<class T>
void BuildHeap(T *pa, int size)
{
    for(int i=size/2;i>=0;i--)
    {
        PercolateDown(pa,i,size);
    }
}


/*向下调整为小根堆*/
template<class T>
void PercolateDown(T *pa, int pos, int size)
{
    T temp=pa[pos];
    int c=2*pos+1;
    while(c<size)
    {
        if(c+1<size&&pa[c]>pa[c+1])
        {
            c++;
        }
        if(temp>pa[c])
        {
            pa[pos]=pa[c];
            pos=c;
            c=2*pos+1;
        }
        else
        {
            break;
        }    
    }
    pa[pos]=temp;
}


/*向上调整为小根堆*/
template<class T>
void PercolateUp(T*pa, int pos, int size)
{
    T temp=pa[pos];
    int p=pos;
    int c=(p+1)/2-1;
    while(c>=0)
    {
        if(temp<pa[c])
        {
            pa[p]=pa[c];
            p=c;
            c=(p+1)/2-1;
        }
        else
        {
            break;
        } 
    }
    pa[p]=temp;
}


/*堆排序*/
template<class T>
void HeapSortDown(T *pa, int size)
{
    T temp;
    BuildHeap(pa, size);
    Display(pa, size);
    for(int i=size-1;i>0;i--)
    {
        PercolateDown(pa,0,i);   
        temp=pa[0];
        pa[0]=pa[i];
        pa[i]=temp;       
    }
}


template<class T>
void Display(T*pa, int size)
{
    for(int i=0;i<size;i++)
    {
        cout<<"\\"<<pa[i];
    }
    cout<<endl;
}


int main()
{
    int a[]={10,20,30,40,50,60,199,2,323,65,645,642,21,78};
    int size=14;
    cout<<"The ordinary array:"<<endl;
    Display(a,size);
    BuildHeap(a, size);
    vector<int> vec(a, a+size);
    BTNode<int> *t=Transform_nrec(vec);
    PrintTree(t, 80);
    cout<<"Build_heap:"<<endl;
    HeapSortDown(a, size);
    cout<<"HEAPSORT_SMALL:"<<endl;
    Display(a, size);
    getchar();
    return 0;
}


// /*堆排序向上排序*/
// template<class T>
// void HeapSortUp(T*pa, int size)
// {
//     T temp;
//     BuildHeap(pa, size);
//     Display(pa, size);
//     for(int i=size-1;i>0;i--)
//     {
//         PercolateUp(pa, i, i);
//         Display(pa, size);
//     }
// }


// template<class T>
// ostream& operator << (ostream &os, T *pa)
// {
//     for()
// }
