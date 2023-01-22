#ifndef ADJMATRIXGRATH_H_INCLUDED
#define ADJMATRIXGRATH_H_INCLUDED

typedef int TypeOfEdge;
typedef int TypeOfVer;

class AdjMatrixGraph
{
private:
    TypeOfEdge **edge;
    TypeOfEdge *ver;
    TypeOfEdge noEdge;
    int vers,edges;
public:
    AdjMatrixGraph(int vSize, const TypeOfVer d[], const TypeOfEdge noEdgeFlag);//只有结点没有边的图
    ~AdjMatrixGraph();
    bool insertx(int u,int v, TypeOfEdge w);
    bool removex(int u,int v);
    bool exist(int u, int v)const;
    int numOfEdge()const{return edges;}
    int numOfVer()const{return vers;}
};

void testAdjMartixGraph();

#endif // ADJMATRIXGRATH_H_INCLUDED
