// Day4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

/// <summary>
/// Function to get input from text file and calculate answers for part 1 and part2.
/// For part 1, given two pairs of numbers, we are finding if any one pair is totally contained inside another.
/// For part2, given the same two pairs of numbers, we are finding if there is any overlap at all between the two pairs.
/// </summary>
/// <param name="filename">string containing input filename.</param>
void getInput(std::string filename) {
    std::ifstream inputFile;
    inputFile.open(filename);
    int start1, end1, start2, end2 = 0;
    char throwaway;
    int countPart1 = 0;
    int countPart2 = 0;
    if (inputFile.is_open()) {
        while (inputFile >> start1 >> throwaway >> end1 >> throwaway >> start2 >> throwaway >> end2) {
            
            // Part 1
            if ((start1 >= start2 && end1 <= end2) || (start2 >= start1 && end2 <= end1)) {
                countPart1++;
            }

            // Part 2
            bool overlap = false;
            if (start1 < start2) {
                overlap = end1 < start2 ? false : true;
            }
            else if (start2 < start1) {
                overlap = end2 < start1 ? false : true;
            }
            else { 
                overlap = true;
            }
            if (overlap) countPart2++;
   
        }
    }
    std::cout << "Answer to part 1 is " << countPart1 << std::endl;
    std::cout << "Answer to part 2 is " << countPart2 << std::endl;
}

int main()
{
    getInput("input.txt");
}