#include "QuadTree.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include "lodepng.h"
using namespace std;


struct QuadrantImageCompression : Quadrant
{
    int pixelAvg;

    QuadrantImageCompression* topLeft;
    QuadrantImageCompression* topRight;
    QuadrantImageCompression* bottomLeft;
    QuadrantImageCompression* bottomRight;

    QuadrantImageCompression(Point topLeftCorner, Point bottomRightCorner, int depth) : Quadrant(topLeftCorner, bottomRightCorner, depth)
    {
        pixelAvg = 0;
        topLeft = nullptr;
        topRight = nullptr;
        bottomLeft = nullptr;
        bottomRight = nullptr;
    }

    void split();
    void buildTree(const std::vector<unsigned char> &image, int treshold, int error, int maxDepth, int imageWidth);
    void printTreeImage(std::vector<unsigned char> &image, int imageWidth);
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

void QuadrantImageCompression::buildTree(const std::vector<unsigned char> &image, int treshold, int error, int maxDepth, int imageWidth)
{
    int height = this->bottomRightCorner.y+1;
    int width = this->bottomRightCorner.x+1;

    unordered_map<int, int> uniquePixels;

    int avg_r = 0;
    int avg_g = 0;
    int avg_b = 0;

    
    // Calculate avarage color while saving all the unique colors to a map
    for (int y = this->topLeftCorner.y; y < height; ++y) 
    {
        for (int x = this->topLeftCorner.x; x < width; ++x) 
        {
            // Calculate the index of the current pixel in the image data array
            unsigned index = 4 * imageWidth * y + 4 * x;

            unsigned char red = image[index];
            unsigned char green = image[index + 1];
            unsigned char blue = image[index + 2];

            //Store every UNIQUE pixel and it's count.
            int pixelCode = ((red*1000) + green) * 1000 + blue;
            if(uniquePixels.count(pixelCode) < 1)
            {
                uniquePixels[pixelCode] = 1;
            }
            else
            {
                uniquePixels[pixelCode]++;
            }

            avg_r += red;
            avg_g += green;
            avg_b += blue;
        }
    }

    //Calculate the avarage color
    int pixelCount = (width - this->topLeftCorner.x) * (height - this->topLeftCorner.y);
    avg_r /= pixelCount;
    avg_g /= pixelCount;
    avg_b /= pixelCount;
    this->pixelAvg = ((avg_r*1000) + avg_g) * 1000 + avg_b;

    //If this is the max depth then this is where we call quits
    if(this->depth >= maxDepth) return;

    //Check to see if there is a unique color above treshold. If there is we can return
    int pixelCountTreshold = (treshold / 100.0) * pixelCount;
    for(const auto& pair : uniquePixels)
    {
        if(pair.second >= pixelCountTreshold) return;
    }

    //If there is not then we need to create a second map where we calculate new pixel counts with error
    unordered_map<int, int> uniquePixelsWithError;
    for(const auto pair : uniquePixels)
    {
        uniquePixelsWithError[pair.first] = pair.second;
    }

    for(const auto currentPair : uniquePixels)
    {
        for(const auto otherPair : uniquePixels)
        {
            if(currentPair.first == otherPair.first) continue;

            int code1 = currentPair.first;
            int b1 = code1 % 1000;
            code1 /= 1000;
            int g1 = code1 % 1000;
            code1 /= 1000;
            int r1 = code1 % 1000;

            int code2 = otherPair.first;
            int b2 = code1 % 1000;
            code2 /= 1000;
            int g2 = code2 % 1000;
            code2 /= 1000;
            int r2 = code2 % 1000;

            if(abs(r1 - r2) <= error && abs(g1 - g2) <= error && abs(b1 - b2) <= error)
            {
                uniquePixelsWithError[currentPair.first] += otherPair.second;
                if(uniquePixelsWithError[currentPair.first] >= pixelCountTreshold) return;
            }
        }
    }

    //If we arrive there it means the QuadTree must split.
    this->split();
    if(this->isLeaf) return;
    else
    {
        topLeft->buildTree(image, treshold, error, maxDepth, imageWidth);
        topRight->buildTree(image, treshold, error, maxDepth, imageWidth);
        bottomLeft->buildTree(image, treshold, error, maxDepth, imageWidth);
        bottomRight->buildTree(image, treshold, error, maxDepth, imageWidth);
    }
}

void QuadrantImageCompression::printTreeImage(std::vector<unsigned char> &image, int imageWidth)
{
    if(this->isLeaf)
    {
        int height = this->bottomRightCorner.y;
        int width = this->bottomRightCorner.x;
        
        unsigned char r, g, b;
        int temp = this->pixelAvg;
        b = temp % 1000;
        temp /= 1000;
        g = temp % 1000;
        temp /= 1000;
        r = temp % 1000;

        // Set every pixel color to AVG
        for (int y = this->topLeftCorner.y; y <= height; ++y) 
        {
            for (int x = this->topLeftCorner.x; x <= width; ++x) 
            {
                unsigned index = 4 * imageWidth * y + 4 * x;

                // Set the RGB color values for the current pixel
                image[index] = r;    // Red
                image[index + 1] = g;  // Green
                image[index + 2] = b;  // Blue
            }
        }
    }
    else
    {
        topLeft->printTreeImage(image, imageWidth);
        topRight->printTreeImage(image, imageWidth);
        bottomLeft->printTreeImage(image, imageWidth);
        bottomRight->printTreeImage(image, imageWidth);
    }
}



class QuadTreeImageCompression : public QuadTree
{
    private:
        QuadrantImageCompression* root;

