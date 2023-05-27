#include <iostream>
#include "QuadTree.h"
using namespace std;

int main()
{   
    Quadrant* root = new Quadrant(Point(0, 0), Point(3, 3), 0);
    root->split();
    delete root;

    return 0;
}