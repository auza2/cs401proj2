#include "Vertex.h"
#include <iostream>

using namespace std;

Vertex::Vertex()
{

}

Vertex::Vertex(int _num)
{
    num = _num;
}

void Vertex::addEdge(Edge e)
{
    edges.push_back(e);
}

int Vertex::getNum()
{
    return num;
}

list<Edge>::const_iterator Vertex::getIterator()
{
    return edges.begin();
}

list<Edge> Vertex::getEdgeList()
{
    return edges;
}

list<Edge>::const_iterator Vertex::getIteratorEnd()
{
    return edges.end();
}

void Vertex::printEdgeList(){
	list<Edge>::const_iterator it = edges.begin();
	Edge e;
	for( ; it != edges.end(); it++){
		e = (Edge) *it;
		cout << "Start: " << num << "| End: " << e.getTarget() << "| Cost: " << e.getCost() << "| Time: " << e.getTime() << endl;
	}
}
