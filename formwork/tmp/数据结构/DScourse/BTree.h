#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED
/*
typedef int BType;

const int idxSize = 5;
const int dataBlkSize = 20;

class BTree
{
private:
    struct idxNode
    {
        int type;//0:下一层是索引   1:下一层是数据
        BType key[idxSize-1];//关键字数组
        void *idx[idxSize];
        int len;//有效儿子数
        idxNode():len(1){}
    };
    struct dataNode
    {
        int len;   //有效记录数
        BType recode[dataBlkSize];
        dataNode():len(1){}
    };

    idxNode *root;

public:
    BTree():root(nullptr){}
    ~BTree(){makeEmpty(root);}
    bool findx(const BType &x)const {return findx(x,root);}
    void insertx(const BType &x);
    void removex(const BType &x);

private:
    void makeEmpty(idxNode *t);
    idxNode *insertx(const BType &x, idxNode *t);
    dataNode *insertData(const BType &x, dataNode *t);
    idxNode *sddIdxBlk(idxNode *n, idxNode *t);
    idxNode *addDataBlk(dataNode *n, idxNode *t);
};

void testBTree();
*/
#endif // BTREE_H_INCLUDED
