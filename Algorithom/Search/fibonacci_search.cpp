#include<iostream>
using namespace std;
static int F[]={0,1,1,2,3,5,8,13,21,34,55};

int Fibonacci_Search(int *a, int n, int key)
{
    int low,high,mid,i,k;
    low=1;
    high=n;
    k=0;
    while(n>F[k]-1)
    {
        k++;
    }
    /*补满待搜索数组*/
    for(i=n;i<F[k]-1;i++)
    {
        a[i]=a[n];
    }
    while(low<=high)
    {
        mid=low+F[k-1]-1;
        if(key>a[mid])
        {
            low=mid+1;
            k=k-2;
        }
        else if (key<a[mid])
        {
            high=mid-1;
            k=k-1;
        }
        else
        {
            if(mid>=n)
            {
                return n;
            }
            return mid;      
        }   
    }
    return 0;
}

template<class T>
int Fibonacci_Search(T *a, int n, T key)
{
    int low,high,mid,i,k;
    low=1;
    high=n;
    k=0;
    while(n>F[k]-1)
    {
        k++;
    }
    /*补满待搜索数组*/
    for(i=n;i<F[k]-1;i++)
    {
        a[i]=a[n];
    }
    while(low<=high)
    {
        mid=low+F[k-1]-1;
        if(key>a[mid])
        {
            low=mid+1;
            k=k-2;
        }
        else if (key<a[mid])
        {
            high=mid-1;
            k=k-1;
        }
        else
        {
            if(mid>=n)
            {
                return n;
            }
            return mid;      
        }   
    }
    return 0;
}

int main()
{
    int a[]={0,1,2,3,4,5,6,7,8,190};
    char b[]={'0','a','b','c','d','e','f','g','h','i'};
    int n=9;
    int size=1;
    int i;
    i=Fibonacci_Search(a,n,19);
    i=Fibonacci_Search(b,9,'d');
    cout<<i<<"->"<<b[i]<<endl;
    getchar();
}