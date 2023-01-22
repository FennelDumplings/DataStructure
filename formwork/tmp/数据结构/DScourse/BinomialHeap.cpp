#include "BinomialHeap.h"
#include "math.h"

BinomialHeap::BinomialHeapNode * BinomialHeap::mergeBinomialTree(BinomialHeapNode *t1, BinomialHeapNode *t2)
{
    BinomialHeapNode *min1, *max1;

    if(t1->data < t2->data)
    {
        min1 = t1;
        max1 = t2;
    }
    else
    {
        min1 = t2;
        max1 = t1;
    }

    if(min1->son==nullptr)
        min1->son = max1;
    else
    {
        BinomialHeapNode *tmp = min1->son;
        while(tmp->brother!=nullptr)
            tmp = tmp->brother;
        tmp->brother = max1;
    }
    return min1;
}

int BinomialHeap::findmin()
{
    int min1;
    int i=0;
    for(;i<noOfTree&&forest[i]==nullptr;++i);
    min1 = i;

    for(;i<noOfTree;++i)
        if(forest[i]!=nullptr&&forest[i]->data<forest[min1]->data)
            min1 = i;

    return min1;
}

void BinomialHeap::enQueue(const BinoimalHType &x)
{
    BinomialHeap tmp(1);
    tmp.forest[0] = new BinomialHeapNode(x);
    mergeHeap(tmp);
}

void BinomialHeap::deQueue()
{
    int min1 = findmin();//找到根节点最小的树
    if(min1==0)
    {
        delete forest[0];
        forest[0] = nullptr;
        return;
    }

    BinomialHeapNode *t = forest[min1];////含最小根的树
    BinomialHeapNode *son, *brother;
    int sizeOfQueue = int(pow(2,min1)-1);//根节点最小的树的子树个数
    BinomialHeap tmp(sizeOfQueue);//存储删根节点后产生的子树
    forest[min1] = nullptr;//删根节点最小的树

    son = t->son;//第一棵子树
    delete t;
    int i=0;
    do
    {
        tmp.forest[i++] = son;
        brother = son->brother;
        son->brother = nullptr;
    }while((son=brother)!=nullptr);

    mergeHeap(tmp);
}

bool BinomialHeap::isEmpty()
{
    for(int i=0;i<noOfTree;++i)
    {
        if(forest[i]!=nullptr)
            return false;
    }
    return true;
}

BinoimalHType BinomialHeap::getHead()
{
    int pos = findmin();
    return forest[pos]->data;
}


void BinomialHeap::mergeHeap(BinomialHeap &other)
{
    BinomialHeapNode **tmp  = forest;
    int tmpSize = noOfTree;//当前队列的信息
    int min1 = noOfTree < other.noOfTree ? noOfTree : other.noOfTree;//规模较小的森林的规模

    int i;

    if(noOfTree < other.noOfTree)//确定归并后的森林规模
    {
        noOfTree = other.noOfTree;
        if(other.forest[noOfTree]!=nullptr)
            ++noOfTree;
    }
    else if(forest[noOfTree]!=nullptr)
        ++noOfTree;

    forest = new BinomialHeapNode *[noOfTree];//为归并后的队列申请空间
    for(i=0;i<noOfTree;++i)
    {
        forest[i] = nullptr;
    }


    BinomialHeapNode *carry;//进位
    carry = nullptr;
    for(i=0;i<min1;++i)
    {
        if(carry==nullptr)
        {
            if(tmp[i]==nullptr)
                forest[i] = other.forest[i];
            else
            {
                if(other.forest[i]==nullptr)
                    forest[i] = tmp[i];
                else
                    carry = mergeBinomialTree(other.forest[i],tmp[i]);
            }
        }
        else
        {
            if(tmp[i]!=nullptr&&other.forest[i]!=nullptr)
            {
                forest[i] = carry;
                carry = mergeBinomialTree(other.forest[i],tmp[i]);
            }
            else
            {
                if(tmp[i]==nullptr&&other.forest[i]==nullptr)
                {
                    forest[i] = carry;
                    carry = nullptr;
                }
                else if(tmp[i]==nullptr)
                    carry = mergeBinomialTree(other.forest[i],carry);
                else
                    carry = mergeBinomialTree(tmp[i],carry);
            }
        }
    }

    //一个队列已经结束
    if(other.noOfTree==min1)//other已经结束
    {
        for(;i<tmpSize;++i)
        {
            if(carry==nullptr)
                forest[i] = tmp[i];
            else if(tmp[i]==nullptr)
            {
                forest[i] = carry;
                carry = nullptr;
            }
            else
                carry = mergeBinomialTree(tmp[i],carry);
        }
    }
    else//当前的队列结束
    {
        for(;i<other.noOfTree;++i)
        {
            if(carry==nullptr)
                forest[i] = other.forest[i];
            else if(other.forest[i]==nullptr)
            {
                forest[i] = carry;
                carry = nullptr;
            }
            else
                carry = mergeBinomialTree(other.forest[i],carry);
        }
    }
    if(carry!=nullptr)
        forest[i] = carry;

    for(i=0;i<other.noOfTree;++i)
        other.forest[i]=nullptr;
    delete [] tmp;
}


void testBinomialHeap()
{

}
