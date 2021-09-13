/*参考网址：
    https://wenku.baidu.com/view/d1e9d6fe02020740bf1e9bce.html?from=search
    https://www.cnblogs.com/gwzz/p/9197445.html  */
#include<iostream>
using namespace std;
static int n_=8;
static int count_=0;
static int a[8]={0};

void Display(int *p, int n)
{
    static int total=0;
    for(int y=0;y<n;y++)
    {
        if(y%n==0)
        {
            cout<<++total<<endl;
        }
        for(int x=0;x<n;x++)
        {
            if(p[y]!=x)
            {
                cout<<"#";
            }
            else
            {
                cout<<"@";
            }
        }
        cout<<endl;
    }
    cout<<"Press any key to see"<<endl;
    getchar();
}


void Queen_rec(int y)
{
    static int A[22], B[22], C[22], Y[8];
    if(y<0 || y>8)
    {
        return;
    }
    if(y==8)
    {
        Display(Y, 8);
    }
    for(int x=0;x<8;x++)
    {
        if(!A[x+7] && !B[x+y+7] && !C[x-y+7])
        {
            Y[y]=x;
            A[x+7]=B[x+y+7]=C[x-y+7]=1;
            Queen_rec(y+1);
            A[x+7]=B[x+y+7]=C[x-y+7]=0;
        }
    }
}


void Queen_nrec(int n)
{
    if(n==0)
    {
        cout<<"plate NUM fault"<<endl;
        exit(1);
    }
    static int A[22], B[22], C[22], Y[8];
    int y=0;
    int x=0;
    for(;y<n;y++)
    {
        for(;x<8;x++)
        {
            if(!A[x+7] && !B[x+y+7] && !C[x-y+7])
            {
                Y[y]=x;
                A[x+7]=B[x+y+7]=C[x-y+7]=1;
            }
        }
    }
    Display(Y, n);
}


bool check(int *a, int n)
{
    int i,j;
    //从第二层开始向下判断
    for(i=2;i<=n;i++)
    {    //j表示的是i层以上的都逐一比较，i每增加一层要与上面的所有queen进行比较
        for(j=1;j<=i-1;j++)
        {
            //a[i]-a[j])==abs(i-j)判断其是否在对角线上
            //a[i]==a[j]判断是否在同一列上
            //同一层则不需要判断，i与j肯定不同
            if((abs(a[i]-a[j])==abs(i-j))||(a[i]==a[j]))
            {
                return false;
            }
        }
    }
    return true;
}


void Display(int *a)
{
    int i;
    count_++;
    cout<<"The  "<<count_<<"  circumstace: ";
    for(i=1;i<=n_;i++)
    {
        cout<<"("<<i<<','<<a[i]<<')';
    }
    cout<<endl;
}


void Queen8_rec(int k)
{
    /*用k表示第几行，即第几个皇后,用i表示第几列*/
    int i=0;
    if(k>n_)
    {
        Display(a);
    }
    else
    {
        /*用k表示第几行，即第几个皇后,用i表示第几列*/
        for(i=1;i<=n_;i++)
        {
            a[k]=i;
            if(check(a,k))
            {
                Queen8_rec(k+1);
            }
        }
    }  
}


void Queen8_nrec()
{
    int i=1;
    /*i代表了第几个皇后，即第几层*/
    while(i>0)
    {
        /*i小于0则证明8的8次方几乎所有的数都被试过了*/
        // a[i]++;
        // while(!check(a, i))
        // {
        //     a[i]++;
        // }
        // if(a[i]<=n_)
        // {
        //     if(i==n_)
        //     {
        //         Display(a);
        //     }
        //     else
        //     {
        //         i++;
        //     }      
        // }
        // else
        // {
        //     a[i]=0;
        //     i--;
        // }  
        a[i]++;
        while(!check(a, i))
        {
            /*再到不与上面的数冲突的点*/
            a[i]++;
        }
        if(a[i]<=n_)
        {
            /*满足则说明在这一层内*/
            if(i==n_)
            {
                Display(a);
            }
            else
            {
                i++;
            } 
        }  
        else
        {
            /*这个地方是回溯的关键，运行到这儿，就说明
                这一行从一到八都试过了，每一个点都会与上面冲突,就要试在新的上一个的新的这一行的每位数，
                ，所以这个地方要重置，返回上一层，找下一个不与上层冲突的数，再来试触*/
            a[i]=0;
            i--;
        }
          
    }
}


int main()
{
    //Queen_rec(0);
    //Queen_nrec(8);
    Queen8_nrec();
    getchar();
    return(0);
}