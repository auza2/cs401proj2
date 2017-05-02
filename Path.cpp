#include "Path.h"
#include <string>
#include <iostream>

using namespace std;

Path::Path()
{
    pathSoFar = "";
    totalCost = 99999;
    totalTime = 99999;

}
bool Path::operator<(const Path &p) const
{
    if(totalCost == p.totalCost)
        return totalTime < p.totalTime;
    else
        return totalCost < p.totalCost;
}


Path::Path(int _cost, int _time, string s)
{
    totalCost = _cost;
    totalTime = _time;
    pathSoFar = s;
}


int Path::getCost()
{
    return totalCost;
}

int Path::getTime()
{
    return totalTime;
}


void Path::updateCost(int newCost)
{
    totalCost = newCost;
}

void Path::updateTime(int newTime)
{
    totalTime = newTime;
}

void Path::updatePath(string newPath)
{
	if( !pathHasBeenUpdated) //HEHEHEHEHEEEEEEE
		pathSoFar = "";
    pathSoFar = newPath + pathSoFar ;
}

int Path::getEndingVertex(){
	return (int)(pathSoFar[0] -'0');
}

Path::~Path()
{
	//MAKE CLEAR
}

string Path::getPath()
{
    return pathSoFar;
}

string Path::getPathInOrder(){
	string returnME = "";
	for( int i = pathSoFar.length() -1 ; i >= 0 ; i-- ){
		returnME = returnME + pathSoFar[i];
		if( i != 0)
			returnME = returnME + "->";
	}
	return returnME;
}
