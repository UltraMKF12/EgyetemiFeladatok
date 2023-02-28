#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

// Reads a list of words from the input stream and returns them as a vector.
std::vector<std::string> read_words(int n)
{
    std::vector<std::string> words;
    for (int i = 0; i < n; ++i)
    {
        std::string word;
        std::cin >> word;
        words.push_back(word);
    }
    return words;
}

// Returns true if the given word covers all the letters in the alphabet.
bool covers_alphabet(const std::string &word)
{
    std::unordered_set<char> seen;
    for (char c : word)
    {
        seen.insert(c);
    }
    return seen.size() == 26;
}

int main()
{
    freopen("bemenet.txt", "r", stdin);
    int n;
    std::cin >> n;
    std::vector<std::string> words = read_words(n);

    // Sort the words lexicographically.
    std::sort(words.begin(), words.end());

    // Find the minimum number of words needed to cover the alphabet.
    int k = 0;
    std::unordered_set<char> seen;
    while (seen.size() < 26 && k < n)
    {
        for (char c : words[k])
        {
            seen.insert(c);
        }
        ++k;
    }

    // If we couldn't cover the alphabet, output -1.
    if (seen.size() < 26)
    {
        std::cout << -1 << std::endl;
        return 0;
    }

    // Otherwise, output the number of words and the words themselves.
    std::cout << k << std::endl;
    for (int i = 0; i < k; ++i)
    {
        std::cout << words[i] << std::endl;
    }
    return 0;
}