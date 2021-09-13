#include<iostream>
#include<list>
#include<queue>
#include<algorithm>
using namespace std;

const double MAXCOST=20000;


/*记录边的信息*/
struct PathData
{
    int start,dest;
    double cost;
    /*类型转换函数，隐式转换，可以避免写重载函数的麻烦
    用于与double类型比较，参考网址：https://www.cnblogs.com/dishengAndziyu/p/10914348.html*/
    operator double()const{return cost;}
};


/*边结点，还是要把它放在类的外面*/
struct Edgecode
    {
        int dest;                                       //终点下标
        double cost;                                    //权值
        operator int(){return dest;}
    };


template<class T>
class Graph
{
    
    T* VA;                                              //顶点数组指针
    list<Edgecode> *HL;                                 //边链表数组指针
    int sizeV, sizeE;                                   //顶点，边的个数
    int maxV;                                           //顶点数组空间长度
    double GetCost(int si, int dj)const;                //按起点下标和终点下标读取相应边的权值
public:
    Graph(int n=100):sizeV(0), sizeE(0), maxV(n)        //构造函数
    {
        VA=new T[n];
        HL=new list<Edgecode>[n];
    } 
    ~Graph()
    {
        delete [] VA;
        delete [] HL;
    }
    int Empty()const{return(sizeV);}
    int Full()const{return(sizeV==maxV);}
    int SizeV()const{return(sizeV);}
    int SizeE()const{return(sizeE);}


    double GetCost(const T&v1, const T&v2)const;                //按起点和终点，读取相应边的权值
    int FindNode(const T&v)const;                               //返回相应顶点的下标
    bool FindNode(T &v, int pos);                               //判断相应下标是否存在该顶点
    bool InsertV(const T&v);                                    //插入顶点
    bool InsertE(const T&v1, const T&v2, double weigh=MAXCOST);         //插入相应边
    bool DeleteV(const T&v);
    bool DeleteE(const T&v1, const T&v2);
    void ReadGraph(const char *filename);                       //从相应文件中读取图
    void WriteGraph(const char *filename);                      //向相应文件中写入图
    int InDegree(int i)const;                                  //得到结点的入度
    int OutDegree(int i)const;                                 //得到结点的出度

    /*重载输入符*/
    template<class U>
    friend ostream& operator<<(ostream &ostr, const Graph<U>& g);
    /*重载输出符*/
    template<class U>
    friend istream& operator>>(istream &istr, Graph<U> &g);

    /*广度遍历*/
    void BFS_nrec(list<T> &ls)const;
    void BFS_nrec(list<T> &ls, int pos, bool *visited)const;
    /*不存在广度遍历递归算法，除非修改数据结构*/
    

    /*深度遍历*/
    void DFS_rec(list<T> &Ls)const;
    void DFS_rec(list<T> &ls, int pos, bool *visited)const;
    void DFS_nrec(list<T> &ls)const;
    void DFS_nrec(list<T> &ls, int pos, bool *visited)const;


    /*适用于图的堆排序*/
    void BuildHeap(PathData *E, int size)const;
    void PercolateDown(PathData *E, int pos, int size)const;


    /*最小生成树，E表示最后储存最小二叉树信息的地方，ne为最小生成树边的个数*/
    bool Prim (const T&v, PathData *E, int ne)const;
    bool Kruskal(PathData *E, int ne)const;


    /*迪克特斯拉算法，最短路径*/
    bool Dijkstra(const T&v, PathData *E, double *D, int *P, int nv)const;
    /*弗洛伊德算法，最短路径*/
    void Floyd(double **P, int **D)const;


    /*打印路径信息*/
    void Print_path(PathData *E, int ne) const; 
    void Print_path(double *D, int *P) const;  
    void Print_path(double **P, int **D, int n=10000)const;   


    /*拓扑排序*/
    bool TopSort(int *t,int nv)const;
    bool TopSort(list<T>& l)const;              


    /*打印拓扑排序*/
    bool Print_top(int *t)const;
    bool Print_top(list<int> &l)const;


    /*关键路径*/
    void CriticalPath(double *VE,double *VL,int nv)const;


    /*打印关键路径*/
    void Print_CriticalPath(double *VE, double *VL,int *p=NULL);
    int Get_Top_Index(int*p,int pos)const;
};


/*重载输入符*/
template<class T>
istream& operator>>(istream& is, Graph<T>& g)
{
    char s[50];
    int n;
    double w;
    T v1,v2;
    is>>s>>n;
    for(int i=0;i<n;i++)
    {
        is>>v1;
        g.InsertV(v1);
    }
    is>>s>>n;
    for(int i=0;i<n;i++)
    {
        is>>v1>>v2>>w;
        g.InsertE(v1, v2, w);
    }
    return is;
}


/*重载输出符*/
template<class T>
ostream& operator<<(ostream &os,const Graph<T> &g)
{
    os<<"<Verteis>:\t"<<g.sizeV<<endl;
    os<<"<Edges>:  \t"<<g.sizeE<<endl;
    for(int i=0;i<g.sizeV;i++)
    {
        os<<i<<'-'<<g.VA[i]<<":";
        list<Edgecode >::iterator itr=g.HL[i].begin();
        for(;itr!=g.HL[i].end();itr++)
        {
            os<<'('<<(*itr).dest<<" , "<<(*itr).cost<<")  ";
        }
        os<<endl;
    }
    return os;
}
