// Day9.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <map>
#include <tuple>
#include <vector>

std::map<std::pair<int, int>, int> tailPos;


bool isTouching(int headx, int heady, int tailx, int taily) {
    //...
    //.H. same position or any adjacent is touching
    //...
    if (tailx == headx - 1 && taily == heady + 1) return true; // upper left
    if (tailx == headx - 1 && taily == heady) return true; // left
    if (tailx == headx - 1 && taily == heady - 1) return true; // lower left
    if (tailx == headx && taily == heady - 1) return true; // under
    if (tailx == headx + 1 && taily == heady - 1) return true; // lower right
    if (tailx == headx + 1 && taily == heady) return true; // right
    if (tailx == headx + 1 && taily == heady + 1) return true; // upper right
    if (tailx == headx && taily == heady + 1) return true; // above
    if (tailx == headx && taily == heady) return true; // overlapping
    return false;
}


void moveTail(char dir, int& headx, int& heady, int& tailx, int& taily) {
    if (!isTouching(headx, heady, tailx, taily)) { // if its touching it doesnt need to move
        if (headx < tailx && heady == taily) tailx -= 1; // going straight left
        else if (headx > tailx && heady == taily) tailx += 1; // going straight right
        else if (heady > taily && headx == tailx) taily += 1; // going straight up
        else if (heady < taily && headx == tailx) taily -= 1; // going straight 
        else if (heady < taily && headx < tailx) {  // move down left diagonal
            tailx -= 1;
            taily -= 1;
        }
        else if (heady < taily && headx > tailx) { // move down right diagonal
            tailx += 1;
            taily -= 1;
        }
        else if (heady > taily && headx > tailx) { // move up right diagonal
            tailx += 1;
            taily += 1;
        }
        else if (heady > taily && headx < tailx) { // move up left diagonal
            tailx -= 1;
            taily += 1;
        }
    }
}

void moveHead(char dir, int &headx, int &heady) {
    switch (dir) {
        case 'l':
        case 'L':
            headx -= 1;
            break;
        case 'r':
        case 'R':
            headx += 1;
            break;
        case 'u':
        case 'U':
            heady += 1;
            break;
        case 'd':
        case 'D':
            heady -= 1;
            break;
    }
}


void getInputPart1(std::string filename) {
    std::ifstream inputFile;
    inputFile.open(filename);
    bool toggle = false;
    if (inputFile.is_open()) {
        char direction;
        int num;
        int headx = 0;
        int heady = 0;
        int tailx = 0;
        int taily = 0;
        tailPos.insert(std::make_pair(std::make_pair(tailx, taily), 0)); // start position
        while (inputFile >> direction >> num) {
            for (int i = 0; i < num; i++) {
                moveHead(direction, headx, heady);
                int origtailx = tailx;
                int origtaily = taily;
                moveTail(direction, headx, heady, tailx, taily);
                if (tailx != origtailx || taily != origtaily) tailPos.insert(std::make_pair(std::make_pair(tailx, taily), 0));
                
            }
        }
    }
}

void getInputPart2(std::string filename) {
    std::ifstream inputFile;
    inputFile.open(filename);
    bool toggle = false;
    if (inputFile.is_open()) {
        char direction;
        int num;
        std::vector<std::tuple<int, int>> rope;
        for (int x = 0; x < 10; x++) rope.push_back({ 0,0 });
        tailPos.insert(std::make_pair(std::make_pair(0, 0), 0)); // start position
        while (inputFile >> direction >> num) {
            for (int i = 0; i < num; i++) {
                int origtailx = std::get<0>(rope[9]);
                int origtaily = std::get<1>(rope[9]);
                moveHead(direction, std::get<0>(rope[0]), std::get<1>(rope[0]));
                for (int x = 1; x < rope.size(); x++) {
                    moveTail(direction, std::get<0>(rope[x-1]), std::get<1>(rope[x-1]), std::get<0>(rope[x]), std::get<1>(rope[x]));
                }
                if (std::get<0>(rope[9]) != origtailx || std::get<1>(rope[9]) != origtaily) tailPos.insert(std::make_pair(std::make_pair(std::get<0>(rope[9]), std::get<1>(rope[9])), 0));
            }
        }
    }
}

int main()
{
    getInputPart1("input.txt");
    std::cout << "The answer to part1 is " << tailPos.size() << std::endl;
    tailPos.clear();
    getInputPart2("input.txt");
    std::cout << "The answer to part2 is " << tailPos.size() << std::endl;
}