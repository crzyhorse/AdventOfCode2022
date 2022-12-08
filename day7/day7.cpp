// day7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>

struct _dir {
    int size;
    _dir* parentDir;
    std::map<std::string, int> files;
    std::map<std::string, _dir *> dirs;
};

   
_dir* getInput(std::string filename)
{
    _dir * root = new(_dir);
    root->size = 0;
    root->parentDir = NULL;
    _dir* curDir = root;
    std::ifstream inputFile;
    inputFile.open(filename);
    if (inputFile.is_open()) {
        std::string line;
        std::getline(inputFile, line); // first line = root dir
        while (std::getline(inputFile, line)) {
            if (line == "$ ls") {
                do {
                    std::getline(inputFile, line);
                    std::stringstream s(line);
                    std::string part1, part2;
                    s >> part1 >> part2;
                    if (part1 == "dir") { // this is a directory
                        _dir * newDir = new _dir();
                        newDir->parentDir = curDir;
                        newDir->size = 0;
                        curDir->dirs.insert({part2,newDir });
                    }
                    else if (part2 != "cd") { // this is a file
                        int size = 0;
                        std::stringstream stoi(part1);
                        stoi >> size;
                        curDir->size += size;
                        _dir* upStream = curDir->parentDir;
                         do if (upStream != NULL) { // make sure to add the file size up the chain of parent directories.
                            upStream->size += size;
                            upStream = upStream->parentDir;
                        } while (upStream != NULL);
                        
                        curDir->files.insert({ part2,size });
                    }
                } while (line.find("$ cd") == std::string::npos && !inputFile.eof());
            }
            if (line.substr(0, 4) == "$ cd") {
                std::string cmd = line.substr(5, line.length());
                if (cmd == "..") {
                    curDir = curDir->parentDir;
                }
                else {
                    curDir = curDir->dirs.at(cmd);
                }
            }
        }
    }
    return root;
}

void sumDirTotalSizeAtMost100000(_dir* root, int &sizes) { // recursively add up the sizes
    int size = 0;
    for (std::map<std::string, _dir*>::iterator it = root->dirs.begin(); it != root->dirs.end(); it++) {
        if (it->second->size < 100000) sizes += it->second->size;
        if (it->second->dirs.size() > 0) sumDirTotalSizeAtMost100000(it->second, sizes);
    }
}

void findFolderToDelete(_dir* root, int sizeneeded, int &smallest) { // recursively look for the smallest.
    int smallestSoFar = smallest;
    for (std::map<std::string, _dir*>::iterator it = root->dirs.begin(); it != root->dirs.end(); it++) {
        if (it->second->size > sizeneeded) {
            if (smallest == 0 || smallestSoFar > it->second->size) {
                smallest = it->second->size;
            }
        }
        if (it->second->dirs.size() > 0) findFolderToDelete(it->second, sizeneeded, smallest);
    }
 }

#define TOTAL_SPACE 70000000
#define SPACE_NEEDED 30000000

int main()
{
    _dir* root = getInput("input.txt");
   
    // part 1
    int sizes = 0;
    sumDirTotalSizeAtMost100000(root, sizes);
    std::cout << "Answer to Part1 = " << sizes << std::endl;

    // part2
    int smallest = 0;
    int freeSpace = TOTAL_SPACE - root->size;
    int spaceNeeded = SPACE_NEEDED - freeSpace;
    findFolderToDelete(root, spaceNeeded, smallest);
    std::cout << "Answer to Part2 = " << smallest << std::endl;
}
