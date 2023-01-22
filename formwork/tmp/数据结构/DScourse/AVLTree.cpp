#include "AVLTree.h"

bool AVLTree::findx(const AVLType &x, AVLnode *t)const
{
    if(t==nullptr) return false;
    else if(t->data > x) return findx(x,t->left);
    else if(t->data < x) return findx(x,t->right);
    else return true;
}

void AVLTree::insertx(const AVLType &x, AVLnode * &t)
{
    if(t==nullptr)//空树上插入
        t = new AVLnode(x,nullptr,nullptr);
    else if(x < t->data)//左子树上插入
    {
        insertx(x,t->left);
        if(height(t->left)-height(t->right)==2)//LL or LR
            if(x<t->left->data)
                LL(t);
            else
                LR(t);
    }
    else if(x > t->data)//右子树上插入
    {
        insertx(x,t->right);
        if(height(t->right)-height(t->left)==2)
            if(x<t->right->data)
                RL(t);
            else
                RR(t);
    }
    //重新计算t的高度
    t->height = maxab(height(t->left),height(t->right)) + 1;
}

bool AVLTree::removex(const AVLType &x, AVLnode * &t)
{
    bool stop = false;
    int subTree; //1表说删除发生在左子树，2表示发生在右子树

    if(t==nullptr)
        return true;
    if(x<t->data)
    {
        stop = removex(x,t->left);
        subTree = 1;
    }
    else if(x>t->data)
    {
        stop = removex(x,t->right);
        subTree = 2;
    }
    else
    {
        if(t->left!=nullptr&&t->right!=nullptr)
        {
            AVLnode *tmp = t->right;
            while(tmp->left!=nullptr)
                tmp = tmp->left;
            t->data = tmp->data;
            stop = removex(t->data,t->right);
            subTree = 2;
        }
        else
        {
            AVLnode *oldNode = t;
            t = (t->left!=nullptr)?t->left:t->right;
            delete oldNode;
            return false;
        }
    }
    if(stop)
        return true;

    //调整平衡
    int bf;//删除前t的平衡因子
    switch(subTree)//删除发生在左子树
    {
    case 1:
        bf = height(t->left) - height(t->right) + 1;//此时删除已经完成，需要+1
        if(bf==0) return true;
        if(bf==1) return false;
        if(bf==-1)
        {
            int bfr = height(t->right->left) - height(t->right->right);
            switch(bfr)
            {
            case 0:
                RR(t);
                return true;
            case -1:
                RR(t);
                return false;
            default:
                RL(t);
                return false;
            }
        }
        break;
    case 2://删除发生在右子树
        bf = height(t->left) - height(t->right) - 1;
        if(bf==0) return true;
        if(bf==-1) return false;
        if(bf==1)
        {
            int bfl = height(t->right->left) - height(t->right->right);
            switch(bfl)
            {
            case 0:
                LL(t);
                return true;
            case -1:
                LL(t);
                return false;
            default:
                LR(t);
                return false;
            }
        }
    }

}

void AVLTree::LL(AVLnode *&t)
{
    AVLnode *tl = t->left;
    t->left = tl->right;
    tl->right = t;
    t->height = maxab(height(t->left),height(t->right)) + 1;
    tl->height = maxab(height(tl->left),height(t)) + 1;
    t = tl;
}
void AVLTree::LR(AVLnode *&t)
{
    RR(t->left);
    LL(t);
}
void AVLTree::RL(AVLnode *&t)
{
    LL(t->right);
    RR(t);
}
void AVLTree::RR(AVLnode *&t)
{
    AVLnode *tr = t->right;
    t->right = tr->left;
    tr->left = t;
    t->height = maxab(height(t->left),height(t->right)) + 1;
    tr->height = maxab(height(tr->right),height(t)) + 1;
    t = tr;
}

void testAVLTree()
{

}
