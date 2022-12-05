// Day5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
#include <tuple>


std::deque<char> * getStacks(std::string filename) {
    std::ifstream inputFile;
    inputFile.open(filename);
    std::deque<char>* stacks = new std::deque<char> [9];
    if (inputFile.is_open()) {
        std::string line;
        for (int x = 0; x < 8; x++) {
            std::getline(inputFile, line);
            int stacknum = 0;
            for (int y = 2; y <= 34; y += 4) {
                char ch = line[y-1];
                if (ch != 32 && ch != '\0') {
                    stacks[stacknum].push_back(ch);
                }
                stacknum++;
            }
        }
        std::getline(inputFile, line);
    }
    return stacks;
}

std::vector<std::tuple<int, int, int>> getMoves(std::string filename) {
    std::ifstream inputFile;
    inputFile.open(filename);
    std::vector<std::tuple<int, int, int>> moves;
    if (inputFile.is_open()) {
        std::string throwaway;
        for (int x = 0; x < 10; x++) {
            
            std::getline(inputFile, throwaway);
        }
        
        int num, to, from = 0;
        //move 2 from 2 to 7
        while (inputFile >> throwaway >> num >> throwaway >> from >> throwaway >> to) {
            std::tuple<int, int, int> move(num, to, from);
            moves.push_back(move);
        }
    }
    return moves;
}

void doMovesPart1(std::deque<char> * stacks, std::vector<std::tuple<int, int, int>> moves) {
    for (int x = 0; x < moves.size(); x++) {
        int num = std::get<0>(moves[x]);
        int to = std::get<1>(moves[x]);
        int from = std::get<2>(moves[x]);
        for (int x = 0; x < num; x++) {
            char ch = stacks[from-1].front();
            stacks[from - 1].pop_front();
            stacks[to - 1].push_front(ch);
        }
    }
 }
 
void doMovesPart2(std::deque<char>* stacks, std::vector<std::tuple<int, int, int>> moves) {
    for (int x = 0; x < moves.size(); x++) {
        int num = std::get<0>(moves[x]);
        int to = std::get<1>(moves[x]);
        int from = std::get<2>(moves[x]);
        std::vector<char> boxes;
        for (int x = 0; x < num; x++) {
            char ch = stacks[from - 1].front();
            stacks[from - 1].pop_front();
            boxes.push_back(ch);
        }
        for (int y = boxes.size(); y > 0; y--) {
            stacks[to - 1].push_front(boxes[y-1]);
        }
    }
}


int main()
{
    std::deque<char> * part1stacks = getStacks("input.txt");
    std::deque<char> part2stacks[9];
    std::copy(part1stacks,part1stacks+9,part2stacks);
    std::vector < std::tuple<int, int, int>> moves = getMoves("input.txt");
    
    // part 1
    doMovesPart1(part1stacks, moves);
    std::cout << "Part1 answer is ";
    for (int x = 0; x < 9; x++) {
        std::cout << part1stacks[x].front();
    }
    std::cout << std::endl;

    // part 2
    doMovesPart2(part2stacks, moves);
    std::cout << "Part2 answer is ";
    for (int x = 0; x < 9; x++) {
        std::cout << part2stacks[x].front();
    }
}
