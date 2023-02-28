#include <iostream>
#include <vector>
#include <algorithm>

struct Block {
    std::string color;
    int size;
};

// comparison function for sorting blocks in ascending order of size
bool blockCompare(const Block& a, const Block& b) {
    return a.size < b.size;
}

// recursive function to generate and print towers
void generateTowers(std::vector<Block>& blocks, std::vector<int>& tower, int k) {
    if (tower.size() == k) {
        // print tower
        for (int i = k-1; i >= 0; i--) {
            std::cout << tower[i] << " ";
        }
        std::cout << std::endl;
        return;
    }

    for (int i = 0; i < blocks.size(); i++) {
        // check if current block can be added to tower
        if (tower.empty() || blocks[i].color != blocks[tower.back() - 1].color && blocks[i].size > blocks[tower.back() - 1].size) {
            // add block to tower
            tower.push_back(i + 1);
            // generate towers with remaining blocks
            generateTowers(blocks, tower, k);
            // remove block from tower
            tower.pop_back();
        }
    }
}

int main() {
    freopen("bemenet.txt", "r", stdin);
    int n, k;
    std::cin >> n >> k;

    std::vector<Block> blocks;
    for (int i = 0; i < n; i++) {
        std::string color;
        int size;
        std::cin >> color >> size;
        blocks.push_back({color, size});
    }

    // sort blocks in ascending order of size
    std::sort(blocks.begin(), blocks.end(), blockCompare);

    std::vector<int> tower;
    generateTowers(blocks, tower, k);

    return 0;
}