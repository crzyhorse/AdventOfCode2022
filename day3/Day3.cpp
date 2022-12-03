// Day3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

typedef std::vector<std::pair<std::string, std::string>> compartments;

/// <summary>
/// Reads the input file.
/// </summary>
/// <param name="filename">String containing the filename.</param>
/// <returns>A vector of strings which is each line of the entire file.</returns>
std::vector<std::string> getInput(std::string filename) { 
    std::vector<std::string> temp; 
    std::ifstream inputFile;
    inputFile.open(filename);
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            temp.push_back(line);
        }
    }
    return temp;
}

/// <summary>
/// Break the input data up to the specifics of part 1
/// Each string is evenly divided into two equal parts which represent "compartments" in a backpack.
/// </summary>
/// <param name="inputData">Vector of strings which contains the input data.</param>
/// <returns>returns a vector of pairs of strings (std::vector<std::pair<std::string,std::string>></returns>
compartments getCompartments(std::vector<std::string> inputData) {
    compartments temp;
    for (std::vector<std::string>::iterator it = inputData.begin(); it != inputData.end(); it++)
    {
        std::string compartment1 = it->substr(0, it->length() / 2);
        std::string compartment2 = it->substr(it->length() / 2, it->length() / 2);
        temp.push_back(std::make_pair(compartment1, compartment2));
    }
    return temp;
}

/// <summary>
/// Find the common item between the two "compartments" for Part 1. This would be the character that exists
/// in both halves of the input string.
/// </summary>
/// <param name="compartment1">string containing the characters in compartment 1 (first half of string)</param>
/// <param name="compartment2">string containing the characters in compartment 2 (second half of string)</param>
/// <returns>The common character that is in both compartments (both halves of the string)</returns>
char findCommon(std::string compartment1, std::string compartment2) {
    std::vector<bool> inString(123, false); // ascii 122 is uppercase Z and our index starts at 0
    char common;
    for (auto c : compartment1) {
        inString[c] = true;
    }
    for (auto c : compartment2) {
        if (inString[c]) {
            common = c;
            break;
        }
    }
    return common;
}

/// <summary>
/// Find the common item for Part 2. This would be the character that exists in 3 consecutive strings from the input file.
/// </summary>
/// <param name="elf1">The string representing what is carried by "elf #1".</param>
/// <param name="elf2">The string representing what is carried by "elf #2"</param>
/// <param name="elf3">The string representing what is carried by "elf #3"</param>
/// <returns>The common character that esists in all three strings.</returns>
char findCommon(std::string elf1, std::string elf2, std::string elf3) { 
    std::vector<std::array<bool, 3>> inString;
    std::array<bool, 3> compString{ false,false,false };
    for (int x = 0;x<124;x++) // uppercase Z is ascii 122, and our index starts at 0.
        inString.push_back(compString);

    for (auto c : elf1) {
        inString[c][0] = true;
    }
    for (auto c : elf2) {
        inString[c][1] = true;
    }
    for (auto c : elf3) {
        inString[c][2] = true; 
    }
    for (int x = 0; x<inString.size();x++)
        if (inString[x][0] && inString[x][1] && inString[x][2]) {
            return x;
        }
}

/// <summary>
/// Find the "priority" of items for parts 1 and 2. Priority is a-z = 1-26, A-Z = 27-52
/// </summary>
/// <param name="common">The character that is in common from the input data.</param>
/// <returns>an integer between 1 and 52 representing the item priority.</returns>
int findPriority(char common) {
    if (common >= 97 && common <= 122) { // lowercase
        return common - 96; // lowercase characters start at ASCII 97
    }
    else { // uppercase
        return common - 38; // uppercase characters start at ASCII 65
    }
}


int main()
{
    // read input data
    std::vector<std::string> inputData = getInput("input.txt");
    
    // Part 1
    compartments part1 = getCompartments(inputData); // break data into compartments
    int priority = 0;
    for (compartments::iterator it = part1.begin(); it != part1.end(); it++)
    {
        char common = findCommon(it->first, it->second); // find common character between compartments
        priority += findPriority(common); // calculate priority.
    }
    std::cout << "Part 1 priority is " << priority << std::endl;
    
    // Part 2
    priority = 0;
    for (int i = 0; i < inputData.size(); i += 3) // iterate in groups of 3
    {
        char common = findCommon(inputData[i], inputData[i + 1], inputData[i + 2]); // find common character between 3 strings.
        priority += findPriority(common); // calculate priority.
    }
    std::cout << "Part 2 priority is " << priority << std::endl;
}
