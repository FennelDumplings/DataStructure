#include "BinarySearchTree.h"



void BinarySearchTree::insertx(const BSTType &x, BSTnode * &t)//注意是指针的引用
{
    if(t==nullptr)
        t = new BSTnode(x,nullptr,nullptr);
    else if(t->data > x) insertx(x,t->left);
    else insertx(x, t->right);
}

void BinarySearchTree::removex(const BSTType &x, BSTnode * &t)
{
    if(t==nullptr) return;
    if(x < t->data) removex(x,t->left);
    if(x > t->data) removex(x,t->right);
    if(x == t->data)
    {
        if(t->left!=nullptr&&t->right!=nullptr)
        {
            BSTnode *tmp = t->right;
            while(tmp->left!=nullptr)
                tmp = tmp->left;
            t->data = tmp->data;
            removex(t->data,t->right);
        }
        else
        {
            BSTnode *oldNode = t;
            t = (t->left!=nullptr)?t->left:t->right;
            delete oldNode;
        }
    }
}


bool BinarySearchTree::findx(const BSTType &x, BSTnode *t)const
{
    if(t==nullptr) return false;
    else if(t->data > x) return findx(x,t->left);
    else if(t->data < x) return findx(x,t->right);
    else return true;
}

void BinarySearchTree::clearTree(BSTnode * &t)
{
    if(t->left!=nullptr)clearTree(t->left);
    if(t->right!=nullptr)clearTree(t->right);
    delete t;
}



void testBinarySearchTree()
{

}
