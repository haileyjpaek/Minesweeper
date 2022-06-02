//
// Created by Hailey Paek on 4/13/22.
//
#pragma once
#include "Tile.h"
#include "SetUp.h"
#include "TextureManager.h"
#include <vector>
using std::vector;

class Board
{
private:
    int flagNumber, bomb;
    vector<Tile> board;
    unsigned int height, width, mineNumber;
    int flag = 0;
    bool debug, done, win = false;
    sf::Sprite bombs;
    bool mine, flagged, empty, reveal;
public:
    Board(unsigned int _height, unsigned int _width, unsigned int _mineNumber);
    Tile& GetTile(unsigned int tile);
    unsigned int GetHeight();
    unsigned int GetWidth();
    unsigned int GetSize();
    void Debug();
    void SetMineNumber(unsigned int mineNumber);
    void InitialBoard(int test);
    void RandomBoard();
    void SetDebug(bool debugged);
    bool IsDebug() const;
    bool GetGameDone();
    void GameDone();
    void SetGameDone();
    void SetNumbers();
    void SetMines();
    void GetNextTo();
    vector<int> digit(int num);
    void Reveal(Tile* tile);
    void SwitchFlag(Tile* tile);
    void SetFlag(int flag);
    bool GetWin();
    int GetFlag();
    int GetMine();
};
