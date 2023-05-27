#include <iostream>
#include "QuadTree.h"
using namespace std;

int main()
{   
    QuadTree alma(Point(0, 0), Point(7,7));
    alma.insert(Point(1, 1));
    alma.insert(Point(2, 2));
    alma.insert(Point(0, 2));
    alma.insert(Point(0, 3));
    alma.remove(Point(0, 3));
    alma.remove(Point(0, 2));
    alma.remove(Point(1, 1));
    alma.print();
    return 0;
}