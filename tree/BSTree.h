#include<queue>
#include<iostream>
#include"bitree.h"
template<class T> class BSTree;

// template<class T>
// class const_iterator
// {


// public:
// //protected:
//     BTNode<T>*current;
//     T& retrieve()const{return(current->data);}                  //检索函数
//     const_iterator(BTNode<T> *t){current=GoFarLeft(t);}         //构造函数
//     stack<BTNode<T>*> St;
//     BTNode<T> *GoFarLeft(BTNode<T>*t)
//     {
//         if(!t)
//         {
//             return(NULL);
//         }
//         while(t->left)
//         {
//             St.push(t);
//             t=t->left;
//         }
//         return t;
//     }
//     friend class BSTree<T>;
//     const_iterator():current(NULL){}
//     const T&operator*()const{return(retrieve());}
//     const_iterator& operator++()
//     {
//         if(current->right)
//         {
//             current=GoFarLeft(current->right);
//         }
//         else if (!St.empty())
//         {
//             current=St.top();
//             St.pop();
//         }
//         else
//         {
//             current=NULL;
//         }
//         return(*this); 
//     }
//     bool operator==(const const_iterator& rhs)const{return(current==rhs.current);}
//     bool operator!=(const const_iterator& rhs)const{return(current!=rhs.current);}
// };


/*目前最主要的问题，中序迭代器，是const_iterator未被继承*/
// template<class T>
// class iterator :public const_iterator<T>
// {
// protected:
//     iterator(BTNode<T>* t):const_iterator(t){}
//     friend class BSTree<T>;
// public:
//     iterator(){}//构造函数
//     T&operator*(){return(const_iterator<T>::retrieve());}
//     const T&operator*()const{return(const_iterator<T>::operator*());}
//     iterator<T>&operator++()
//     {
//         if(current->right)
//         {
//             const_iterator<T>::current=GoFarLeft(current->right);
//         }
//         else if (!St.empty())
//         {
//             current=St.top();
//             St.pop();
//         }
//         else
//         {
//             current=NULL;
//         }
//         return(*this); 
//     }
// };


template<class T>
class BSTree
{
private:
    BTNode<T> *root;
    int size;
    void Insert(const T&x,BTNode<T> *&t);
    void Remove(const T&x,BTNode<T> *&t);
    BTNode<T>* FindMin(BTNode<T> *t)const;
    BTNode<T>* FindMax(BTNode<T> *t)const;
    BTNode<T>* FindNode(const T&x,BTNode<T> *t)const;
    void Clear(BTNode<T> *&t);
    //void PrintTree(const BTNode<T>*t, int w)const;
public:
    BSTree():root(NULL),size(0){};
    ~BSTree(){Clear();}
    T& FindMin()const{return(FindMin(root));}
    T& FindMax()const{return(FindMax(root));}
    bool Find(const T&x)const{return(FindNode((x,root))!=NULL);}
    bool Find(T&x)const;
    bool Empty()const{return(size==0);}
    int Size(void){return(size==0);}
    void Clear(){Clear(root);}
    void Update(const T&v);
    void Insert(const T&x){Insert(x,root);}
    void Remove(const T&x){Remove(x,root);}
    void PrintBSTree(int w=40)const{PrintTree(root,w);}


    /* const_iterator<T> begin()const{return(const_iterator(root));}
    const_iterator<T> end()const{return(NULL);}
    iterator<T> begin(){return(iterator(root));}
    iterator<T> end(){return(NULL);} */
};