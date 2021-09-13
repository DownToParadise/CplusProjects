#include"heap.h"
#include"bitree.h"
#include<iostream>
using namespace std;

int main()
{
    int a[]={10,23,123,2,424,23,123,1,34,234};
    int size=10;
    vector<int> vec={a, a+size};
    Heap<int> h(vec); 
    BTNode<int> *t=h.Transform_BT();
    PrintTree(t);
    getchar();
}