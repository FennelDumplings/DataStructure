#include "BinaryHeap.h"

void BinaryHeap::deQueue()
{
    data[1] = data[length--];
    percolateDown(1);
}

void BinaryHeap::enQueue(const BHType &x)
{
    if(length==maxSize-1)
        doubleSpace();

    int hole = ++length;
    for(;hole>1&&x<data[hole/2];hole/=2)
        data[hole] = data[hole/2];
    data[hole] = x;
}

void BinaryHeap::buildHeap()
{
    for(int i=length/2;i>0;i--)//从非叶节点开始
        percolateDown(i);
}

void BinaryHeap::percolateDown(int hole)
{
    int child;
    BHType tmp = data[hole];

    for(;hole*2<=length;hole=child)
    {
        child = hole*2;
        if(child!=length&&data[child+1]<data[child])
            child++;
        if(data[child]<tmp)
            data[hole] = data[child];
        else
            break;
    }
    data[hole] = tmp;
}

BinaryHeap::BinaryHeap(const BHType arr[],int num)
{
    maxSize = num+10;
    length = num;
    data = new BHType[maxSize];
    for(int i=0; i<num; i++)
        data[i+1] = arr[i];
    buildHeap();
}

void testBinaryHeap()
{

}
