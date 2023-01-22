#ifndef ADJLISTGRAPH_H_INCLUDED
#define ADJLISTGRAPH_H_INCLUDED

typedef int TypeOfEdge;
typedef int TypeOfVer;

class AdjListGraph
{
private:
    struct EulerNode
    {
        int NodeNum;
        EulerNode *next;
        EulerNode(int ver){NodeNum=ver;next=nullptr;}
    };
    struct edgeNode
    {
        int endx;//终点编号
        TypeOfEdge weight;
        edgeNode *next;
        edgeNode(int e, TypeOfEdge w,edgeNode *n=nullptr)
        {
            endx = e;
            weight = w;
            next = n;
        }
    };

    struct verNode
    {
        TypeOfVer ver;
        edgeNode *head;
        verNode(edgeNode *h = nullptr)
        {
            head = h;
        }
    };
    int vers,edges;
    verNode *verList;

public:
    AdjListGraph(int vSize, const TypeOfVer d[]);//只有结点没有边的图
    ~AdjListGraph();
    bool insertx(int u,int v, TypeOfEdge w);
    bool removex(int u,int v);
    bool exist(int u, int v)const;
    int numOfEdge()const{return edges;}
    int numOfVer()const{return vers;}
    void dfs()const;
    void bfs()const;
    void topSort()const;
    void EulerCircuit(TypeOfVer start);
    verNode* clone()const;
    void findStrong()const
    {
        int *visit = new int[vers];
        int seqNo = 0;
        int noOfStrong;

        int i;
        for(i=0;i<vers;i++)
        {
            visit[i] = -1;
        }

        for(i=0;i<vers;i++)
        {
            if(visit[i]>=0)
                continue;
            findSeqNo(i, visit, seqNo);
        }

        //生成Gr
        verNode *tmpV = new verNode[vers];
        edgeNode *oldp, *newp;
        for(i=0;i<vers;i++)
        {
            oldp = verList[i].head;
            while(oldp!=nullptr)
            {
                tmpV[oldp->endx].head = new edgeNode(i,oldp->weight,tmpV[oldp->endx].head);
                oldp = oldp->next;
            }
        }

        //按序号从大到小遍历Gr
        noOfStrong = 0;
        for(seqNo=vers-1;seqNo>=0;--seqNo)
        {
            for(i=0;i<vers;++i)
                if(visit[i]==seqNo)
                    break;
            if(i==vers)
                continue;
            ++noOfStrong;
            //第noOfStrong个强连通分量
            finddfs(i,tmpV,visit);
        }

        //释放Gr
        for(i=0;i<vers;i++)
        {
            oldp = tmpV[i].head;
            while(oldp!=nullptr)
            {
                newp = oldp;
                oldp = oldp->next;
                delete newp;
            }
        }
        delete [] tmpV;
    }
    bool isDAG()const
    {
        bool *visited = new bool[vers];
        bool flag;

        int i;
        for(i=0;i<vers;i++)
        {
            visited[i] = false;
        }

        for(i=0;i<vers;++i)
        {
            flag = isDAG(i,visited);
            if(!flag)
                return false;
            visited[i] = false;
        }
        return true;
    }

private:
    void dfs(int start, bool visit[])const;
    EulerNode* EulerCircuit(TypeOfVer start,EulerNode *&endy);
    void findSeqNo(int start, int visited[],int &seqNo)const
    {
        edgeNode *p = verList[start].head;

        visited[start] = -2;//未被访问过为-1，被访问过，值为序号，当访问某节点的后继时，先标记为-2，以免访问后继时又回到这个节点
        while(p!=nullptr)
        {
            if(visited[p->endx==-1])
                findSeqNo(p->endx,visited,seqNo);
            p = p->next;
        }
        visited[start] = seqNo++;
    }
    void finddfs(int start, verNode *tmpV, int visit[])const
    {
        edgeNode *p = tmpV[start].head;

        //访问连通分量中的该节点
        visit[start] = -1;//已经访问过
        while(p!=nullptr)
        {
            if(visit[p->endx]!=-1)
                finddfs(p->endx,tmpV,visit);
            p=p->next;
        }
    }
    bool isDAG(int start, bool visited[])const
    {
        edgeNode *p = verList[start].head;
        bool flag;

        visited[start] = true;//设起始点已被访问
        while(p!=nullptr)
        {
            if(visited[p->endx])
                return false;
            else
                flag = isDAG(p->endx,visited);
            if(!flag)
                return false;
            visited[p->endx] = false;
            p = p->next;
        }
        return true;
    }
};

void testAdjListGraph();

#endif // ADJLISTGRAPH_H_INCLUDED
