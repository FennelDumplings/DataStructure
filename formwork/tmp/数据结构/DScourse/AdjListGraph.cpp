#include "AdjListGraph.h"
#include <queue>

using namespace std;

AdjListGraph::AdjListGraph(int vSize,const TypeOfVer d[])
{
    vers = vSize;
    edges = 0;

    verList = new verNode[vSize];
    for(int i=0;i<vSize;i++)
    {
        verList[i].ver = d[i];
    }
}

AdjListGraph::~AdjListGraph()
{
    int i;
    edgeNode *p;

    for(i=0;i<vers;++i)
    {
        while((p=verList[i].head)!=nullptr)
        {
            verList[i].head = p->next;
            delete p;
        }
    }
    delete [] verList;
}

bool AdjListGraph::exist(int u, int v)const
{
    edgeNode *p = verList[u].head;
    while(p!=nullptr&&p->endx!=v)
        p = p->next;
    if(p==nullptr)
        return false;
    else
        return true;
}

bool AdjListGraph::insertx(int u,int v, TypeOfEdge w)
{
    verList[u].head = new edgeNode(v,w,verList[u].head);
    ++edges;
    return true;
}

bool AdjListGraph::removex(int u,int v)
{
    edgeNode *p = verList[u].head, *q;
    if(p==nullptr)//无相邻的边
        return false;
    if(p->endx==v)//单链表中第一个结点就是被删除的边
    {
        verList[u].head = p->next;
        delete p;
        --edges;
        return true;
    }
    while(p->next!=nullptr&&p->next->endx!=v)
        p=p->next;
    if(p->next==nullptr)
        return false;
    q = p->next;
    p->next = q->next;
    delete q;
    --edges;
    return true;
}

void AdjListGraph::dfs()const
{
    bool *visit =new bool[vers];

    for(int i=0;i<vers;i++)
    {
        visit[i] = false;
    }

    for(int j=0;j<vers;j++)//遍历对于所有连通分量
    {
        if(visit[j]==true)
            continue;
        dfs(j,visit);
    }
}

void AdjListGraph::dfs(int start, bool visit[])const
{
    edgeNode *p = verList[start].head;

    visit[start] = true;
    while(p!=nullptr)
    {
        if(visit[p->endx]==false)
            dfs(p->endx,visit);
        p = p->next;
    }
}

void AdjListGraph::bfs() const
{
    bool *visit =new bool[vers];

    for(int i=0;i<vers;i++)
    {
        visit[i] = false;
    }

    int currentNode;
    queue<int> q;

    edgeNode *p;

    //开始bfs
    for(int i=0;i<vers;i++)
    {
        if(visit[i]==true)
            continue;
        q.push(i);
        while(!q.empty())
        {
            currentNode = q.front();
            q.pop();
            if(visit[currentNode]==true)
                continue;
                //访问节点
            visit[currentNode] = true;
            //currentNode后继节点入队
            while(p!=nullptr)
            {
                if(visit[p->endx]==false)
                {
                    q.push(p->endx);
                    p = p->next;
                }

            }
        }
        //一个连通分量结束
    }
}

void AdjListGraph::topSort()const
{
    queue<int> q;
    edgeNode *p;
    int current;
    int *inDegree = new int[vers];

    for(int i=0;i<vers;i++)//计算每个节点的入度
    {
        inDegree[i] = 0;
    }
    for(int i=0;i<vers;i++)
    {
        for(p=verList[i].head;p!=nullptr;p = p->next)
        {
            ++inDegree[p->endx];
        }
    }
    //入度0节点入队
    for(int i=0;i<vers;i++)
    {
        if(inDegree[i]==0)
            q.push(i);
    }
    //开始排序

    while(!q.empty())
    {
        current = q.front();
        q.pop();
        //访问节点
        for(p=verList[current].head;p!=nullptr;p=p->next)
        {
            if(--inDegree[p->endx]==0)
                q.push(p->endx);
        }
        //一个连通分量结束
    }

}

void AdjListGraph::EulerCircuit(TypeOfVer start)
{
    EulerNode *beg,*endy,*p,*q,*tb,*te;//beg和endy为欧拉回路的起点和终点
    int numOfDegree;
    edgeNode *r;
    verNode *tmp;

    //检查是否存在
    if(edges==0)
        return;//不存在
    int i;
    for(i=0;i<vers;i++)
    {
        numOfDegree = 0;//统计每个节点的出度
        r = verList[i].head;
        while(r!=0)
        {
            ++numOfDegree;
            r = r->next;
        }
        if(numOfDegree==0||numOfDegree%2)//不存在欧拉回路
            return;
    }
    //寻找起始点编号
    for(i=0;i<vers;i++)
    {
        if(verList[i].ver==start)
            break;
    }

    if(i==vers)
        return;//不存在起始节点

    tmp = clone();//邻接表的复制

    beg = EulerCircuit(i,endy);//寻找从i出发的路径，dfs

    while(true)
    {
        p = beg;
        while(p->next!=nullptr)//检查是否尚有边未被访问
            if(verList[p->next->NodeNum].head!=nullptr)
                break;
            else
                p = p->next;
        if(p->next==nullptr)//所有边都已经被访问
            break;
        q = p->next;
        tb = EulerCircuit(q->NodeNum,te);
        te->next = q->next;
        p->next = tb;
        delete q;
    }
    //恢复原图
    delete [] verList;
    verList = tmp;
}

AdjListGraph::verNode* AdjListGraph::clone()const
{
    verNode *tmp = new verNode[vers];
    edgeNode *p;

    for(int i=0;i<vers;i++)
    {
        tmp[i].ver = verList[i].ver;
        p = verList[i].head;
        while(p!=nullptr)
        {
            tmp[i].head = new edgeNode(p->endx,p->weight,tmp[i].head);//参数传递方式传递节点的链接
            p = p->next;
        }
    }
    return tmp;
}

AdjListGraph::EulerNode* AdjListGraph::EulerCircuit(TypeOfVer start,EulerNode *&endy)
{
    EulerNode *beg;
    int nextNode;

    beg = endy = new EulerNode(start);
    while(verList[start].head!=nullptr)
    {
        nextNode = verList[start].head->endx;
        removex(start,nextNode);
        removex(nextNode,start);
        start = nextNode;
        endy ->next = new EulerNode(start);
        endy = endy->next;
    }
    return beg;
}

void testAdjListGraph()
{

}
