#include "RBTree.h"

#include <stack>
using namespace std;

void RBTree::reLink(RBnode *oldp,RBnode *newp, stack<RBnode *> &path)//path����������������·��
{
    if(path.empty())
        root = newp; //·��Ϊ�գ�����ڵ�Ϊ����
    else
    {
        RBnode *grandParent = path.top();
        path.pop();
        if(grandParent->left==oldp)
            grandParent->left = newp;
        else
            grandParent->right = newp;
        path.push(grandParent);
    }
}

bool RBTree::findx(const RBType &x, RBnode *t)const
{
    if(t==nullptr) return false;
    else if(t->data > x) return findx(x,t->left);
    else if(t->data < x) return findx(x,t->right);
    else return true;
}

void RBTree::LL(RBnode *&t)
{
    RBnode *tl = t->left;
    t->left = tl->right;
    tl->right = t;
    t = tl;
}
void RBTree::LR(RBnode *&t)
{
    RR(t->left);
    LL(t);
}
void RBTree::RL(RBnode *&t)
{
    LL(t->right);
    RR(t);
}
void RBTree::RR(RBnode *&t)
{
    RBnode *tr = t->right;
    t->right = tr->left;
    tr->left = t;
    t = tr;
}

void RBTree::insertx(const RBType &x)
{
    stack<RBnode *> path;//����������������·��
    RBnode *t,*parent;

    if(root==nullptr)//�ڿ�������
    {
        root = new RBnode(x,nullptr,nullptr,1);
        return;
    }
    t = root;
    while(t!=nullptr&&t->data != x)//Ѱ��λ�ã���·����Ϣ����ջ
    {
        path.push(t);
        if(t->data<x)
            t = t->right;
        else
            t = t->left;
    }
    if(t!=nullptr) return;//�ҵ��ظ��ڵ㣬��������

    //ִ�в���
    t = new RBnode(x,nullptr,nullptr);
    parent = path.top();
    path.pop();
    if(x<parent->data)
        parent->left=t;
    else
        parent->right = t;

    if(parent->color==1) return;//���ڵ�Ϊ�ڣ����õ���

    path.push(parent);
    insertReBalance(t, path);
}

void RBTree::removex(const RBType &x)
{
    stack<RBnode *> path;//������ɾ�ڵ��·��
    RBnode *t=root,*old,*parent=nullptr;

    while(t!=nullptr&&t->data != x)//Ѱ��λ�ã���·����Ϣ����ջ
    {
        path.push(t);
        if(t->data<x)
            t = t->right;
        else
            t = t->left;
    }
    if(t==nullptr) return;//û�ҵ���ɾ�㣬����ɾ��

    //������ڵ㲢���
    if(t->left!=nullptr&&t->right!=nullptr)
    {
        path.push(t);
        old=t;
        t=t->right;
        while(t->left!=nullptr)
        {
            path.push(t);
            t = t->left;
        }
        old->data=t->data;
    }
    //ִ��ɾ��
    if(t==root)//ɾ���ڵ�
    {
        root = (t->left?t->left:t->right);
        if(root!=nullptr)
            root->color = 1;
        return;
    }

    //ɾҶ�ڵ��ֻ��һ�����ӵĽڵ�
    parent = path.top();
    path.pop();
    old = t;
    t = (t->left?t->left:t->right);
    if(parent->left==old)
        parent->left=t;
    else
        parent->right = t;

    if(old->color==0)//ɾ��ڵ�
    {
        delete old;
        return;
    }

    delete old;

    if(t!=nullptr)//��һ�������
    {
        t->color=1;
        return;
    }

    //ɾ���Ǻڽڵ㣬��ʼ����

    path.push(parent);
    removeReBalance(t,path);
}

void RBTree::insertReBalance(RBnode *t, stack<RBnode *> &path)
{
    RBnode *parent,*grandParent,*uncle,*rootOfSunTree;
    parent = path.top();
    path.pop();
    while(parent->color==0)//���ڵ��Ǻ�ɫ����Ҫ����
    {
        if(parent==root)
        {
            parent->color=1;
            return;
        }
        grandParent = rootOfSunTree = path.top();
        path.pop();
        if(grandParent->data > parent -> data)//�ҳ�����ڵ�
            uncle = grandParent -> right;
        else
            uncle = grandParent -> left;

        if(uncle==nullptr||uncle->color==1)//���1
        {
            if(grandParent->left == parent)
            {
                if(t == parent->left)//LLb
                {
                    parent->color = 1;
                    grandParent->color=0;
                    LL(grandParent);
                }
                else//LRb
                {
                    grandParent->color = 0;
                    t->color=1;
                    LR(grandParent);
                }
            }
            else if(t==parent->right)//RRb
            {
                parent->color = 1;
                grandParent->color=0;
                RR(grandParent);
            }
            else
            {
                grandParent->color = 0;
                t->color=1;
                RL(grandParent);
            }
            reLink(rootOfSunTree,grandParent,path);
            return;
        }
        else//���2
        {
            grandParent->color=0;
            parent->color=1;
            uncle->color=1;
            if(root==grandParent)
            {
                root->color=1;
                return;
            }
            t=grandParent;
            parent = path.top();
            path.pop();
        }
    }
}

void RBTree::removeReBalance(RBnode *t, stack<RBnode *> &path)
{
    RBnode *parent,*sibling, *rootOfSubTree;

    parent = rootOfSubTree = path.top();
    path.pop();

    while(parent!=nullptr)//����L0,R0�����2
    {
        if(parent->left==t)
            sibling = parent->right;
        else
            sibling = parent->left;

        if(sibling->color==0)
        {
            sibling->color = 1;
            parent->color=0;
            if(parent->left==t)
                RR(parent);
            else
                LL(parent);
            reLink(rootOfSubTree,parent,path);
            path.push(parent);
            parent=rootOfSubTree;
        }
        else//�ֵ��Ǻڽڵ�
        {
            if((sibling->left==nullptr||sibling->left->color==1)&&(sibling->right==nullptr||sibling->right->color==1))
            //L0��R0
            {
                sibling->color = 0;
                if(parent->color==0)
                {
                    parent->color=1;
                    return;
                }
                else
                {
                    t = parent;
                    if(t==root)
                        return;
                    else
                    {
                        parent = rootOfSubTree = path.top();
                        path.pop();
                    }

                }
            }
            else
                break;
        }
    }

    if(parent->left==t)//�ֵ����Ҷ���
    {
        if(sibling->left!=nullptr&&sibling->left->color==0)//R1R��R2
        {
            sibling->left->color = parent->color;
            parent->color=1;
            LR(parent);
            reLink(rootOfSubTree,parent,path);
        }
        else//R1R
        {
            sibling->color = parent->color;
            sibling->right->color = 1;
            parent->color = 1;
            LL(parent);
            reLink(rootOfSubTree,parent,path);
        }
    }
    else//�ֵ��������
    {
        if(sibling->right!=nullptr&&sibling->right->color==0)//L1R��L2
        {
            sibling->right->color = parent->color;
            parent->color=1;
            LR(parent);
            reLink(rootOfSubTree,parent,path);
        }
        else//L1L
        {
            sibling->color = parent->color;
            sibling->left->color = 1;
            parent->color = 1;
            LL(parent);
            reLink(rootOfSubTree,parent,path);
        }
    }
}


void testRBTree()
{

}
