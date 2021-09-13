/*使用除数留余的方法建立散列表
开放地址法的线性探测解决冲突*/
#include<iostream>
#include<math.h>
#include<vector>
#include<list>
using namespace std;

/*用define定义过后变成了一种类型*/
#define HashSize 11;/*定义散列表的初始长度，为数组的长度*/
#define NullKey -32723;

struct HashTable
{
    int *elem;
    int count;
};
int m=0;/*散列表表长*/
bool InitHashTalbe(HashTable*H)
{
    int i;
    m=HashSize;
    H->elem=new int[m];
    for(i=0;i<m;i++)
    {
        H->elem[i]=NullKey;
    }
    return true;
}

int Hash(int key)
{
    return key%m;
}

/*插入关键字进散列表，用线性探测解决冲突*/
void InsertHash_mod(HashTable *H,int key)
{
    int addr=Hash(key);
    int num=NullKey;
    while(H->elem[addr]!=num)
    {
        addr=(addr+1)%m;
    }
    H->elem[addr]=key;
}


/*散列表查找关键字，用线性探测解决冲突*/
bool SearchHash_mod(HashTable H, int key, int *addr)
{
    *addr=Hash(key);
    int num=NullKey; 
    while(H.elem[*addr]!= key)
    {
        *addr=Hash(*addr+1);
        if(H.elem[*addr]==num || *addr==Hash(key))
        {
            return false;
        }
    }
    return true;
}


/*使用二次探测法消除冲突*/
void InsertHash_square(HashTable *H,int key)
{
    int addr=Hash(key);
    static int num=NullKey;
    int d=1;
    int a=1;
    while(H->elem[addr]!=num)
    {
        if(d<0)
        {
            a++;
            d=pow(a,2);
        }
        else
        {
            d=-d;
        }
        addr=(addr+d)%m;
    }
    H->elem[addr]=key;
}


/*散列表查找元素，基于二次探测法*/
bool SearchHash_square(HashTable H,int key,int *addr)
{
    *addr=Hash(key);
    int d=1;
    int a=1;
    static int num=NullKey;
    while(H.elem[*addr]!=key)
    {
        if(d<0)
        {
            a++;
            d=pow(a,2);
        }
        else
        {
            d=-d;
        }
        *addr=(*addr+d)%m;
        if(H.elem[*addr]==num || *addr==Hash(key))
        {
            return false;
        }
    }
    return true;
}

 
/*使用分离连接法解决冲突，没有改变HashTable数据结构，造成了空间的一定浪费，可以完全不用HashTable数据类型
出现了某些莫名其妙的事情，导致vec尾插错误*/
void InsertHash_list(vector<list<int> > &vec,int key)
{
    int addr=Hash(key);
    vec[addr].push_back(key);
}

/*散列表查找元素，基于分离连接法*/
int SearchHash_list(vector<list<int> > &vec,int key,int *addr)
{
    int pos=Hash(key);
    *addr=0;
    list<int>::iterator itr=vec[pos].begin();
    for(;itr!=vec[pos].end();itr++,(*addr)++)
    {
        if(*itr==key)
        {
            return pos;
        }
    }
    return false;
}


int main()
{
    int a[]={47,7,29,11,16,92,22,8,3};
    HashTable H;
    int key;
    int addr;
    int *p=&addr;
    InitHashTalbe(&H);
    int num=HashSize;
    int size=9;
    
    for(int i=0;i<9;i++)
    {
        InsertHash_mod(&H,a[i]);
    }
    for(int i=0;i<num;i++)
    {
        cout<<H.elem[i]<<"  ";
    }
    cout<<endl;
    cout<<"Please input a key"<<endl;
    cin>>key;
    if(SearchHash_mod(H,key,p))
    {
        cout<<"The address is\t"<<*p<<endl;
        cout<<"The key is\t"<<H.elem[*p]<<endl;
    }
    else
    {
        cout<<"Not exsist"<<endl;
    }
    getchar();
    
    // vector<list<int> > vec;
    // for(int i=0;i<m;i++)
    // {
    //     list<int> l;
    //     vec.push_back(/* *(new list<int>) */l);
    // }
    /* vec.resize(m);
    vector<list<int> >::iterator itrl=vec.begin();
    (*itrl).push_back(1);
    vec[1].push_back(1);
    int n;
    int *p=&n;
    InitHashTalbe(&H);
    int i;
    int size=9;
    for(int i=0;i<size;i++)
    {
        cout.width(4);
        InsertHash_list(vec,a[i]);
        cout<<i;
    }
    cout<<endl; */
    
    // if(SearchHash_square(H,92,p))
    // {
    //     cout<<"The address is\t"<<*p<<endl;
    //     cout<<"The key is\t"<<H.elem[*p]<<endl;
    // }
    // else
    // {
    //     cout<<"Not exsist"<<endl;
    // }
    /* if(i=SearchHash_list(vec,22,p))
    {
        cout<<"The postion of key in vec is\t"<<i<<endl;
        cout<<"The postion of key in list is\t"<<*p<<endl;
        // cout<<"The value of key is\t"<<vec[i];
        // list<int>::iterator itr;
        // for(int j=0;j<*P;itr++)
    } */
    getchar();
    return 0;
}