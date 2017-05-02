#include "Edge.h"

Edge::Edge()
{

}

Edge::Edge(int _cost, int _time, int _target)
{
    cost = _cost;
    time = _time;
    target = _target;
}

void Edge::setCost(int c)
{
    cost = c;
}

void Edge::setTime(int t)
{
    time = t;
}

int Edge::getTime()
{
    return time;
}

int Edge::getCost()
{
    return cost;
}

int Edge::getTarget()
{
    return target;
}
