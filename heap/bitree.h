#ifndef BITREE_H_
#define BITREE_H_

#include<iostream>
#include<queue>
#include<vector>
#include<stack>
using namespace std;
template<class T>


struct BTNode
{
	T data;
	BTNode *left, *right;			//ָ��������Һ���
	BTNode(const T& item=T(), BTNode *lptr=NULL, BTNode *rptr=NULL):
	data(item), left(lptr), right(rptr){}

};//c++不支持typedef，自动简写BTNode


struct Loc
{//用以定义坐标，这里用于光标位置
	int x,y;
};


template<class T>
BTNode<T> * GetBTNode(const T& item, BTNode<T> *lp=NULL, BTNode<T> *rp=NULL)
//为什么要用const，因为const类型与其他类型不是互通的，前者定义BTNode时也是用了const
{
	BTNode<T> *p;
	p = new BTNode<T>(item, lp, rp);
	if(p==NULL)
	{
		cerr<<"Memorry allocation failure!"<<endl;
		exit(1);
	}
	return(p);
}


void Gotoxy(int x, int y)
{
	//将光标位置移动到x,y
	static int indent=0, level=0;
	if(y==0)
{
        indent=0;
        level=0;
    }
    if(level!=y)
    {
        cout<<endl;
        indent=0;
        level++;
    }
    cout.width(x-indent);
    indent=x;
}


template<class T>
void PrintTree(const BTNode<T> *t, int w=40)
{
	//垂直输出二叉树
	Loc f,item;
	int level=0,off=w/2;
	queue<const BTNode<T> *> btq;
	const BTNode<T> *bt;
	queue<Loc> locq;
	f.x=off;
	f.y=level;
	btq.push(t);
	locq.push(f);
	if(t==NULL)
	{
		return;
	}
	while(!btq.empty())
	{
		bt=btq.front();//front返回第一个元素
		btq.pop();//删除第一个元素，但不返回值
		item=locq.front();
		locq.pop();
		Gotoxy(item.x, item.y);
		cout<<bt->data;
		if(item.y!=level)
		{
			level++;
			off=off/2;
		}	
		if(bt->left)
		{
			btq.push(bt->left);
			f.x=item.x-off/2;
			f.y=item.y+1;
			locq.push(f);
		}
		if(bt->right)
		{
			btq.push(bt->right);
			f.x=item.x+off/2;
			f.y=item.y+1;
			locq.push(f);
		}
	}
	cout<<endl;
}


template<class T>
void LevelTraversal(const BTNode<T> *t)
{
	//层次遍历输出
	queue<const BTNode<T>*> btq;
	const BTNode<T> *bt;
	btq.push(t);
	while(!btq.empty())
	{
		bt=btq.front();
		btq.pop();
		cout<<bt->data<<"*";
		if(bt->left)
		{
			btq.push(bt->left);
		}
		if(bt->right)
		{
			btq.push(bt->right);
		}
	}
}


template<class T>

BTNode<T>* Transform_nrec(vector<T> vec)
{
	//将向量的顺序结构转化为二叉树，我这是自底向上的建，教材是自顶向下的建
	//这个函数应该是非递归算法，递归算法是直接建立二叉树，而不借助其他储存结构
	//好像有点问题。。。。
	if(vec.empty())
	{
		cout<<"FALSE VECTOR"<<endl;
		return NULL;
	}
	BTNode<T> *head, *left=NULL, *right=NULL;
	int i,j=0;
	int lc,lr;
	i=vec.size()-1;
	int size=vec.size();
	T data;
	vector< BTNode<T>* > btv;
	while(i>=0)
	{
		data=vec[i];
		if(2*(i+1)>size)
		{
			left=NULL;
			right=NULL;
		}
		if(2*(i+1)<=size)
		{
			lc=size-2*(i+1);
			left=btv[lc];
			right=NULL;
		}
		if((2*(i+1)+1)<=size)
		{
			lr=size-(2*(i+1)+1);
			right=btv[lr];
		}
		if(i>=0&&vec[i]==T())
		{
			i--;
			head=NULL;
			btv.push_back(head);
			continue;
		}
		head=GetBTNode(data, left, right);
		btv.push_back(head);	
		i--;	
	}
	return head;
	
}


