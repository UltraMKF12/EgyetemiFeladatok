#include "QuadTree.h"

Point::Point()
{
    x = 0;
    y = 0;
}

Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

Point Point::operator/(int number) const
{
    return Point(this->x/number, this->y/number);
}

Point Point::operator+(int number) const
{
    return Point(this->x + number, this->y + number);
}

Point Point::operator+(const Point& other) const
{
    return Point(this->x + other.x, this->y + other.y);
}

bool Point::operator==(const Point& other) const
{
    return ((this->x == other.x) && (this->y == other.y));
}

bool Point::operator!=(const Point& other) const
{
    return ((this->x != other.x) && (this->y != other.y));
}


Quadrant::Quadrant(Point topLeftCorner, Point bottomRightCorner, int depth)
{
    this->topLeftCorner = topLeftCorner;
    this->bottomRightCorner = bottomRightCorner;
    this->depth = depth;
    this->isLeaf = true;

    this->topLeft = nullptr;
    this->topRight = nullptr;
    this->bottomLeft = nullptr;
    this->bottomRight = nullptr;
}

Quadrant::~Quadrant()
{
    delete this->topLeft;
    delete this->topRight;
    delete this->bottomLeft;
    delete this->bottomRight;
}

void Quadrant::split()
{
    if (topLeftCorner == bottomRightCorner) return;

    this->isLeaf = false;

    this->topLeft = new Quadrant(this->topLeftCorner, this->bottomRightCorner/2, depth+1);
    this->topRight = new Quadrant(Point(this->bottomRightCorner.x/2+1, 0), Point(this->bottomRightCorner.x, this->bottomRightCorner.y/2),depth+1);
    this->bottomLeft = new Quadrant(Point(0, this->bottomRightCorner.y/2+1), Point(this->bottomRightCorner.x/2 ,this->bottomRightCorner.y), depth+1);
    this->bottomRight = new Quadrant(this->bottomRightCorner/2 + 1, this->bottomRightCorner, depth+1);
}


QuadTree::QuadTree(Point topLeftCorner, Point bottomRightCorner)
{
    root = new Quadrant(topLeftCorner, bottomRightCorner, 0);
}

QuadTree::~QuadTree()
{
    delete root;
}