#include<iostream>
#include<fstream>
#include<istream>
#include"E:\Pool_Birds\Projects_for_C++\heap\heap.h"
#include<queue>
#include<stack>
#include<list>
#include"graph.h"
using namespace std;


/*????б?*/
void Display_ls(list<char> ls)
{
    list<char>::iterator itr=ls.begin();
    for(;itr!=ls.end();itr++)
    {
        cout<<(*itr)<<"  ";
    }
    cout<<endl;
}

int main()
{
    char filename[]="city_info.txt";  
    Graph<PosNode> g;
    g.ReadGraph(filename);
    cout<<g;
    int size=g.SizeV();
    double **p=new double*[size];
    int **d=new int*[size];
    double *p_=new double[size];
    int *d_=new int[size];
    for(int i=0;i<=size;i++)
    {
        p[i]=new double[size];
        d[i]=new int[size];
    }
    string c1="西安",c2="武汉";
    PathData *E=new PathData[g.SizeV()-1];
    g.Floyd(p,d); 
    g.Print_path(p,d);
    string a1="西安";
    system("pause");
    int i;
    if(g.Dijkstra(a1,E,p_,d_,size))
    {
        cout<<"Djkstra: "<<endl;
        g.Print_path(p_,d_);
        g.Print_path(E,g.SizeV()-1);
    }
    system("pause");
    /* Graph<char> g;
    list<char> ls;  
    char filename[]={"graph_test_5.txt"};   
    g.ReadGraph(filename);
    int *p=new int[g.SizeV()];
    double *d=new double[g.SizeV()];
    int size=g.SizeV();
    // size=g.SizeV();
    // cout<<g;
    // g.DeleteV('C');
    // g.DFS_nrec(ls);
    // Display_ls(ls);
    double **p_=new double*[size];
    int **d_=new int*[size];
    double *VE=new double [size];
    double *VL=new double [size];
    // for(int i=0;i<size;i++)
    // {
    //     p_[i]=new double[size];
    //     d_[i]=new int[size];
    // }
    // for(int i=0;i<g.SizeV();i++)
    // {
    //     p[i]=-1;
    // }
    // cout<<g;
    // cout<<"indegree:\t"<<g.InDegree(0)<<endl;
    // cout<<"outdegree:\t"<<g.OutDegree(0)<<endl;
    cout<<g;
    if(g.TopSort(p, g.SizeV()))
    {
        cout<<"TopSort:"<<endl;
        g.Print_top(p);
    }
    cout<<"<<<<<<<<<<<<<<<"<<endl;
    g.CriticalPath(VE,VL,size);
    g.Print_CriticalPath(VE,VL,p);
    // g.InsertV('a');
    // g.InsertV('b');
    // g.InsertV('c');
    // g.InsertE('a', 'b', 100);
    // cout<<g;
    // cout<<g.Getcost('a', 'b');
    PathData *E=new PathData[g.SizeV()-1];
    //cout<<g;
    // if(g.Prim('A',E,g.SizeV()-1))
    // {
    //     cout<<"Prim: "<<endl;
    //     g.Print_path(E,g.SizeV()-1);
    // }
    // if(g.Kruskal(E, g.SizeV()-1))
    // {
    //     cout<<"Kruskal:"<<endl;
    //     g.Print_path(E,g.SizeV()-1);
    // }
    // if(g.Dijkstra('A',E,d,p,g.SizeV()))
    // {
    //     cout<<"Djkstra: "<<endl;
    //     g.Print_path(d,p);
    //     g.Print_path(E,g.SizeV()-1);
    // }
    // g.Floyd(p_,d_);
    // g.Print_path(p_,d_);
    //g.DFS_rec(ls);
    //Display_ls(ls);
    //ls.clear();
    //g.DFS_nrec(ls);
    //Display_ls(ls); */
    getchar();
    return 0;
}