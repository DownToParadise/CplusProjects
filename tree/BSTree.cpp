#include<iostream>
#include"BSTree.h"
#include"bitree.h"
using namespace std;


/*返回最小值，如果不是二叉树则返回NULL*/
template<class T>
BTNode<T>* BSTree<T>::FindMin(BTNode<T> *t)const
{
    if(t!=NULL)
    {
        while((t->left)!=NULL)
            {
                t=t->left;
            }
    }
    return t;
}


/*返回最大值，如果不是二叉树则返回NULL*/
template<class T>
BTNode<T>* BSTree<T>::FindMax(BTNode<T> *t)const
{
    if(t!=NULL)
    {
        while((t->right)!=NULL)
        {
            t=t->right;
        }
    }
    return t;
}


/*寻找结点，若返回的值为NULL，则未找到，或输入的指针为空*/
template<class T>
BTNode<T>* BSTree<T>::FindNode(const T&x,BTNode<T>*t)const
{
    if(t==NULL)
    {
        return NULL;
    }
    while(t)
    {
        if(x<t->data)
        {
            t=t->left;
        }
        else if(x>t->data)
        {
            t=t->right;
        }
        else
        {
            return t;
        }  
    }
    return t;
}


/*清除整个二叉表*/
template<class T>
void BSTree<T>::Clear(BTNode<T> *&t)
{
    if(t==NULL)
    {
        return;
    }
    Clear(t->left);
    Clear(t->right);
    delete t;
    t=NULL;
}


/*查找并提取*/
template<class T>
bool BSTree<T>::Find(T&x)const
{
    BTNode<T>*t=FindNode(x,root);
    if(t!=NULL)
    {
        x=t->data;
        return 1;
    }
    return 0;
}


/*修改，若不存在该结点则插入该结点*/
template<class T>
void BSTree<T>::Update(const T&x)
{
    BTNode<T> *t=FindNode(x,root);
    if(t!=NULL)
    {
        t->data=x;
    }
    else
    {
        Insert(x);
    }  
}


/*插入一个数据至规定的结点*/
template<class T>
void BSTree<T>::Insert(const T&x,BTNode<T> *&t)
{
    if(t==NULL)
    {
        t=GetBTNode(x);
        t->data=x;
        size++;
        if(size==1)
        {
            root=t;
        }
    }
    else if(x<t->data)
    {
        Insert(x,t->left);
    }
    else if(x>t->data)
    {
        Insert(x,t->right);
    }
}


/*删除一个结点*/
template<class T>
void BSTree<T>::Remove(const T&x,BTNode<T> *&t)
{
    if(t==NULL)
    {
        return;
    }
    if(x<t->data)
    {
        Remove(x,t->left);
    }
    else if(x>t->data)
    {
        Remove(x,t->right);
    }
    else if(t->left!=NULL&&t->right!=NULL)
    {
        /*此处可以是右子树的最小值，也可以是左子树的最大值*/
        t->data=FindMin(t->right)->data;
        Remove(t->data,t->right);
    }
    else
    {
        BTNode<T> *old=t;
        t=(t->left!=NULL)?t->left:t->right;
        delete old;
        size--;
    }  
}


int main()
{
    BSTree<int> bst;
    int num=9;
    bst.Insert(8);
    bst.Insert(11);
    bst.Insert(10);
    bst.Insert(3);
    bst.Insert(2);
    bst.Insert(6);
    bst.Insert(4);
    bst.Insert(5);
    bst.PrintBSTree();
    cout<<"\ndelete '3'"<<endl;
    bst.Remove(3);
    bst.PrintBSTree();
    cout<<"\ninsert '3'"<<endl;
    bst.Insert(3);
    bst.PrintBSTree();
    getchar();
    return 0;
}