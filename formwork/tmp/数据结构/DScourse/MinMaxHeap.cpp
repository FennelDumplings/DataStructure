#include "MinMaxHeap.h"

#include "math.h"
#include <iostream>
using namespace std;

void MinMaxHeap::enQueue(const MMHType x)
{
    if(length==sizeArray-1)
    {
        cout << "队列满";
        return;
    }
    ++length;
    int p = length/2;//新节点的父节点
    if(p==0)
    {
        data[1] = x;
        return;
    }
    switch(level(p))
    {
    case 0://父节点在最小层
        if(x < data[p])
        {
            data[length] = data[p];
            verifyMin(p,x);
        }
        else
        {
            verifyMax(length,x);
        }
        break;
    case 1:
        if(x > data[p])
        {
            data[length] = data[p];
            verifyMax(p,x);
        }
        else
        {
            verifyMin(length,x);
        }
    }
}

int MinMaxHeap::level(int p)
{
    int lvl = log(p)/log(2);
    return (lvl%2);
}

void MinMaxHeap::verifyMax(int i, MMHType x)
{
    for(int gp = i/4;gp &&(x>data[gp]);gp/=4)
    {
        data[i] = data[gp];
        i = gp;
    }
    data[i] = x;
}

void MinMaxHeap::verifyMin(int i,MMHType x)
{
    for(int gp=i/4; gp&&(x<data[gp]);gp/=4)
    {
        if(data[i] < data[gp])
        {
            data[i] = data[gp];
            i = gp;
        }
    }
    data[i] = x;
}

void MinMaxHeap::deleteMin()
{
    data[0] = data[1];//存根元素
    MMHType x = data[length--];//删最后一个元素
    int i=1, last = length/2;
    int min1;

    //寻找插入x的位置
    while(i<=last)//i有儿子
    {
        min1 = findMinSonOrGrandSon(i);
        if(x<=data[min1])
            break;
        else
        {
            data[i] = data[min1];
            if(min1<=2*i+1)//min1是i的儿子
            {
                i = min1;
                break;
            }
            else
            {
                int p = min1/2;//p是min的父亲
                if(x>data[p])
                {
                    MMHType t = data[p];
                    data[p] = x;
                    x = t;
                }
            }
            i = min1;
        }
    }
    data[i] = x;
    return;
}

int MinMaxHeap::findMinSonOrGrandSon(int n)
{
    int min1 = 2*n;
    if(min1+1<=length&&data[min1+1]<data[min1])
        ++min1;
    for(int k=4*n; k<=length && k<4*(n+1); ++k)
    {
        if(data[k]<data[min1])
            min1=k;
    }
    return min1;
}

void MinMaxHeap::deleteMax()
{
    if(length==1)
    {
        length--;
        return;
    }
    int max1;

    if(length==2)
        max1 = 2;
    else
        max1 = (data[2]>data[3]?2:3);
    data[0] = data[max1];//暂存最大元素

    MMHType x = data[length--];

    int i,last = length/2,parent;
    for(i=max1;i<=last;)
    {
        max1 = findMaxSonOrGrandSon(i);
        if(x>=data[max1])
            break;
        data[i] = data[max1];

        if(max1<=2*i+1)
        {
            i=max1;
            break;
        }
        parent = max1/2;
        if(x<data[parent])
        {
            MMHType tmp = x;
            x = data[parent];
            data[parent] = tmp;
        }
        i = max1;
    }
    data[i] = x;
    return;
}

int MinMaxHeap::findMaxSonOrGrandSon(int n)
{
    int max1 = 2*n;
    if(max1+1<=length&&data[max1+1]>data[max1])
        ++max1;
    for(int k=4*n; k<=length && k<4*(n+1); ++k)
    {
        if(data[k]>data[max1])
            max1=k;
    }
    return max1;
}

MMHType MinMaxHeap::getMax()
{
    if(length==1)
        return data[1];

    int max1;
    if(length==2)
        max1 = 2;
    else
        max1 = (data[2]>data[3]?2:3);

    return data[max1];
}

void testMinMaxHeap()
{
    MinMaxHeap heap;
}
