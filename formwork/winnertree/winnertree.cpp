#include <iostream>
#include <cassert>
using namespace std;

#define  MAX 0x7fffffff

struct node{
    int nData;
    int id;
    node(int n,int i){nData=n;id=i;}
};

node* BuildTree(int data[],int len,int &nTreeSize)
{
    int nNodes = 1;
    while(nNodes<len)//为了构建完全二叉树，不够的要补
        nNodes <<= 1;

    nTreeSize = nNodes*2 - 1;
    node *trees = (node*)malloc(sizeof(node)*nTreeSize);
    assert(trees);

    for(int i=nNodes-1; i<nTreeSize; i++){
        int idx = i - (nNodes - 1);
        if(idx<len)
            trees[i] = node(data[idx],i);
        else
            trees[i] = node(MAX,-1);//对于补充的数据，我们初始化成最大。
    }

    for(int i=nNodes-2; i>=0; --i){ //初始化，前面白色节点，指向孩子节点的最小值
        if(trees[i*2+1].nData < trees[i* 2+2].nData)
            trees[i] = trees[i*2+1];
        else
            trees[i] = trees[i*2+2];
    }

    return trees;
}

void Adjust(node *data, int idx)//当去除最小元素以后，我们要调整数组
{
    while(idx != 0)   //从后向前调整
    {
        if(idx%2 == 1)//当前id是奇数，说明并列的是idx + 1, 父节点是 (idx-1)/2
        {
            if(data[idx].nData < data[idx + 1].nData) //idx+1为兄弟节点
                data[(idx-1)/2] = data[idx];
            else
                data[(idx-1)/2] = data[idx+1];
            idx = (idx-1)/2;
        }
        else
        {
            if(data[idx-1].nData < data[idx].nData) //idx-1为兄弟节点
                data[idx/2-1] = data[idx-1];
            else
                data[idx/2-1] = data[idx];
            idx = (idx/2-1);
        }
    }
}


void sort(node *trees,int len)//返回排序的结果
{
    int dataLen = len/2+1;
    int *data = new int[dataLen];
    assert(data);

    for(int i=0; i<dataLen; i++){
        data[i] = trees[0].nData;//输出
        trees[trees[0].id].nData = MAX;//输出节点替换为最大值
        Adjust(trees,trees[0].id);//调整树
    }

    for(int i=0;i<dataLen;i++){
        cout<<data[i]<<" ";
    }
    cout<<endl;

    delete[] data;
}

void PrintArr(node *arr,int len)
{
    assert(arr && len>0);
    for(int i=0; i<len; ++i){
        cout<<arr[i].nData<<" ";
    }
    cout<<endl;
}

int main()
{
    int treeLen;
    node *trees;
    int arr[] = {3,4,1,6,2,8,7,9};

    trees = BuildTree(arr,8,treeLen);
    PrintArr(trees,treeLen);

    sort(trees,treeLen);

    delete[] trees;
    system("pause");
    return 0;
}
