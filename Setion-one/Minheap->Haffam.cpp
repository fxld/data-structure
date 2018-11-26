//
//  main.cpp
//  哈夫曼树的实现（最小堆）
//
//  Created by dream on 2018/11/13.
//  Copyright © 2018 dream. All rights reserved.
//

#include <iostream>
#include <stack>
using namespace std;

typedef class treenode *Huffman;
typedef class heapnode *Heap;

class treenode
{
public:
    int weight;
    Huffman left;
    Huffman right;
};
class heapnode
{
public:
    int size;
    Huffman array;
};

Heap Createheap(int n)
{
    Heap h=NULL;
    int a;
    h=new heapnode();
    h->size=n;
    h->array=new treenode[n+1];
    for (int i=1; i<=n; i++)
    {
        cin>>a;
        h->array[i].weight=a;
        h->array[i].right=h->array[i].left=NULL;
    }
    return h;
}

Heap CreateMinheap(Heap h)
{
    int parent,children;
    Huffman temp=NULL;
    temp=new treenode();
    for (int i=h->size/2; i>0; i--)
    {
        *temp=h->array[i];
        for (parent=i; parent*2<=h->size; parent=children)
        {
            children=parent*2;
            if (children!=h->size&&h->array[children].weight>h->array[children+1].weight)
            {
                children++;
            }
            if (temp->weight<h->array[children].weight)
            {
                break;
            }
            else
            {
                h->array[parent]=h->array[children];
            }
        }
        h->array[parent]=*temp;
    }
    for (int i=1; i<=h->size; i++)//输出最小生成堆
    {
        cout<<h->array[i].weight<<" ";
    }
    cout<<endl;
    return h;
}

void insertNode(Heap h,Huffman temp)
{
    int i;
    h->size=h->size+1;
    for (i=h->size;i>1 ; i=i/2)
    {
        if (h->array[i/2].weight<temp->weight)
        {
            break;
        }
        h->array[i]=h->array[i/2];
    }
    h->array[i]=*temp;
}

Huffman deleteNode(Heap h)
{
    Huffman min=NULL,temp=NULL;
    int parent,children;
    min=new treenode();
    temp=new treenode();
    *min=h->array[1];
    *temp=h->array[h->size--];
    for (parent=1; parent*2<=h->size; parent=children)
    {
        children=parent*2;
        if (children!=h->size&&h->array[children].weight>h->array[children+1].weight)
        {
            children++;
        }
        if (temp->weight<h->array[children].weight)
        {
            break;
        }
        else
        {
            h->array[parent]=h->array[children];
        }
    }
    h->array[parent]=*temp;
    return min;
}

Huffman buildTree(Heap h,int n)
{
    Huffman temp;
    int c;
    for (int i=1; i<n; i++)
    {
        temp=new treenode();
        temp->left=deleteNode(h);
        temp->right=deleteNode(h);
        temp->weight=temp->left->weight+temp->right->weight;
        c=temp->weight;
        insertNode(h, temp);
    }
    temp=deleteNode(h);
    return temp;
}

void MinCalendar(Huffman t,int weight)  //中序历遍哈夫曼树
{
    stack<treenode*> Sstack;
    Sstack.push(t);
    Huffman p=t;
    while (!Sstack.empty())
    {
        while (p)
        {
            p=p->left;
            Sstack.push(p);
        }
        Sstack.pop();
        if (!Sstack.empty())
        {
        p=Sstack.top();
        cout<<p->weight<<" ";
        weight=weight+p->weight;
        Sstack.pop();
        p=p->right;
        Sstack.push(p);
        }
    }
    cout<<weight-t->weight;
}

int main()
{
    Heap p;
    int n;
    int weight=0;
    Huffman T;
    cin>>n;
    p=Createheap(n);
    p=CreateMinheap(p);
    T=buildTree(p,n);
    cout<<T->weight<<endl;//输出哈夫曼树的根的权值
    MinCalendar(T,weight);
    return 0;
}
