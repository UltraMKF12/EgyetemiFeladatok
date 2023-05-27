#include <iostream>
#include "QuadTree.h"
using namespace std;

int main()
{   
    QuadTree alma(Point(0, 0), Point(8,8));
    alma.insert(Point(1, 1));
    alma.insert(Point(0, 0));
    alma.insert(Point(0, 2));
    alma.insert(Point(0, 3));
    alma.print();
    return 0;
}