#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED
class Edge
{
    public:
        Edge();
        Edge(int _cost, int _time,int _target);
        void setCost(int c);
        void setTime(int t);
        int getTime();
        int getCost();
        int getTarget();

    private:
        int cost;
        int time;
        int target;
};


#endif // EDGE_H_INCLUDED
