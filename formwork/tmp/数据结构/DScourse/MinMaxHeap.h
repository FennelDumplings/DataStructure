#ifndef MINMAXHEAP_H_INCLUDED
#define MINMAXHEAP_H_INCLUDED

typedef int MMHType;

class MinMaxHeap
{
private:
    MMHType *data;//��̬������ʼ��ַ
    int length;//��ЧԪ�ظ���
    int sizeArray;//�����ģ

    int level(int p);//���p�����㻹����С�㣬��󷵻�1����С����0
    void verifyMin(int p, MMHType x);//����С�����
    void verifyMax(int p, MMHType x);//���������
    int findMinSonOrGrandSon(int n);//���Ӻ����ӵ���С�ڵ�
    int findMaxSonOrGrandSon(int n);//���Ӻ����ӵ����ڵ�

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
