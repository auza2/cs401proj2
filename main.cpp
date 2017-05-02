//
//  main.cpp
//  cs401proj2
//
//  Created by Jamie Auza on 4/19/17.
//  Copyright © 2017 Jamie Auza. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm> // for heap operations
#include <vector>
#include "Edge.h"
#include "Vertex.h"
#include "Path.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;
Vertex * adjacenyList;
//list<Path> * Signatures;
std::list<Path> * Signatures;
int numVertices;
vector<Path> heap;

int BUDGET;
int START;
int END;

// Given an adjacency list Alist
void init(){
	// Makes all of the curves for each vertex have the first node as (infinity, infinity, null)
	// Add path Start ( c: 0, t:0, path, S? )
	
	//Initialize all Signatures for each vertex to have a path null, infinity, infinity
	Signatures = new std::list<Path>[numVertices];
	
	Path first = (Path) *Signatures[START].begin();
	first.updateCost(0);
	first.updateTime(0);
	first.updatePath(to_string(START));
	
	heap.push_back(first);
	make_heap(heap.begin(),heap.end());
}

void addToSignatures(Path p, int vertex){
	// Look at the current last signature in this vertex
	Signatures[vertex].push_back(p);
	
	 /*
	list<Path>::const_iterator it =Signatures[vertex].begin();
	Path last = (Path) (*it);
	if( last.getCost() != 99999){
		if( last.getCost() < p.getCost()&& p.getTime()< last.getTime())
			Signatures[vertex].push_back(p);
	}else{
		Signatures[vertex].push_back(p);
	}
	 */
	
}

struct compare
{
	bool operator()( Path& a ,  Path& b) const
	{
		if(a.getCost() == b.getCost())
			return a.getTime() < b.getTime();
		else
			return a.getCost() < b.getCost();
	}
};

void Dijsktra_Like(int budget){
	init();
	
	/*
	 * while( heap is not empty )
	 * Take min path off heap
	 *		Look at ending vertex's last Signature and check if it dominates it, add if it does
	 * Look at ending vertex's edges
	 * Create new Paths ( adding the ending vertex to that path), adding the cost and time
	 * Add on to the heap
	 *
	 */
	
	Path poppedFromHeap;
	while( heap.size() != 0 ){
		//Take min path off heap
		poppedFromHeap = heap.back();
		
		// Gets the list of edges that the ending vertes can get to
		int endingVertex =poppedFromHeap.getEndingVertex();
		heap.pop_back();
		list<Edge> edges = adjacenyList[endingVertex].getEdgeList();
		Edge e;
		string endVertex;
		
		// For all the new paths add to the heap and re-sort
		for(list<Edge>::const_iterator it  = edges.begin();it != edges.end(); it++){
			e = (Edge) *it;
			endVertex = std::to_string(e.getTarget());

			Path * p = new Path( poppedFromHeap.getCost() + e.getCost(),poppedFromHeap.getTime() + e.getTime(), endVertex+ poppedFromHeap.getPath() );
			heap.push_back(*p);
		}
		
		sort_heap(heap.begin(),heap.end(),compare());
		
		
		// check if the popped Path is non-dominated
		addToSignatures(poppedFromHeap, endingVertex);
	}
	
}

int main(int argc, const char * argv[]) {
	int start,fin,cost,time;
	std::ifstream infile;
	
	if(argc !=5)
		cout << "Wrong inputs" <<endl;
	else
	{
		infile.open(argv[1]);
	}
	
	

	//infile.open("thefile.txt");
	
	if( !infile.is_open())
	{
		cout << "No file" << endl;
	}
	else{
		// Gets the number of Vertices from the first line
		infile >> numVertices;

		// counter Array is used to find if there is already an list
		int counter[numVertices];
		for(int i = 0; i < numVertices;i++)
		{
			counter[i] = 0;
		}
		
		// Array of Vertices that hold an Edge list
		adjacenyList = new Vertex[numVertices];
		
		// Create adjacency list from the file
		while(infile >> start >> fin >> cost >> time)
		{
			cout<< "Processing " << "Start: " << start << "| End: " << fin << "| Cost: " << cost << "| Time: " << time << endl;
			if(counter[start] == 0)
			{
				Vertex v =  Vertex(start);
				adjacenyList[start] = v;
				Edge e = Edge(cost,time,fin);
				adjacenyList[start].addEdge(e);
				counter[start] = 1;
			}
			else
			{
				Edge e = Edge(cost,time,fin);
				adjacenyList[start].addEdge(e);
			}
		}
		infile.close();
		
		/* Debug for
		 for( int i = 0 ; i < numVertices ; i++){
			adjacenyList[i].printEdgeList();
		 }
		 */
		
		
		//BUDGET = (int) *argv[4];
		//BUDGET = BUDGET -'0';
		BUDGET = atoi(argv[4]);
		//START = (int) *argv[2];
		//START = START - '0';
		START = atoi(argv[2]);
		//END = (int) *argv[3];
		//END = END - '0';
		END = atoi(argv[3]);
		 
		
		cout << BUDGET << endl;
		Dijsktra_Like(BUDGET);
		//check sig destination and pick one within budget
		Path finalPath = Path();
		for(list<Path>::const_iterator it  = Signatures[END].begin();it != Signatures[END].end(); it++){
			Path p;
			p = (Path) *it;
			
			cout << "Cost:"  << p.getCost() << " Time:" <<  p.getTime() << " Path:" << p.getPathInOrder() <<endl;
			
			if(BUDGET >= p.getCost())
			{
				if(finalPath.getTime() > p.getTime())
				{
					//we can keep it
					finalPath = p;
				}
			}
			else if(finalPath.getCost() == p.getCost())
			{
				if(finalPath.getTime() > p.getTime())
					finalPath = p;
			}
			
		}
		
		cout << "FINAL:"<<"Cost:"  << finalPath.getCost() << " Time:" <<  finalPath.getTime() << " Path:" << finalPath.getPathInOrder() <<endl;
	}
    return 0;
}
