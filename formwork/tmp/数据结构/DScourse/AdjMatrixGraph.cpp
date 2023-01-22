#include "AdjMatrixGraph.h"

AdjMatrixGraph::AdjMatrixGraph(int vSize,const TypeOfVer d[],const TypeOfEdge noEdgeFlag)
{
    int i,j;
    vers = vSize;
    edges = 0;
    noEdge = noEdgeFlag;

    ver = new TypeOfVer[vSize];
    for(i=0;i<vSize;i++)
    ver[i]=d[i];
    edge = new TypeOfEdge*[vSize];
    for(i=0;i<vSize;i++)
    {
        edge[i] = new TypeOfEdge[vSize];
        for(j=0;j<vSize;j++)
            edge[i][j]=noEdge;
        edge[i][i]=0;
    }
}

AdjMatrixGraph::~AdjMatrixGraph()
{
    delete [] ver;
    for(int i=0;i<vers;i++)
    {
        delete [] edge[i];
    }
    delete [] edge;
}

bool AdjMatrixGraph::exist(int u, int v)const
{
    if(u<0||u>vers-1||v<0||v>vers-1)
        return false;
    if(edge[u][v]==noEdge)
        return false;
    else
        return true;
}

bool AdjMatrixGraph::insertx(int u,int v, TypeOfEdge w)
{
    if(u<0||u>vers-1||v<0||v>vers-1)
        return false;
    if(edge[u][v]!=noEdge)
        return false;
    edge[u][v] = w;
    edges++;
    return true;
}

bool AdjMatrixGraph::removex(int u,int v)
{
    if(u<0||u>vers-1||v<0||v>vers-1)
        return false;
    if(edge[u][v]==noEdge)
        return false;
    edge[u][v];
    edges--;
    return true;
}

void testAdjMartixGraph()
{

}
