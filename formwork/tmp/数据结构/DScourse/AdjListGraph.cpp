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
    if(p==nullptr)//�����ڵı�
        return false;
    if(p->endx==v)//�������е�һ�������Ǳ�ɾ���ı�
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

    for(int j=0;j<vers;j++)//��������������ͨ����
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

    //��ʼbfs
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
                //���ʽڵ�
            visit[currentNode] = true;
            //currentNode��̽ڵ����
            while(p!=nullptr)
            {
                if(visit[p->endx]==false)
                {
                    q.push(p->endx);
                    p = p->next;
                }

            }
        }
        //һ����ͨ��������
    }
}

void AdjListGraph::topSort()const
{
    queue<int> q;
    edgeNode *p;
    int current;
    int *inDegree = new int[vers];

    for(int i=0;i<vers;i++)//����ÿ���ڵ�����
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
    //���0�ڵ����
    for(int i=0;i<vers;i++)
    {
        if(inDegree[i]==0)
            q.push(i);
    }
    //��ʼ����

    while(!q.empty())
    {
        current = q.front();
        q.pop();
        //���ʽڵ�
        for(p=verList[current].head;p!=nullptr;p=p->next)
        {
            if(--inDegree[p->endx]==0)
                q.push(p->endx);
        }
        //һ����ͨ��������
    }

}

void AdjListGraph::EulerCircuit(TypeOfVer start)
{
    EulerNode *beg,*endy,*p,*q,*tb,*te;//beg��endyΪŷ����·�������յ�
    int numOfDegree;
    edgeNode *r;
    verNode *tmp;

    //����Ƿ����
    if(edges==0)
        return;//������
    int i;
    for(i=0;i<vers;i++)
    {
        numOfDegree = 0;//ͳ��ÿ���ڵ�ĳ���
        r = verList[i].head;
        while(r!=0)
        {
            ++numOfDegree;
            r = r->next;
        }
        if(numOfDegree==0||numOfDegree%2)//������ŷ����·
            return;
    }
    //Ѱ����ʼ����
    for(i=0;i<vers;i++)
    {
        if(verList[i].ver==start)
            break;
    }

    if(i==vers)
        return;//��������ʼ�ڵ�

    tmp = clone();//�ڽӱ�ĸ���

    beg = EulerCircuit(i,endy);//Ѱ�Ҵ�i������·����dfs

    while(true)
    {
        p = beg;
        while(p->next!=nullptr)//����Ƿ����б�δ������
            if(verList[p->next->NodeNum].head!=nullptr)
                break;
            else
                p = p->next;
        if(p->next==nullptr)//���б߶��Ѿ�������
            break;
        q = p->next;
        tb = EulerCircuit(q->NodeNum,te);
        te->next = q->next;
        p->next = tb;
        delete q;
    }
    //�ָ�ԭͼ
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
            tmp[i].head = new edgeNode(p->endx,p->weight,tmp[i].head);//�������ݷ�ʽ���ݽڵ������
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
