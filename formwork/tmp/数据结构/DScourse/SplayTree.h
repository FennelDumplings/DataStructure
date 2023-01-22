#ifndef SPLAYTREE_H_INCLUDED
#define SPLAYTREE_H_INCLUDED

typedef int SplayType;

class SplayTree
{
private:
    struct node
    {
        SplayType data;
        node *left;
        node *right;
        node():left(nullptr),right(nullptr){}
        node(const SplayType &x, node *m = nullptr, node *n = nullptr):data(x),left(m),right(n){}
    };
    node *root;
public:
    SplayTree(){root=nullptr;}
    ~SplayTree(){clearTree(root);}
    bool findx(const SplayType &x);
    void insertx(const SplayType &x);
    void removex(const SplayType &x){removex(x,root);}
private:
    void clearTree(node *t)
    {
        if(t->left!=nullptr)clearTree(t->left);
        if(t->right!=nullptr)clearTree(t->right);
        delete t;
    }
    void removex(const SplayType &x, node * &t);
    enum splayNodeType{X,ZIG,ZAG,FALSE};
    splayNodeType findx(const SplayType &x, node * t);
    splayNodeType insertx(const SplayType &x, node * &t);
    void zigzig(node * &t);
    void zigzag(node * &t);
    void zagzig(node * &t);
    void zagzag(node * &t);
    void LL(node *&t);
    void LR(node *&t);
    void RL(node *&t);
    void RR(node *&t);
};

void testSplayTree();
#endif // SPLAYTREE_H_INCLUDED
