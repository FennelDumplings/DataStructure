#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED

#include<iostream>
using namespace std;

typedef int BTType;

class BinaryTree//链式二叉树
{
private:
    struct BTreeNode
    {
        BTType data;
        BTreeNode *left;
        BTreeNode *right;

        BTreeNode():left(NULL),right(NULL){}
        BTreeNode(BTType item, BTreeNode *L=nullptr, BTreeNode *R=nullptr):data(item),left(L),right(R){}
        ~BTreeNode(){}
    };
    BTreeNode *root;


public:
    BinaryTree():root(NULL){}
    BinaryTree(const BTType &value){root = new BTreeNode(value);}
    ~BinaryTree(){clearTree();};
    void clearTree()
    {
        if(root!=NULL)
            clearTree(root);
        root = NULL;
    }
    int height()const
    {
        return height(root);
    }
    int sizeTree()const
    {
        return sizeTree(root);
    }
    bool isEmpty()const{return root==NULL;}

    BTType getLeft()const{return root->left->data;}
    BTType getRight()const{return root->right->data;}
    BTType getRoot()const{return root->data;}

    void delLeft()
    {
        clearTree(root->left);
        root->left = NULL;
    }
    void delRight()
    {
        clearTree(root->right);
        root->right = NULL;
    }

    void makeTree(const BTType &x, BinaryTree &lt, BinaryTree &rt);
    //void createTree(BTType flag);//flag为空节点标记

    void preOrder()const
    {
        if(root==nullptr)
            return;
        preOrder(root);
    }
    void midOrder()const
    {
        if(root==nullptr)
            return;
        midOrder(root);
    }
    void postOrder()const
    {
        if(root==nullptr)
            return;
        postOrder(root);
    }

private:
    void clearTree(BTreeNode *t)
    {
        if(t->left!=nullptr)clearTree(t->left);
        if(t->right!=nullptr)clearTree(t->right);
        delete t;
    }
    int height(BTreeNode *t)const
    {
        if(t==nullptr)
            return 0;
        int lt = height(t->left);
        int rt = height(t->right);
        return 1 + ((lt>rt)?lt:rt);
    }
    int sizeTree(BTreeNode *t)const
    {
        if(t==nullptr)
            return 0;
        return 1 + sizeTree(t->left) + sizeTree(t->right);
    }

    void preOrder(BTreeNode *t)const
    {
        if(t==nullptr)
            return;
        cout << t->data;
        preOrder(t->left);
        preOrder(t->right);
    }
    void midOrder(BTreeNode *t)const
    {
        if(t==nullptr)
            return;
        midOrder(t->left);
        cout << t->data;
        midOrder(t->right);
    }
    void postOrder(BTreeNode *t)const
    {
        if(t==nullptr)
            return;
        postOrder(t->left);
        postOrder(t->right);
        cout << t->data;
    }
};


void testBinaryTree();

#endif // BINARYTREE_H_INCLUDED
