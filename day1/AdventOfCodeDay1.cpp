// AdventOfCodeDay1.cpp 
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>


std::map<int, int> getInput(std::string filename) {
    std::map<int, int> temp; // using a map because it will automatically be sorted by key. so <calories, elf position>
    std::ifstream inputFile;
    inputFile.open(filename);
    if (inputFile.is_open()) {
        std::string line;
        int pos = 1;
        int sum = 0;
        while (std::getline(inputFile,line)) { // using getline so we can get the blank line.
            if (!line.size()) { // if it's a blank line, it's the next elf.
                temp.insert({ sum,pos });
                sum = 0;
                pos += 1;
            }
            else { // if it's not we need to total the elf calories.
                std::stringstream s;
                s << line;
                int n;
                s >> n;
                sum += n;
            }
        }
    }
    return temp;
}

int main()
{
    std::map <int, int> input = getInput("input.txt"); // <total calories, pos>
    int total = 0;
    auto it = input.end(); // get the largest calorie count to start. maps are sorted by key.
    it--;
    std::cout << "Answer to part 1 is " << it->first << std::endl;
    for (int i = 0; i < 3; i++) {
        total += it->first;
        it--;
    }
    std::cout << "Answer to part 2 is " << total << std::endl;
}