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
    int min1 = findmin();//�ҵ����ڵ���С����
    if(min1==0)
    {
        delete forest[0];
        forest[0] = nullptr;
        return;
    }

    BinomialHeapNode *t = forest[min1];////����С������
    BinomialHeapNode *son, *brother;
    int sizeOfQueue = int(pow(2,min1)-1);//���ڵ���С��������������
    BinomialHeap tmp(sizeOfQueue);//�洢ɾ���ڵ�����������
    forest[min1] = nullptr;//ɾ���ڵ���С����

    son = t->son;//��һ������
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
    int tmpSize = noOfTree;//��ǰ���е���Ϣ
    int min1 = noOfTree < other.noOfTree ? noOfTree : other.noOfTree;//��ģ��С��ɭ�ֵĹ�ģ

    int i;

    if(noOfTree < other.noOfTree)//ȷ���鲢���ɭ�ֹ�ģ
    {
        noOfTree = other.noOfTree;
        if(other.forest[noOfTree]!=nullptr)
            ++noOfTree;
    }
    else if(forest[noOfTree]!=nullptr)
        ++noOfTree;

    forest = new BinomialHeapNode *[noOfTree];//Ϊ�鲢��Ķ�������ռ�
    for(i=0;i<noOfTree;++i)
    {
        forest[i] = nullptr;
    }


    BinomialHeapNode *carry;//��λ
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

    //һ�������Ѿ�����
    if(other.noOfTree==min1)//other�Ѿ�����
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
    else//��ǰ�Ķ��н���
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
