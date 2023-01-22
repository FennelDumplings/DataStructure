#ifndef BINOMIALHEAP_H_INCLUDED
#define BINOMIALHEAP_H_INCLUDED

#include <math.h>
using namespace std;

typedef int BinoimalHType;


class BinomialHeap//��Ŭ����
{
private:
    struct BinomialHeapNode//��������ڵ���ͬ
    {
        BinoimalHType data;
        BinomialHeapNode *son;
        BinomialHeapNode *brother;

        BinomialHeapNode():son(nullptr),brother(nullptr){}
        BinomialHeapNode(BinoimalHType item, BinomialHeapNode *L=nullptr, BinomialHeapNode *R=nullptr):data(item),son(L),brother(R){}
        ~BinomialHeapNode(){}
    };


    BinomialHeapNode **forest;//ָ�����飬ɭ����ÿ����������
    int noOfTree; //�����ģ ���ĸ���

    BinomialHeapNode *mergeBinomialTree(BinomialHeapNode *t1, BinomialHeapNode *t2);//�鲢��������
    int findmin();//�Ҹ���С����
    void deleteTree(BinomialHeapNode *rt)//�ͷ�ɭ���е�һ����
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
