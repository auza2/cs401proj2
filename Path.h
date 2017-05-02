#include <string>
#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

using namespace std;
class Path
{
    public:

        Path();
        Path(int _cost, int _time, string s);
        ~Path();
        int getCost();
        int getTime();
        string getPath();
        void updateCost(int newCost);
        void updateTime(int newTime);
        void updatePath(string newPath);
        bool operator<(const Path &p) const;
		int getEndingVertex();
		string getPathInOrder();

    private:
        int totalCost;
        int totalTime;
        string pathSoFar;
		bool pathHasBeenUpdated = false;

};

#endif // PATH_H_INCLUDED
