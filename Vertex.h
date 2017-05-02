#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED
#include <list>
#include "Edge.h"
using namespace std;

class Vertex{

public:
    Vertex();
    Vertex(int _num);
    void addEdge(Edge e);
    //void tempEdge(int e);
    //void printstuff();
    int getNum();
    list<Edge>::const_iterator getIterator();
    list<Edge>::const_iterator getIteratorEnd();
    list<Edge> getEdgeList();
	void printEdgeList();

private:
    int num;
    list<Edge> edges;


};
#endif // VERTEX_H_INCLUDED
