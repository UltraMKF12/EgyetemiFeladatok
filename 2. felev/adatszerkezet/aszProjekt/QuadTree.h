#ifndef QUADTREE.H
#define QUADTREE.H

#include <vector>
using namespace std;

struct Point
{
    int x;
    int y;

    Point();
    Point(int x, int y);
    Point operator/(int number) const;
    Point operator+(int number) const;
    Point operator+(const Point& number) const;
    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;
};

class Quadrant
{
    protected:
        Point topLeftCorner;
        Point bottomRightCorner;

        int depth;
        bool isLeaf;

        Quadrant* topLeft;
        Quadrant* topRight;
        Quadrant* bottomLeft;
        Quadrant* bottomRight;
        vector<Point*> points;

    public:
        Quadrant(Point topLeftCorner, Point bottomRightCorner, int depth);
        ~Quadrant();

        void split();
};

class QuadTree
{
    private:
        Quadrant* root;
    
    public:
        QuadTree(Point topLeftCorner, Point bottomRightCorner);
        ~QuadTree();
        void insert(Point point);
        Quadrant* search(Point point);
        void remove(Point point);
        void print();
};

#endif