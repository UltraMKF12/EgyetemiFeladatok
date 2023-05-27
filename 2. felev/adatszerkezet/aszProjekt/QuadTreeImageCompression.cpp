#include "QuadTree.h"
#include <iostream>
#include <vector>
using namespace std;


struct QuadrantImageCompression : Quadrant
{
    int value;

    QuadrantImageCompression(Point topLeftCorner, Point bottomRightCorner, int depth) : Quadrant(topLeftCorner, bottomRightCorner, depth)
    {
        value = 0;
    }

    void split();

};

class QuadTreeImageCompression : public QuadTree
{
    private:
        QuadrantImageCompression* root;
    
    public:
        QuadTreeImageCompression(Point topLeftCorner, Point bottomRightCorner)
        {
            root = new QuadrantImageCompression(topLeftCorner, bottomRightCorner, 0);
        }
};

void QuadrantImageCompression::split()
{
    // If a coordinate in topleft or bottomright are the same, we can not split it into four.
    if (this->topLeftCorner.x == this->bottomRightCorner.x ||
        this->topLeftCorner.y == this->bottomRightCorner.y ||
        !this->isLeaf) return;

    this->isLeaf = false;
    this->topLeft = new QuadrantImageCompression(this->topLeftCorner,
                        (this->topLeftCorner + this->bottomRightCorner) / 2, 
                        depth+1);

    this->topRight = new QuadrantImageCompression(Point(((this->topLeftCorner.x + this->bottomRightCorner.x) / 2) + 1, this->topLeftCorner.y),
                        Point(this->bottomRightCorner.x, (this->topLeftCorner.y + this->bottomRightCorner.y) / 2), 
                        depth+1);

    this->bottomLeft = new QuadrantImageCompression(Point(this->topLeftCorner.x, ((this->topLeftCorner.y + this->bottomRightCorner.y) / 2) + 1),
                        Point((this->topLeftCorner.x + this->bottomRightCorner.x) / 2, this->bottomRightCorner.y), 
                        depth+1);

    this->bottomRight = new QuadrantImageCompression(((this->topLeftCorner + this->bottomRightCorner) / 2) + 1,
                        this->bottomRightCorner, 
                        depth+1);
}


int main()
{
    int treshold;
    int error;
    int depth;
    return 0;
}