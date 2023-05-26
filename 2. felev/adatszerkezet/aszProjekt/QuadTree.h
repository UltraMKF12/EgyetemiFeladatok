#ifndef QUADTREE.H
#define QUADTREE.H

struct Point
{
    int x;
    int y;

    Point()
    {
        x = 0;
        y = 0;
    }

    Point(int valueX, int valueY)
    {
        x = valueX;
        y = valueY;
    }
};

struct Node
{
    Point pos;
    int data;

    Node(Point _pos, int _data)
    {
        pos = _pos;
        data = _data;
    }

    Node()
    {
        data = 0;
    }
};


class QuadTree
{
    protected:
        Point topLeftPosition;
        Point bottomRightPosition;
        int depth;

        QuadTree* topLeftQuad;
        QuadTree* topRightQuad;
        QuadTree* bottomLeftQuad;
        QuadTree* bottomRightQuad;

    public:
        QuadTree();
        QuadTree(Point topLeft, Point bottomRight);
        void insert();
        void remove();
        QuadTree* search();
        void print();
        int getDepth();
};

#endif