        std::vector<unsigned char> image;
        int treshold;
        int error;
        int depth;

        int channels;
    
    public:
        QuadTreeImageCompression(const char* image_name, int treshold, int error, int depth);
        ~QuadTreeImageCompression();
        void buildTree();
        void printTreeImage();
};

QuadTreeImageCompression::QuadTreeImageCompression(const char* image_name, int treshold, int error, int depth)
{
    // Read the image
    unsigned width, height;
    unsigned error_img = lodepng::decode(image, width, height, image_name);
    if (error_img) 
    {
        std::cout << "Error while decoding image: " << lodepng_error_text(error_img) << std::endl;
        exit(1);
    }
    
    root = new QuadrantImageCompression(Point(0,0), Point(width-1, height-1), 0);
    this->treshold = treshold;
    this->error = error;
    this->depth = depth;
}

QuadTreeImageCompression::~QuadTreeImageCompression()
{
    delete root;
}

void QuadTreeImageCompression::buildTree()
{
    root->buildTree(image, treshold, error, depth, root->bottomRightCorner.x+1);
}

void QuadTreeImageCompression::printTreeImage()
{
    // Create a new image
    int height = root->bottomRightCorner.y+1;
    int width = root->bottomRightCorner.x+1;
    std::vector<unsigned char> newImage(width * height * 4, 255);

    root->printTreeImage(newImage, width);

    // Encode and save the image file
    unsigned error_img = lodepng::encode("output.png", newImage, width, height);

    // Check if the encoding was successful
    if (error_img) 
    {
        std::cout << "Error while encoding image: " << lodepng_error_text(error_img) << std::endl;
        return;
    }

    std::cout << "New image created and saved as " << "output.png" << std::endl;
}



char* getParameters(int argc, char* argv[], int &treshold, int &error, int &depth)
{
    if(argc != 5)
    {
        cout << "Error: There must be exactly four parameters. Usage: [Filename(string)] [Treshold(0-100)] [Error(>0)] [Depth(>0)]" << endl;
        exit(1);
    }

    try
    {
        treshold = stoi(argv[2]);
        error = stoi(argv[3]);
        depth = stoi(argv[4]); 
    }
    catch(const invalid_argument)
    {
        cout << "Error: Treshold, Error and Depth must be numbers" << endl;
        exit(1);
    }

    if(treshold < 0 || treshold > 100)
    {
        cout << "Error: Treshold must be between 0 and 100" << endl;
        exit(1);
    }

    if(error < 0 || depth < 0)
    {
        cout << "Error: Error of Depth must be above 0" << endl;
        exit(1);
    }

    return argv[1];
}

int main(int argc, char* argv[])
{

    int treshold, error, depth;
    const char* filename = getParameters(argc, argv, treshold, error, depth);
    
    QuadTreeImageCompression img(filename, treshold, error, depth);
    img.buildTree();
    img.printTreeImage();

    return 0;
}