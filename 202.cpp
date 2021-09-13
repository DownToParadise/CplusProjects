#include<iostream>
#include<queue>
#include<vector>
//#include<windows>
using namespace std;


template<class T>
struct	BTNode
{
	T data;
	BTNode * left,*right;
	BTNode(T item=T(),BTNode* le=NULL,BTNode*ri=NULL)
	{
		data=item;
		left=le;
		right=ri;
	}
};
template<class T>
BTNode<T>* getBTNode(T item=0,BTNode<T> *le=NULL,BTNode<T> *ri=NULL)
{
	BTNode<T> *p;
	p=new BTNode<T>(item,le,ri);
	if(p==NULL)
	{
		cout<<"empty"<<endl;
		exit(1);
	}
	return p;
}


template<class T> //��α���
int Level(const BTNode<T> *t)
{
	if(t==NULL)
	{
		return 0; 
	}
	queue<const BTNode<T>*> Q;
	const BTNode<T>* p;
	Q.push(t);
	while(!Q.empty())
	{
		p=Q.front();
		Q.pop();
		cout<<p->data<<"  ";
		
		if(p->left)
		{	Q.push(p->left);}
		if(p->right)
		{	Q.push(p->right);}
	}
	return 0;
} 

template<class T>
class smallHeap
{
	int size;//���ݴ�С
	vector<T> vec;//��������	
public:
	void BuildHeap()//����Ϊ�ѣ�����С��������,С����
	{
		T temp;
		int i,j;
		for(i=1;i<size;i++)
			for(j=1;j<size-i;j++)
			{
				if(vec[j-1]>vec[j])
				{
					temp=vec[j-1];
					vec[j-1]=vec[j];
					vec[j]=temp;
				}
			}
	}
	smallHeap(vector<T>& a)//�����������
	{	
		vec=a;
		size=a.size();
		BuildHeap();
	}



	void inset(T &item)//�Ѳ���,β��
	{
		if(size==0)
			return;
		vec.push_back(item);
		size++;
		BuildHeap();
	}

	void headdelete()//��ɾ
	{
		int i;
		if(size==0)
			return;
		/*for(i=1;i<size;i++)
		{
			vec[i-1]=vec[i];
		}*/
		vec[0]=vec[size-1];
		vec.pop_back();
		BuildHeap();
		size--;
	}

	void taildelete()//βɾ
	{
		size--;
	}
	T top()//�����һ��������Сֵ
	{
		return vec[0];
	}
	void clear()//���
	{
		size=0;
	}
};




template <class T>
struct HufmNode
{
	BTNode <T>* t;
	int operator>(const HufmNode& h ){	return (t->data>h.t->data);}
	int operator>=(const HufmNode& h ){	return (t->data>=h.t->data);}
};

template <class T>
BTNode<T>* foundhfm(const T*pa,int n)
{
	HufmNode<T> hf;
	BTNode<T> *t,*left,*right;
	vector<HufmNode<T> > x;
	smallHeap<HufmNode<T> > H(x);
	for(int i=0;i<n;i++)
	{  
		t=getBTNode(pa[i]);
		hf.t=t;
		H.inset(hf);
	}
	
	for(int j=0;j<n;j++)
	{
		
		hf=H.top();
		left=hf.t;
		H.headdelete();
		hf=H.top();
		right=hf.t;
		H.headdelete();
		t=getBTNode(left->data+right->data,left,right);
		hf.t=t;
		H.inset(hf);
	}
	hf=H.top();
	H.headdelete();
	return hf.t;
}



int main()
{
	int c[]={1,2,3,4}; 	
	BTNode<int>* root;
    vector<int> b(c,c+5);
	smallHeap<int> a(b);
	cout<<a.top()<<endl;
	root= foundhfm(c,4);
	Level(root);
	return 0;
}
