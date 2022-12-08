// Day8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>



const int WIDTH =  99; // used these defines so i can just change them to run the test input. too lazy to write code to read the file and determine the dimensions.
const int HEIGHT = 99;

int matrix[HEIGHT][WIDTH];
int highestscenicscore = 0;

std::vector<std::pair<int, int>> visibletrees;

void getInput(std::string filename) {
    std::ifstream inputFile;
    inputFile.open(filename);
    if (inputFile.is_open()) {
        char c;
        for (int x = 0; x < WIDTH; x++) {
            for (int y = 0; y < HEIGHT; y++) {
                inputFile >> c;
                matrix[x][y] = c -= '0'; // char is ascii value of character. We want int. Character 0 is ascii 30. so to convert to int, we just subtract character 0.
            }
        }
    }
}

bool checkVisible(int x, int y) { // determine if the "tree" is visible based on x, y coordinates.
    if (x == 0 || y == 0 || x == WIDTH - 1 || y == HEIGHT - 1) return true;  // edge cases...get it?
    bool visible = true;
    int val = matrix[y][x];
    for (int xx = x - 1; xx >= 0; xx--) {
        if (matrix[y][xx] >= val) visible = false;
    }
    if (visible) return visible;
    visible = true;
    for (int xx = x + 1; xx < WIDTH; xx++) {
        if (matrix[y][xx] >= val) visible = false;
    }
    if (visible) return visible;
    visible = true;
    for (int yy = y - 1; yy >= 0; yy--) {
        if (matrix[yy][x] >= val) visible = false;
    }
    if (visible) return visible;
    visible = true;
    for (int yy = y + 1; yy < HEIGHT; yy++) {
        if (matrix[yy][x] >= val) visible = false;
    }
    return visible;
}

void calcScore(int x, int y) { // get the scenic score for each "tree" based on x, y coordinates.
    int left = 0;
    int right = 0;
    int up = 0;
    int down = 0;
    int val = matrix[y][x];
    if (x != 0) {
        for (int xx = x - 1; xx >= 0; xx--) {
            left += 1;
            if (matrix[y][xx] >= val) break;
        }
    }
    else {
        left = 0;
    }
    if (x != WIDTH - 1) {
        for (int xx = x + 1; xx < WIDTH; xx++) {
            right += 1;
            if (matrix[y][xx] >= val) break;
        }
    }
    else {
        right = 0;
    }
    if (y != 0) {
        for (int yy = y - 1; yy >= 0; yy--) {
            up += 1;
            if (matrix[yy][x] >= val) break;
        }
    }
    else {
        up = 0;
    }
    if (y != HEIGHT - 1) {
        for (int yy = y + 1; yy < HEIGHT; yy++) {
            down += 1;
            if (matrix[yy][x] >= val) break;
        }
    } else {
        down = 0;
    }
    int scenicscore = up * down * left * right;
    if (scenicscore > highestscenicscore) highestscenicscore = scenicscore;
}



void findVisible() {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            if (checkVisible(x, y)) visibletrees.push_back(std::make_pair(x, y));
            calcScore(x, y);
        }
    }
}

int main()
{
    getInput("input.txt");
    findVisible();
    std::cout << "The answer to part1 is " << visibletrees.size() << std::endl;
    std::cout << "The answer to part2 is " << highestscenicscore << std::endl;
}