template<class T>
BTNode<T>* Transform_rec(const stack<T> sta)
{
	if(sta.empty())
	{
		cout<<"FALSE VECTOR"<<endl;
		return NULL;
	}
	BTNode<T> *head, *left=NULL, *right=NULL;
	stack<T> s=sta;
	T data;
	while(!s.empty())
	{
		data=s.top();
		s.pop();
		head=GetBTNode(data, left, right);
	}
	return head;
}


template<class T>
void Preorder_rec(const BTNode<T> *t)
{
	//递归算法实现前序遍历
	//递归算法应该是不断调用自身函数，可以不用循环
	if(t==NULL)
	{
		return;
	}
	cout<<t->data;
	if(t->left)
	{
		Preorder_rec(t->left);
	}
	if(t->right)
	{
		Preorder_rec(t->right);
	}
}


template<class T>
void Preorder_nrec(const BTNode<T> *t)
{
	//非递归前序遍历
	//非递归应该是函数只被调用一次，需要用到循环
	stack< const BTNode<T> *> btq;//这个地方应该放调用stack先进后出，而不是先进先出
	while(t||!btq.empty())
	{
		if(t)
		{
			cout<<t->data;
			if(t->right)
			{
				btq.push(t->right);
			}
			t=t->left;
		}
		else
		{
			t=btq.top();
			btq.pop();
		}		
	}
}


template<class T>
void Midorder_rec(const BTNode<T> *t)
{
	//递归算法实现中序遍历
	if(t==NULL)
	{
		return;
	}
	if(t->left)
	{
		Midorder_rec(t->left);
	}
	cout<<t->data;
	if(t->right)
	{
		Midorder_rec(t->right);
	}
}


template<class T>
void Midorder_nrec(const BTNode<T> *t)
{
	//非递归中序遍历
	
	//这个地方应该放调用stack先进后出，而不是先进先出
	stack< const BTNode<T> *> btq;
	while(t||!btq.empty())
	{
		if(t)
		{
			btq.push(t);
			t=t->left;
		}
		else
		{
			t=btq.top();
			btq.pop();
			cout<<t->data;
			t=t->right;
		}		
	}
}


template<class T>
void Suforder_rec(const BTNode<T> *t)
{
	//递归算法实现后序遍历
	if(t==NULL)
	{
		return;
	}
	if(t->left)
	{
		Suforder_rec(t->left);
	}
	if(t->right)
	{
		Suforder_rec(t->right);
	}
	cout<<t->data;
}


template<class T>
void Suforder_nrec(const BTNode<T> *t)
{
	//后序非递归遍历
	stack<const BTNode<T>*> bts;
	stack<int> tags;//tag分为1，与2，当遇见2时才输出，用1
					//将左子树过渡到右子树
	int tag;
	const BTNode<T> *bt;
	while(t||!bts.empty())
	{
		if(t)
		{
			bts.push(t);
			tags.push(1);
			t=t->left;//用于到最左边的位置
		}
		else
		{
			//能到这儿的，t都是NULL
			//取一个，从bts中
			bt=bts.top();
			bts.pop();
			//取一个对应的标签
			tag=tags.top();
			tags.pop();
			if(tag==1)
			{
				//改变标签属性，借助根结点过渡到右子树
				tag=2;
				tags.push(tag);
				bts.push(bt);
				t=bt->right;
				//这一步比较精妙
			}
			else
			{
				//若改标签为2，则输出
				cout<<bt->data;	
			}
			
		}
	}
}


template<class T>
BTNode<T>* Preorder_rec_buildBT(vector<T> vec, int item=0)
{
	//使用前序遍历建立二叉树
	if(item>=vec.size())
	{
		return NULL;
	}
	BTNode<T> *head,*left=NULL,*right=NULL;
	head=GetBTNode(vec[item], left, right);
	head->left=Preorder_rec_buildBT(vec, 2*item+1);
	head->right=Preorder_rec_buildBT(vec, 2*item+2);
	return head;
}


