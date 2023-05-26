#include <iostream>
using namespace std;

struct Vertex
{
    int value;
    Vertex* left;
    Vertex* right;
};

class BinaryTree
{
    private:
        Vertex* root;
    
    public:
        BinaryTree();
        ~BinaryTree();
        void Insert(int value);
        Vertex* Search(int value);
        Vertex* Mini();
        Vertex* Maxi();
        void Delete(int value);
};

BinaryTree::BinaryTree()
{

}


int main()
{

    return 0;
}