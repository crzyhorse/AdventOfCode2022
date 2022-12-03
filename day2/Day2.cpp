// AdventOfCodeDay2'.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

enum score {
    rock=1,
    paper=2,
    scissors=3
};

enum outcome {
    win=6,
    lose=0,
    draw=3
};

typedef std::vector<std::pair<char, char>> moves;

std::vector<std::pair<char,char>> getInput(std::string filename) {
    moves tempVec; 
    std::ifstream inputFile;
    inputFile.open(filename);
    if (inputFile.is_open()) {
        char their,mine;
        while (inputFile >> their ) { 
            inputFile >> mine;
            std::pair<char, char> tempPair = std::make_pair(their, mine);
            tempVec.push_back(tempPair);
        }
    }
    return tempVec;
}

int getMove(char move) {
    int score = 0;
    switch (move)
    {
    case 'A':
    case 'a':
    case 'X':
    case 'x':
        score = rock;
        break;
    case 'B':
    case 'b':
    case 'Y':
    case 'y':
        score = paper;
        break;
    case 'C':
    case 'c':
    case 'Z':
    case 'z':
        score = scissors;
        break;
    }
    return score;
}

int calcScore(char theirMove, char myMove) {
    //  rock = 1
    //  paper = 2
    //  scissors = 3
    int myMod = 0;
    int theirMod = 0;
    int myScore = getMove(myMove);
    int theirScore = getMove(theirMove);
    switch (myScore + theirScore) {
        case 2: // rock + rock
            myScore += draw;
            theirScore += draw;
            break;
        case 3: // rock + paper
            myMod = myScore > theirScore ? win : lose; 
            theirMod = theirScore > myScore ? win : lose;
            myScore += myMod;
            theirScore += theirMod;
            break;
        case 4: // paper + paper or scissors + rock
            if (myScore == theirScore) { //scissors + scissors
                myScore += draw;
                theirScore += draw;
            }
            else { // scissors + rock
                myMod = myScore > theirScore ? lose : win;
                theirMod = theirScore > myScore ? lose : win;
                myScore += myMod;
                theirScore += theirMod;
            }
            break;
        case 5: // scisssors + paper
            myMod = myScore > theirScore ? win : lose;
            theirMod = theirScore > myScore ? win : lose;
            myScore += myMod;
            theirScore += theirMod;
            break;
        case 6: // scissors + scissors
            myScore += draw;
            theirScore += draw;
            break;
    }   
    return myScore;
}

int getWinning(int move) {
    switch (move) {
        case rock:
            return paper;
        case paper:
            return scissors;
        case scissors:
            return rock;
    }
}

int getLosing(int move) {
    switch (move) {
        case rock:
            return scissors;
        case paper:
            return rock;
        case scissors:
            return paper;
    }
}

int getDrawing(int move) {
    switch (move) {
        case rock:
            return rock;
        case paper:
            return paper;
        case scissors:
            return scissors;
    }
}

int calcScorePart2(char theirMove, char myResult) {
    int myScore = 0;
    int theirPlay = getMove(theirMove);
    switch (myResult)
    {
    case 'X': // lose
    case 'x':
        myScore += lose;
        myScore += getLosing(theirPlay);
        break;
    case 'Y':
    case 'y': // draw
        myScore += draw;
        myScore += getDrawing(theirPlay);
        break;
    case 'Z':
    case 'z': // win
        myScore += win;
        myScore += getWinning(theirPlay);
        break;
    }
    return myScore;
 }

int main()
{
    moves input = getInput("input.txt");
    int part1Score = 0;
    int part2Score = 0;
    for (moves::iterator it = input.begin(); it != input.end(); it++)
    {
        part1Score += calcScore(it->first, it->second);
        part2Score += calcScorePart2(it->first, it->second);
    }
    std::cout << "The answer to part 1 is " << part1Score << std::endl;
    std::cout << "The answer to part 2 is " << part2Score << std::endl;
}
