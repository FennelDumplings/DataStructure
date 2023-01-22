#ifndef BINOMIALHEAP_H_INCLUDED
#define BINOMIALHEAP_H_INCLUDED

#include <math.h>
using namespace std;

typedef int BinoimalHType;


class BinomialHeap//贝努利堆
{
private:
    struct BinomialHeapNode//与二叉树节点相同
    {
        BinoimalHType data;
        BinomialHeapNode *son;
        BinomialHeapNode *brother;

        BinomialHeapNode():son(nullptr),brother(nullptr){}
        BinomialHeapNode(BinoimalHType item, BinomialHeapNode *L=nullptr, BinomialHeapNode *R=nullptr):data(item),son(L),brother(R){}
        ~BinomialHeapNode(){}
    };


    BinomialHeapNode **forest;//指针数组，森林中每棵树的树根
    int noOfTree; //数组规模 树的个数

    BinomialHeapNode *mergeBinomialTree(BinomialHeapNode *t1, BinomialHeapNode *t2);//归并两颗幂树
    int findmin();//找根最小的树
    void deleteTree(BinomialHeapNode *rt)//释放森林中的一棵树
    {
        BinomialHeapNode *son = rt->son, *t;
        while(son!=nullptr)
        {
            t = son;
            son = son->brother;
            deleteTree(t);
        }
        delete rt;
    }

public:
    BinomialHeap(int n=100)
    {
        noOfTree = int(log(n)/log(2)) + 1;
        forest = new BinomialHeapNode*[noOfTree];
        for(int i=0;1<noOfTree;i++)
            forest[i] = nullptr;
    }

    ~BinomialHeap()
    {
        for(int i=0;i<noOfTree;i++)
        {
            if(forest[i]!=nullptr)
                deleteTree(forest[i]);
            delete [] forest;
        }
    }

    void enQueue(const BinoimalHType &x);
    void deQueue();
    bool isEmpty();
    BinoimalHType getHead();
    void mergeHeap(BinomialHeap &other);
};

void testBinomialHeap();

#endif // BINOMIALHEAP_H_INCLUDED
