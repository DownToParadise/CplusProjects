#include<iostream>
using namespace std;
template<typename T>
int partition(T* pi, int size)
{
    int i=0;
    int j=size-1;
    T temp=pi[0];
    while(i!=j)
    {
        while(pi[j]>=temp && i<j)
            j--;
        if(j>i)
        {
            pi[i++] = pi[j];
        }
        while(pi[i]<=temp && i<j)
            i++;
        if(j>i)
        {
            pi[j--] = pi[i];
        }
    }
    pi[i] = temp;
    return(i);
}

int main()
{
    
    return 0;
}