// Day6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <set>

/// <summary>
/// Function to count where the first occurence of numUnique characters ends. 
/// </summary>
/// <param name="filename">Input file for day 6 puzzle</param>
/// <param name="numUnique">Part 1 wants 4 unique characters in a row. Part 2 wants 14.</param>
/// <returns>Integer value which specifies the position in the line where the first group of numUnique characters ends.</returns>
int getMarkerPos(std::string filename, int numUnique) {
    std::ifstream inputFile;
    inputFile.open(filename);
    if (inputFile.is_open()) {
        std::string line;
        std::getline(inputFile, line);
        for (int x = 0; x < line.length(); x += 1) {
            std::set<char> marker;
            std::string subset = line.substr(x, numUnique);
            for (int y = 0; y < numUnique; y++) {
                marker.insert(subset[y]);
                if (marker.size() == numUnique) {
                    return x + numUnique;
                }
            }
        }
     }
}

int main()
{
    int part1 = getMarkerPos("input.txt",4);
    std::cout << "The answer to Part 1 is " << part1 << std::endl;
    int part2 = getMarkerPos("input.txt", 14);
    std::cout << "The answer to Part 1 is " << part2 << std::endl;
}

