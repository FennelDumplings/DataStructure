#include "SplayTree.h"

bool SplayTree::findx(const SplayType &k)
{
    splayNodeType rn = findx(k,root);
    switch(rn)
    {
    case ZIG://伸展节点为根节点左儿子，LL
        LL(root);
        return true;
    case ZAG://伸展节点为根节点右儿子，RR
        RR(root);
        return true;
    case X://伸展节点为根节点
        return true;
    default:
        return false;
    }
}

void SplayTree::insertx(const SplayType &x)
{
    splayNodeType rn = insertx(x,root);
    switch(rn)
    {
    case ZIG://伸展节点为根节点左儿子，LL
        LL(root);
    case ZAG://伸展节点为根节点右儿子，RR
        RR(root);
    }
}

void SplayTree::removex(const SplayType &x, node * &t)
{
    if(t==nullptr) return;
    if(x < t->data) removex(x,t->left);
    if(x > t->data) removex(x,t->right);
    if(x == t->data)
    {
        if(t->left!=nullptr&&t->right!=nullptr)
        {
            node *tmp = t->right;
            while(tmp->left!=nullptr)
                tmp = tmp->left;
            t->data = tmp->data;
            removex(t->data,t->right);
        }
        else
        {
            node *oldNode = t;
            t = (t->left!=nullptr)?t->left:t->right;
            delete oldNode;
        }
    }
}

SplayTree::splayNodeType SplayTree::findx(const SplayType &x, node * t)
{
    splayNodeType rn;
    if(t==nullptr) return FALSE;
    if(x==t->data) return X;
    if(x<t->data)
    {
        rn = findx(x,t->left);
        switch(rn)
        {
        case ZIG:
            zigzig(root);
            return X;
        case ZAG:
            zigzag(root);
            return X;
        case X:
            return ZIG;
        default:
            return FALSE;
        }
    }
    else
    {
        rn = findx(x,t->right);
        switch(rn)
        {
        case ZIG:
            zagzig(root);
            return X;
        case ZAG:
            zagzag(root);
            return X;
        case X:
            return ZAG;
        default:
            return FALSE;
        }
    }
}

SplayTree::splayNodeType SplayTree::insertx(const SplayType &k, node * &t)
{
    splayNodeType rn;
    if(t==nullptr)
    {
        t = new node(k);
        return X;
    }
    if(k==t->data) return X;
    if(k<t->data)
    {
        rn = insertx(k,t->left);
        switch(rn)
        {
        case ZIG:
            zigzig(root);
            return X;
        case ZAG:
            zigzag(root);
            return X;
        case X:
            return ZIG;
        }
    }
    else
    {
        rn = insertx(k,t->right);
        switch(rn)
        {
        case ZIG:
            zagzig(root);
            return X;
        case ZAG:
            zagzag(root);
            return X;
        case X:
            return ZAG;
        }
    }
}

void SplayTree::zigzig(node * &t)
{
    LL(t);
    LL(t);
}
void SplayTree::zigzag(node * &t)
{
    LR(t);
}
void SplayTree::zagzig(node * &t)
{
    RL(t);
}
void SplayTree::zagzag(node * &t)
{
    RR(t);
    RR(t);
}

void SplayTree::LL(node *&t)
{
    node *tl = t->left;
    t->left = tl->right;
    tl->right = t;
    t = tl;
}
void SplayTree::LR(node *&t)
{
    RR(t->left);
    LL(t);
}
void SplayTree::RL(node *&t)
{
    LL(t->right);
    RR(t);
}
void SplayTree::RR(node *&t)
{
    node *tr = t->right;
    t->right = tr->left;
    tr->left = t;
    t = tr;
}

void testSplayTree()
{

}
