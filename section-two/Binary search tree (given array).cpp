#include <iostream>
#include <stack>

using namespace std;

typedef class TreeNode* pTree;

class TreeNode{
public:
    int weight;
    pTree left;
    pTree right;
};

void Sort(int *&array,int n)
{
    int temp,i,j;
    for (i=1; i<n; i++)
    {
        temp=array[i];
        for (j=i-1; j>=0; j--)
        {
            if (array[j]<temp)
            {
                break;
            }
            array[j+1]=array[j];
        }
        array[j+1]=temp;
    }
}

pTree twoSetion(pTree *&p,int left,int right)
{
    if (left==right)
    {
        return p[left];
    }
    if (left>right&&right+1==left)
    {
        return NULL;
    }
    int tempMid=(left+right)/2;
    p[tempMid]->left=twoSetion(p,left,tempMid-1);
    p[tempMid]->right=twoSetion(p,tempMid+1,right);
    return p[tempMid];
}

pTree create(int n)
{
    pTree *p;
    int *temp;
    int temp2[100];
    temp=new int [n];
    int i;
    for (i=0; i<n; i++)
    {
        cin>>temp[i];
    }
    Sort(temp,n);
    for (i=0; i<n; i++)
    {
        temp2[i]=temp[i];
    }
    p=new TreeNode* [n];
    for (int i=0; i<n; i++)
    {
        p[i]=new TreeNode();
        p[i]->weight=temp[i];
        p[i]->left=NULL;
        p[i]->right=NULL;
    }
    delete temp;
    return twoSetion(p, 0, n-1);
}

void Insert(int key,pTree &temp)
{
    pTree p=temp;
    pTree p2;
    if (p==NULL)
    {
        temp=new TreeNode();
        temp->weight=key;
        temp->left=NULL;
        temp->right=NULL;
    }
    while (p)
    {
        p2=p;
        if (key>=p->weight)
        {
            p=p->right;
            if (p==NULL)
            {
                p2->right=new TreeNode();
                p=p2->right;
                p->weight=key;
                p->left=NULL;
                p->right=NULL;
                break;
            }
        }
        else if(key<p->weight)
        {
            p=p->left;
            if (p==NULL)
            {
                p2->left=new TreeNode();
                p=p2->left;
                p->weight=key;
                p->left=NULL;
                p->right=NULL;
                break;
            }
        }
    }
}

pTree create2(int n,pTree tree) //非递归
{
    int *temp;
    temp= new int [n];
    for (int i=0; i<n; i++)
    {
        cin>>temp[i];
        Insert(temp[i], tree);
    }
    return tree;
}

pTree Delete(pTree &temp,int key)
{
    if (temp==NULL)
    {
        cout<<"二叉搜索树不存在"<<endl;
        return NULL;
    }
    if (temp->weight>key)
    {
        temp->left=Delete(temp->left,key);
    }
    else if(temp->weight<key)
    {
        temp->right=Delete(temp->right,key);
    }
    else
    {
        if(temp->left==NULL)
        {
            temp=temp->right;
        }
        else if(temp->right==NULL)
        {
            temp=temp->left;
        }
        else
        {
            pTree p=temp->right;
            p=new TreeNode();
            while (p->left)
            {
                p=p->left;
            }
            temp->weight=p->weight;
            temp->right =Delete(temp->right,key);
        }
    }
    return temp;
}

/*
 这个非递归删除策略是：为了保证删除h该节点后的树还是二叉搜索树，结合性质，应该找左子树的最右子节点来替换，因为该节点是左子树weight最大的点。倘若该节点不存在左子树，则找该节点的右子树最左子节点，来代替，原因同上反之。倘若左子树没有最右节点右子树没有最左节点，则需要按照二分创建规则来创建这颗二叉树再删除。
 */
void Delete2(pTree &temp,int key) //非递归版本
{
    int flag=-1;
    pTree p=temp;   //当前节点
    pTree parent;  //找到节点的父亲节点
    pTree p3;      // 找到的节点
    while (p)      //找到要删除的节点
    {
        if (key>p->weight)
        {
            parent=p;
            flag=1;
            p=p->right;
        }
        else if(key<p->weight)
        {
            parent=p;
            flag=0;
            p=p->left;
        }
        else
        {
            break;
        }
    }
    if (p==NULL)   //f为空 即不存在该要删除的节点
    {
        cout<<"要求删除的数在二叉搜索树中不存在"<<endl;
        return ;
    }
    p3=p;      //暂时保存一下当前节点
    if(p->left!=NULL&&p->left->right!=NULL)
    {
        parent=p;
        p=p->left;
        while (p->right)
        {
            parent=p;
            p=p->right;
        }
        p3->weight=p->weight;
        if(p->left==NULL){
          parent->right=NULL;
            return ;
        }
        parent->right=p->left;
        return ;
    }
    else if(p->right!=NULL&&p->right->left!=NULL)
    {
        parent=p;
        p=p->right;
        while (p->left)
        {
            parent=p;
            p=p->left;
        }
        p3->weight=p->weight;
        if (p->right==NULL)
        {
            parent->left=NULL;
            return ;
        }
        parent->left=p->right;
        return ;
    }
    else if(p->left!=NULL&&p->left->right==NULL&&p!=temp)
    {
        p=p->left;
        if (flag)
        {
            parent->right=p->left;
            if (p3->right!=NULL)
            {
                p->left->right=p3->right;
            }
            return;
        }
        else if(flag==0)
        {
            parent->left=p->left;
            if (p3->right!=NULL)
            {
                p->left->right=p3->right;
            }
            return ;
        }
    }
    else if(p->left==NULL&&p->right!=NULL)
    {
        p=p->right;
        if (flag)
        {
            parent->right=p;
        }
        else if(flag==0)
        {
            parent->left=p;
        }
        return ;
    }
    else if(p->left==NULL&&p->right==NULL&&p!=temp)
    {
        if (flag) {
            parent->right=NULL;
            return ;
        }
        else if(flag==0)
        {
            parent->left=NULL;
            return ;
        }
    }
    else if(p->left==NULL&&p->right==NULL&&p==temp)
    {
        delete temp;
    }
    else if(p->left->right==NULL&&p->right->left==NULL&&p==temp)
    {
        p->left->right=p->right;
        temp=p->left;
        return ;
    }
}

void frontCalendar(pTree &temp)
{
    stack<pTree> StackpTree;
    pTree p=temp;
    StackpTree.push(temp);
    while (!StackpTree.empty())
    {
        cout<<p->weight;
        if (p->right!=NULL)
        {
            StackpTree.push(p->right);
        }
        if (p->left!=NULL)
        {
            p=p->left;
        }
        else
        {
            p=StackpTree.top();
            StackpTree.pop();
        }
    }
    cout<<endl;
}

void MidCalendat(pTree &temp)
{
    stack<pTree> StackPtree;
    pTree p=temp;
    while (p||!StackPtree.empty())
    {
        if (p)
        {
            StackPtree.push(p);
            p=p->left;
        }
        else
        {
            p=StackPtree.top();
            StackPtree.pop();
            cout<<p->weight;
            p=p->right;
        }
    }
    cout<<endl;
}

int main()
{
    int n;
    cin>>n;
    pTree p=NULL;
    p=create(n);
    frontCalendar(p);
    MidCalendat(p);
    int key;
    cin>>key;
    Insert(key, p);
    frontCalendar(p);
    MidCalendat(p);
    cin>>key;
    Delete(p, key);
    frontCalendar(p);
    MidCalendat(p);
    return 0;
}
