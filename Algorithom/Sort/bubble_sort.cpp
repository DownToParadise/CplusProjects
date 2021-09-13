#include<iostream>
using namespace std;
template<typename T>
T* bubble_sort(T *pi, int size)
{
    int i,j;
    T item;
    for(i=0; i<size-1; i++)
    {
        for(j=0; j< size-1-i; j++)
        {
            if(pi[j] > pi[j+1])
            {
                item = pi[j+1];
                pi[j+1] = pi[j];
                pi[j] = item;
            }
        }
    }
    return pi;
}

int main()
{
    cout<<"woaiwojia"<<endl;
    int size=9;
    int a[9]={2, 8, 1, 3, 8, 8, 1, 2, 5};
    int *pi = a;
    for(int i=0; i<size; i++)
    {
        cout<<a[i];
    }
    cout<<endl;
    pi = bubble_sort(a, size);
    for(int i=0; i<size; i++)
    {
        cout<<pi[i];
    }
    getchar();
    return 0;
}