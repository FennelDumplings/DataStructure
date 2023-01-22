#ifndef BINARYHEAP_H_INCLUDED
#define BINARYHEAP_H_INCLUDED

typedef int BHType;

class BinaryHeap//Ë³Ðò¶þ²æ¶Ñ
{
private:
    int maxSize;
    BHType *data;
    int length;

    void doubleSpace()
    {
        BHType *tmp = data;
        maxSize *= 2;
        data = new BHType[maxSize];
        for(int i=0;i<=length;i++)
        {
            data[i] = tmp[i];
        }
        delete []tmp;
    }
    void buildHeap();
    void percolateDown(int hole);

public:
    BinaryHeap(int capacity=100)
    {
        data = new BHType[capacity];
        length = 0;
        maxSize = capacity;
    }
    BinaryHeap(const BHType arr[],int num);
    ~BinaryHeap(){delete [] data;}

    bool isEmpty()const {return length == 0;}
    void enQueue(const BHType &x);
    void deQueue();
    BHType getHead()const {return data[1];}
};

void testBinaryHeap();
#endif // BINARYHEAP_H_INCLUDED
