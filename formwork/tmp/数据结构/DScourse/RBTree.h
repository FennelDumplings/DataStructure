#ifndef RBTREE_H_INCLUDED
#define RBTREE_H_INCLUDED

#include <stack>
using namespace std;

typedef int RBType;

class RBTree
{
private:
    struct RBnode
    {
        RBType data;
        int color;//0Îªºì£¬1ÎªºÚ
        RBnode *left;
        RBnode *right;
        RBnode(const RBType &d, RBnode *p=nullptr, RBnode *q=nullptr, int h = 0)
        {
            data = d;
            left = p;
            right = q;
            color = h;
        }
    };
    RBnode *root;
public:
    RBTree(RBnode *t=nullptr){root=t;}
    ~RBTree(){clearTree(root);}
    bool findx(const RBType &x)const {return findx(x,root);}
    void insertx(const RBType &x);
    void removex(const RBType &x);

private:
    void clearTree(RBnode *t)
    {
        if(t->left!=nullptr)clearTree(t->left);
        if(t->right!=nullptr)clearTree(t->right);
        delete t;
    }
    bool findx(const RBType &x, RBnode *t)const;
    void LL(RBnode *&t);
    void LR(RBnode *&t);
    void RL(RBnode *&t);
    void RR(RBnode *&t);

    void reLink(RBnode *oldp,RBnode *newp, stack<RBnode *> &path);
    void insertReBalance(RBnode *t, stack<RBnode *> &path);
    void removeReBalance(RBnode *t, stack<RBnode *> &path);
};
void testRBTree();
#endif // RBTREE_H_INCLUDED
