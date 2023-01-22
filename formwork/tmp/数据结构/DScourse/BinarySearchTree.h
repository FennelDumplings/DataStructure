#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED

typedef int BSTType;

class BinarySearchTree
{
private:
    struct BSTnode
    {
        BSTType data;
        BSTnode *left;
        BSTnode *right;
        BSTnode():left(nullptr),right(nullptr){}
        BSTnode(const BSTType &x, BSTnode *p=nullptr, BSTnode *q=nullptr):data(x),left(p),right(q){}
    };
    BSTnode *root;
public:
    BinarySearchTree(BSTnode *p = nullptr):root(p){}
    ~BinarySearchTree(){clearTree(root);}
    bool findx(const BSTType &x)const {return findx(x,root);}
    void insertx(const BSTType &x) {insertx(x,root);}
    void removex(const BSTType &x) {removex(x,root);}

private:
    void insertx(const BSTType &x, BSTnode * &t);
    void removex(const BSTType &x, BSTnode * &t);
    bool findx(const BSTType &x, BSTnode *t)const;
    void clearTree(BSTnode * &t);
};

void testBinarySearchTree();
#endif // BINARYSEARCHTREE_H_INCLUDED
