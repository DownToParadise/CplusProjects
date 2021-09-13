#include"bitree.h"
#include<iostream>
using namespace std;
template<class T>
void PercolateUp(T*, int);

/*用向上调整的方法建立大根堆*/
template<class T>
void BuildHeap(T *pa, int size)
{
    for(int i=size-1;i>0;i--)
    {
        PercolateUp(pa,i);
    }
}


/*向上调整为大根堆*/
template<class T>
void PercolateUp(T*pa, int pos)
{
    T temp=pa[pos];
    int p=pos;
    int c=(p+1)/2-1;
    while(c>=0)
    {
        if(temp>pa[c])
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



/*向下调整为大根堆*/
template<class T>
void PercolateDown(T*pa,int size)
{
    T temp=pa[0];
    int p=0;
    int c=(2*p)+1;
    while(c<size)
    {
        if(pa[c]<pa[c+1]&&c+1<size)
        {
            c++;
        }
        if(temp<pa[c])
        {
            pa[p]=pa[c];
            p=c;
            c=(2*p)+1;
        }
        else
        {
            break;
        }
    }
    pa[p]=temp;
}


/*输出堆*/
template<class T>
void Display(T*pa, int size)
{
    for(int i=0;i<size;i++)
    {
        cout<<"\\"<<pa[i];
    }
    cout<<endl;
}


/*堆排序*/
template<class T>
void HeapSort(T*p, int size)
{
    BuildHeap(p, size);
    T temp;
    for(int i=size-1;i>0;i--)
    {
        temp=p[0];
        p[0]=p[i];
        p[i]=temp;
        PercolateDown(p, i);
    }
}


int main()
{
    int a[]={100,85,40,77,80,60,66,98,82,10,20};
    int size=11;
    cout<<"The ordinary array:"<<endl;
    Display(a, size);
    BuildHeap(a, size);
    vector<int> vec(a, a+size);
    BTNode<int> *t=Transform_nrec(vec);
    PrintTree(t, 80);
    cout<<"Build_heap:"<<endl;
    Display(a, size);
    HeapSort(a, size);
    cout<<"HEAPSORT_BIG:"<<endl;
    Display(a, size);
    getchar();
    return 0;
}