#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED

typedef int AVLType;

class AVLTree
{
private:
    struct AVLnode
    {
        AVLType data;
        int height;
        AVLnode *left;
        AVLnode *right;
        AVLnode(const AVLType &d, AVLnode *p=nullptr, AVLnode *q=nullptr, int h = 0)
        {
            data = d;
            left = p;
            right = q;
            height = h;
        }
    };
    AVLnode *root;
public:
    AVLTree(AVLnode *t=nullptr){root=t;}
    ~AVLTree(){clearTree(root);}
    bool findx(const AVLType &x)const {return findx(x,root);}
    void insertx(const AVLType &x) {insertx(x,root);}
    void removex(const AVLType &x) {removex(x,root);}

private:
    void clearTree(AVLnode *t)
    {
        if(t->left!=nullptr)clearTree(t->left);
        if(t->right!=nullptr)clearTree(t->right);
        delete t;
    }
    void insertx(const AVLType &x, AVLnode * &t);
    bool removex(const AVLType &x, AVLnode * &t);
    bool findx(const AVLType &x, AVLnode *t)const;
    int height(AVLnode *t)const
    {
        return t==nullptr?-1:t->height;
    }
    void LL(AVLnode *&t);
    void LR(AVLnode *&t);
    void RL(AVLnode *&t);
    void RR(AVLnode *&t);
    int maxab(int a, int b){return (a>b)?a:b;}
};

void testAVLTree();
#endif // AVLTREE_H_INCLUDED
