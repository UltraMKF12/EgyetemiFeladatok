#include <iostream>
#include <vector>
#include "lodepng.h"

// Function to read an image and get RGB color of each pixel
void readImage(const char* filename) {
    std::vector<unsigned char> image;
    unsigned width, height;

    // Load the image file
    unsigned error = lodepng::decode(image, width, height, filename);

    // Check if the decoding was successful
    if (error) {
        std::cout << "Error while decoding image: " << lodepng_error_text(error) << std::endl;
        return;
    }

    // Iterate over each pixel and get RGB color
    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            unsigned index = 4 * width * y + 4 * x;
            unsigned char r = image[index];
            unsigned char g = image[index + 1];
            unsigned char b = image[index + 2];

            // Process RGB color values as needed
            std::cout << "Pixel at (" << x << ", " << y << "): RGB(" << int(r) << ", " << int(g) << ", " << int(b) << ")" << std::endl;
        }
    }
}

// Function to create a new image with specified RGB color for each pixel
void createImage(const char* filename, unsigned width, unsigned height, unsigned char r, unsigned char g, unsigned char b) {
    std::vector<unsigned char> image(width * height * 4, 255); // Initialize with opaque white pixels

    // Set RGB color for each pixel
    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            unsigned index = 4 * width * y + 4 * x;
            image[index] = r;
            image[index + 1] = g;
            image[index + 2] = b;
        }
    }

    // Encode and save the image file
    unsigned error = lodepng::encode(filename, image, width, height);

    // Check if the encoding was successful
    if (error) {
        std::cout << "Error while encoding image: " << lodepng_error_text(error) << std::endl;
        return;
    }

    std::cout << "New image created and saved as " << filename << std::endl;
}

int main() {
    const char* inputFile = "input.png";
    const char* outputFile = "output.png";

    // Read the input image and get RGB color of each pixel
    readImage(inputFile);

    // Create a new image with specific RGB color for each pixel
    unsigned width = 4;
    unsigned height = 4;
    unsigned char r = 255;
    unsigned char g = 255;
    unsigned char b = 200;
    createImage(outputFile, width, height, r, g, b);

    return 0;
}