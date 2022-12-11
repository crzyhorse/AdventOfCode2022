// day10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <deque>
#include <vector>

std::deque<std::pair<std::string, int>> getInput(std::string filename) {
    std::ifstream inputFile;
    inputFile.open(filename);
    std::deque<std::pair<std::string, int>> input;
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            if (line == "noop") {
                input.push_back(std::make_pair(line, 0));
            }
            else {
                std::string op = line.substr(0, 4);
                std::stringstream s;
                s << line.substr(5, line.length());
                int val;
                s >> val;
                input.push_back(std::make_pair(line.substr(0, 4), val));
            }
        }
    }
    return input;
}

int findStrength(std::deque<std::pair<std::string, int>> input) {
        int cycles = 0;
        int signalstrenght = 0;
        int Xreg = 1;
        bool op = false;
        int endcycle = 0;
        std::pair<std::string, int> opcode;
        for (int x = 1; x <= 220; x++) {
            if (x % 40 == 20)
                signalstrenght += x * Xreg;
            if (!op) {
                opcode = input.front();
                input.pop_front();
                op = true;
                if (opcode.first == "addx") endcycle = x + 1; else op = false;
            }
            else {
                if (endcycle == x) {
                    if (opcode.first == "addx") {
                        Xreg += opcode.second;
                    }
                    op = false;
                    endcycle = 0;
                }
            }
        }
        return signalstrenght;
 }

std::vector<std::string> flipPixels(std::deque<std::pair<std::string, int>> input) {
    std::string resetpixelrow = "........................................";
    std::vector<std::string> pixels;
    for (int index = 0; index <= 5; index++)
        pixels.push_back(resetpixelrow);
    int cycles = 0;
    int Xreg = 1;
    bool op = false;
    std::pair<std::string, int> opcode;
    int rowindex = 0;
    int pixelindex = 0;
    int endcycle = 0;
    do {
        if (cycles >= 241) {
            break;
        }
        if (pixelindex == Xreg || pixelindex == Xreg - 1 || pixelindex == Xreg + 1) {
            pixels[rowindex][pixelindex] = '#';
        }
        pixelindex++;
        if (pixelindex > 39) {
            pixelindex = 0;
            rowindex++;
        }
        if (!op) {
            opcode = input.front();
            input.pop_front();
            op = true;
            if (opcode.first == "addx") endcycle = cycles + 1; else op = false;
        }
        else {
            if (endcycle == cycles) {
                if (opcode.first == "addx") {
                    Xreg += opcode.second;
                }
                op = false;
                endcycle = 0;
            }
        }
        cycles++;
    } while (!input.empty());
    return pixels;
}

int main()
{
    std::deque<std::pair<std::string, int>> input = getInput("input.txt");
    std::cout << "The answer to part 1 is " << findStrength(input) << std::endl;
    input.clear();
    input = getInput("input.txt");
    std::vector<std::string> pixels = flipPixels(input);
    std::cout << "The answer to part 2 is " << std::endl;
    for (std::vector<std::string>::iterator it = pixels.begin(); it != pixels.end(); it++)
    {
        std::cout << it->c_str() << std::endl;
    }
}
