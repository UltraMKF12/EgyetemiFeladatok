#include "QuadTree.h"
#include <iostream>
#include <vector>
using namespace std;

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
    // If a coordinate in topleft or bottomright are the same, we can not split it into four.
    if (this->topLeftCorner.x == this->bottomRightCorner.x ||
        this->topLeftCorner.y == this->bottomRightCorner.y ||
        !this->isLeaf) return;

    this->isLeaf = false;
    this->topLeft = new Quadrant(this->topLeftCorner,
                                (this->topLeftCorner + this->bottomRightCorner) / 2, 
                                depth+1);

    this->topRight = new Quadrant(Point(((this->topLeftCorner.x + this->bottomRightCorner.x) / 2) + 1, this->topLeftCorner.y),
                                Point(this->bottomRightCorner.x, (this->topLeftCorner.y + this->bottomRightCorner.y) / 2), 
                                depth+1);

    this->bottomLeft = new Quadrant(Point(this->topLeftCorner.x, ((this->topLeftCorner.y + this->bottomRightCorner.y) / 2) + 1),
                                Point((this->topLeftCorner.x + this->bottomRightCorner.x) / 2, this->bottomRightCorner.y), 
                                depth+1);

    this->bottomRight = new Quadrant(((this->topLeftCorner + this->bottomRightCorner) / 2) + 1,
                                this->bottomRightCorner, 
                                depth+1);
}

bool Quadrant::isInBounds(Point point)
{
    return (point.x >= this->topLeftCorner.x && point.x <= this->bottomRightCorner.x) &&
           (point.y >= this->topLeftCorner.y && point.y <= this->bottomRightCorner.y);
}

void Quadrant::insert(Point newPoint)
{
    //Check to make sure it's not already there
    for(Point currentPoint : points)
    {
        if(currentPoint == newPoint) return;
    }


    if(!isInBounds(newPoint)) return;
    points.push_back(newPoint);
    if(points.size() <= 1) return;

    this->split();
    if(this->isLeaf) return; // If we could not split it anymore return

    //Now we need to insert all the point into the place they belong.
    for(Point currentPoint : points)
    {
        if(currentPoint.x <= ((this->topLeftCorner.x + this->bottomRightCorner.x) / 2))
        {
            if(currentPoint.y <= ((this->topLeftCorner.y + this->bottomRightCorner.y) / 2))
            {
                topLeft->insert(currentPoint);
            }
            else
            {
                bottomLeft->insert(currentPoint);
            }
        } 
        else
        {
            if(currentPoint.y <= ((this->topLeftCorner.y + this->bottomRightCorner.y) / 2))
            {
                topRight->insert(currentPoint);
            }
            else
            {
                bottomRight->insert(currentPoint);
            }
        }
    }

}

void Quadrant::remove(Point point)
{
    if(!isInBounds(point)) return;

    bool found = false;
    int position;
    for(int i = 0; i < this->points.size(); i++)
    {
        if(points[i] == point)
        {
            found = true;
            position = i;
            break;
        }
    }

    if(!found) return;

    points.erase(points.begin() + position);
    if(points.size() < 1)
    {
        this->isLeaf = true;
        delete topLeft;
        delete topRight;
        delete bottomLeft;
        delete bottomRight;
    }
}

void Quadrant::print(vector<vector<int>> &table, int &value) const
{   
    if(this->isLeaf)
    {
        for(int i = this->topLeftCorner.x; i <= this->bottomRightCorner.x; i++)
        {
            for(int j = this->topLeftCorner.y; j <= this->bottomRightCorner.y; j++)
            {
                table[i][j] = value;
            }
        }
        value++;
        return;
    }
    else if(topLeft != nullptr)
    {
        topLeft->print(table, value);
        topRight->print(table, value);
        bottomLeft->print(table, value);
        bottomRight->print(table, value);
    }
}


QuadTree::QuadTree(Point topLeftCorner, Point bottomRightCorner)
{
    root = new Quadrant(topLeftCorner, bottomRightCorner, 0);
}

QuadTree::~QuadTree()
{
    delete root;
}

void QuadTree::insert(Point newPoint)
{
    root->insert(newPoint);
}

void QuadTree::remove(Point point)
{
    root->remove(point);
}

void QuadTree::print()
{
    vector<vector<int>> table(root->bottomRightCorner.x+1, vector<int>(root->bottomRightCorner.y+1, 0));
    int value = 1;

    root->print(table, value);

    // for(Point currentPoint : root->points)
    // {
    //     table[currentPoint.x][currentPoint.y] = 0;
    // }

    for(int i = root->topLeftCorner.x; i <= root->bottomRightCorner.x; i++)
    {
        for(int j = root->topLeftCorner.y; j <= root->bottomRightCorner.y; j++)
        {
            cout << table[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

}