template<class T>
int Partition(T* pi, int low, int high)
{
	//一次快速排序
    int i=low;
    int j=high;
    T temp=pi[i];
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


template<class T>
void QuickSort(T *pi, int low, int high)
{
	//递归快速排序
	if(low>=high)
	{
		return;
	}
	int m;
	m=Partition(pi,low,high);
	QuickSort(pi,low,m-1);
	QuickSort(pi,m+1,high);
}


template<class T>
void QuickSort(T* pi, int size)
{
	QuickSort(pi, 0, size-1);
}


template<class T>
void Power(vector<vector<T> > &outL, vector<T> &sL, vector<T> &pL, int pos=0)
{
	/*
	outL用于储存最后输出的幂集，sL用来存放初始元素，pl用来形成幂集中的元素
	pos表示的是当前sL所组的元素位置，是以前序遍历递归为模板
	*/
	if(sL.empty())
	{
		exit(1);
		cerr<<"基础元素错误！！！"<<endl;
		return;
	}
	if(pos==sL.size())
	{
		outL.push_back(pL);
		return;
	}
	pL.push_back(sL[pos]);
	Power(outL, sL, pL, pos+1);
	pL.pop_back();
	Power(outL, sL, pL, pos+1);
}


template<class T>
void PrintSet(vector<vector<T>> outl)
{
	//输出幂集vector嵌套
	vector<vector<char> >::iterator itr=outl.begin();
	for(;itr!=outl.end();itr++)
	{
		vector<char>::iterator itr2=(*itr).begin();
		for(;itr2!=(*itr).end();itr2++)
		{
			cout<<*itr2;
		}	
		cout<<'\t';
		//感动mama啊
	}
}


template<class T>
int Get_BT_Depth(BTNode<T> *t, int level)
{
	//获得二叉树的深度
	//这个有点问题
	if(t==NULL)
	{
		cerr<<"该二叉树不存在结点"<<endl;
		return level;
	}
	level++;
	if(t->left)
	{
		level=Get_BT_Depth(t->left, level);
	}
	else if(t->right)
	{
		level=Get_BT_Depth(t->right, level);
	}
	return level;
}


template<class T>
int Get_BT_Depth(BTNode<T> *t)
{
	/*总结，递归算法，就是一个判断条件，一个处理结构，一个本身函数调用
	由这三个部分组成
	这个层数是不加上根结点的，就是我以为的level-1*/
	if(t==NULL)
	{
		//NULL处返回了-1
		return -1;
	}
	int l=Get_BT_Depth(t->left);
	int r=Get_BT_Depth(t->right);
	return (1+(l>r?l:r));
}


void Hanoi(int n, char a, char b, char c)
{
	/*汉诺塔递归，这种只用看全局，用两个盘子推全部*/
	if(n<=0)
	{
		return;
	}
	if(n==1)
	{
		cout<<a<<"->"<<c<<endl;
	}
	else
	{
		Hanoi(n-1, a, c, b);
		cout<<a<<"->"<<c<<endl;
		Hanoi(n-1, b, a, c);
	}
}
 
template<class T>
BTNode<T> * CopyBT(BTNode<T> *t)
{
	//复制二叉树
	if(t==NULL)
	{
		return NULL;
	}
	BTNode<T> *left=CopyBT(t->left);
	BTNode<T> *right=CopyBT(t->right);
	return GetBTNode(t->data, left, right);
}


template<class T>
BTNode<T> *MakeLinked(T* pre, T* mid, int size)
{
	//前序和中序构成二叉树，贼经典
	if(size<=0)
	{
		return NULL;
	}
	BTNode<T> *head,*left, *right;
	T* item;
	int k;
	for(item=mid;item<mid+size;item++)
	{
		if(*item==*pre)
		{
			break;
		}
	}
	k=item-mid;
	left=MakeLinked(pre+1, mid, k);
	right=MakeLinked(pre+k+1, mid+k+1, size-k-1);
	head=GetBTNode(*pre, left, right);
	return head;
}



#endif