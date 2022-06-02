//
// Created by Hailey Paek on 4/20/22.
//

//
// Created by Hailey Paek on 4/14/22.
//
#include <fstream>
#include <string>
#include <vector>
#include "SetUp.h"
#include "TextureManager.h"
using std::ifstream;
using std::string;
//unordered_map<int, sf::Texture> TextureManager::textures1;
vector<char> SetUp::read(int test) {
//vector<char> SetUp::read(char* name) {
    string name = "boards/testboard" + std::to_string(test) + ".brd";
    //string name = "boards/testboard" + string(test) + ".brd";
    //string path = "boards/testboard";
    //path += test + ".brd";

    //textures1[test].loadFromFile(path);

    vector<char> mines;
    ifstream file(name);
    //vector<char> test = read(name);

    if(file.is_open()) {
        char val;
        for(int row = 0; row < 16; row++) {
            for(int col = 0; col < 25; col++) {
                file.get(val);
                //test.push_back(val);
                mines.push_back(val);
            } file.ignore(1);
        } file.close();
    }
    //return test;
    return mines;
}

vector<int> SetUp::number(int num) {
    vector<int> numbers;
    if(num < -99) {
        numbers.push_back(10);
        numbers.push_back(9);
        numbers.push_back(9);
    }
    else if(num < -9) {
        numbers.push_back(10);
        int var = (num * -1) / 10;
        numbers.push_back(var);
        var = (num * -1) % 10;
        numbers.push_back(var);
    }
    else if(num < 10) {
        numbers.push_back(0);
        numbers.push_back(0);
        numbers.push_back(num);
    }
    else if(num < 100) {
        numbers.push_back(10);
        int var = num / 10;
        numbers.push_back(var);
        var = num % 10;
        numbers.push_back(var);
    }
    else if(num <= 400) {
        int var = num / 100;
        numbers.push_back(var);
        var = num % 100;
        var /= 10;
        numbers.push_back(var);
        var = num % 10;
        numbers.push_back(var);
    }
    return numbers;
}