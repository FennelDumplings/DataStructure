#ifndef MINMAXHEAP_H_INCLUDED
#define MINMAXHEAP_H_INCLUDED

typedef int MMHType;

class MinMaxHeap
{
private:
    MMHType *data;//动态数组起始地址
    int length;//有效元素个数
    int sizeArray;//数组规模

    int level(int p);//检查p在最大层还是最小层，最大返回1，最小返回0
    void verifyMin(int p, MMHType x);//沿最小层过滤
    void verifyMax(int p, MMHType x);//沿最大层过滤
    int findMinSonOrGrandSon(int n);//儿子和孙子的最小节点
    int findMaxSonOrGrandSon(int n);//儿子和孙子的最大节点

public:
    MinMaxHeap(int n=100)
    {
        sizeArray = n;
        length = 0;
        data = new MMHType[sizeArray];
    }
    ~MinMaxHeap(){delete []data;}

    void enQueue(const MMHType x);
    MMHType getMax();
    MMHType getMin()
    {
        return data[1];
    }
    bool isEmpty()const {return length==0;}
    void deleteMin();
    void deleteMax();
};

void testMinMaxHeap();

#endif // MINMAXHEAP_H_INCLUDED
