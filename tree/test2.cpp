#include<iosteram>
using namesapce std;

template<class T>
class a1
{
protected:
    int A1;
public:
    a1(int a):a1(a){}

};

template<class T>
class a2:public a1
{
public:
    void display_a1(void)const
    {
        cout<<A1;
    }
}
int main()
{
    a1 a(2);
    a2 A;
    
}