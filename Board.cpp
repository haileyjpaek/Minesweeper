//
// Created by Hailey Paek on 4/20/22.
//

#include "Board.h"
#include "Tile.h"
#include "Random.h"
#include <fstream>
using std::ifstream;
#include <vector>

Board::Board(unsigned int _height, unsigned int _width, unsigned int _mineNumber) {
    height = _height;
    width = _width;
    mineNumber = _mineNumber;
}

Tile& Board::GetTile(unsigned int tile) {
    return board.at(tile);
}

unsigned int Board::GetHeight() {
    return height;
}

unsigned int Board::GetWidth() {
    return width;
}

unsigned int Board::GetSize() {
    return height * width;
}

void Board::Debug()
{
    if(debug) {
        for(unsigned int index = 0; index < board.size(); index++) {
            if(board.at(index).IsMine()) {
                board.at(index).SetSprite("mine");
            }
            else if(board.at(index).IsFlag()) {
                board.at(index).SetSprite("flag");
            }
        }
    }
    else {
        for(unsigned int index = 0; index < board.size(); index++) {
            board.at(index).SetSprite("tile_hidden");
        }
    }
}
void Board::SetMineNumber(unsigned int mineNumber) {
    Board::mineNumber = mineNumber;
}
void Board::InitialBoard(int test)
{
    vector<char> mines = SetUp::read(test);
    board.clear();
    vector<char> mapBoard = SetUp::read(test);
    for(int row = 0; row < width; row++) {
        for(int col = 0; col < height; col++) {
            sf::Vector2f location = sf::Vector2f(col * 32, row * 32);
            Tile tile = Tile(location, "tile_hidden");
            board.push_back(tile);
        }
    }
    for(int index = 0; index < mapBoard.size(); index++) {
        if(mapBoard[index] == '1') {
            board.at(index).SetMine(true);
        }
        else if(mapBoard[index] == '0') {
            board.at(index).SetMine(false);
        }
    }
    SetMines();
    GetNextTo();
}

void Board::RandomBoard()
{
    bool mine, hidCondition, empty;
    vector<int> mineRandom;
    mineRandom.push_back(Random::Int(0, 399));
    while(mineRandom.size() < 50) {
        int var = Random::Int(0, 399);
        bool val = false;
        for(unsigned int index = 0; index < mineRandom.size(); index++) {
            if(var == mineRandom.at(index)) {
                val = true;
                break;
            }
        }
        if(val == false) {
            mineRandom.push_back(var);
        }
    }
    done = false;
    win = false;
    board.clear();
    mineNumber = 0;
    flagNumber = 0;

    for(unsigned int row = 0; row < width; row++) {
        for(unsigned int col = 0; col < height; col++) {
            sf::Vector2f spot = sf::Vector2f((float)(col) * 32, (float)(row) * 32);
            bool hidCondition = empty;
            Tile index = Tile(spot, "tile_hidden");
            board.push_back(index);
        }
    }

    for(unsigned int index = 0; index < mineRandom.size(); index++) {
        board.at(mineRandom.at(index)).SetHiddenCondition(mine);
        mineNumber++;
        if(debug) {
            board.at(mineRandom.at(index)).SetSprite("mine");
        }
    }
    SetMines();
    SetNumbers();
}

void Board::SetDebug(bool debugged) {
    Board::debug = debugged;
}

bool Board::IsDebug() const {
    return debug;
}

bool Board::GetGameDone() {
    return done;
}
void Board::GameDone() {
    for(int index = 0; index < board.size(); index++) {
        if(board.at(index).IsMine()) {
            board.at(index).SetSprite("mine");
        }
    }
}

void Board::SetGameDone() {
    done = true;
    bool mine;
    for(unsigned int index = 0; index < board.size(); index++) {
        board.at(index).SetLeftClick(false);
        board.at(index).SetRightClick(false);
        if(board.at(index).GetHiddenCondition() == mine) {
            board.at(index).SetSprite("mine");
        }
    }
}

void Board::SetNumbers() {
    for(unsigned int row = 0; row < board.size(); row++) {
        bool mine, empty;
        if(!board.at(row).GetHiddenCondition() == mine) {
            int mineNextTo = 0;
            for (unsigned int col = 0; col < board.at(row).GetCount(); col++) {
                Tile *var = board.at(row).GetNextTo(col);
                if (var->GetHiddenCondition() == mine) {
                    mineNextTo++;
                }
            }
            if (mineNextTo == 1) {
                board.at(row).SetHiddenCondition(1);
            } else if (mineNextTo == 2) {
                board.at(row).SetHiddenCondition(2);
            } else if (mineNextTo == 3) {
                board.at(row).SetHiddenCondition(3);
            } else if (mineNextTo == 4) {
                board.at(row).SetHiddenCondition(4);
            } else if (mineNextTo == 5) {
                board.at(row).SetHiddenCondition(5);
            } else if (mineNextTo == 6) {
                board.at(row).SetHiddenCondition(6);
            } else if (mineNextTo == 7) {
                board.at(row).SetHiddenCondition(7);
            } else if (mineNextTo == 8) {
                board.at(row).SetHiddenCondition(8);
            } else {
                board.at(row).SetHiddenCondition(empty);
            }
        }
    }
}

void Board::SetMines() {
    for (unsigned int index = 0; index < board.size(); index++) {
        if (index == 0) {
            board.at(index).AddNextTo(&board.at(1));
            board.at(index).AddNextTo(&board.at(width));
            board.at(index).AddNextTo(&board.at(width + 1));
        } else if (index == width - 1) {
            board.at(index).AddNextTo(&board.at(index - 2));
            board.at(index).AddNextTo(&board.at(index * 2));
            board.at(index).AddNextTo(&board.at((index * 2) + 1));
        } else if (index == (height * width) - width) {
            board.at(index).AddNextTo(&board.at(index - width));
            board.at(index).AddNextTo(&board.at(index - width + 1));
            board.at(index).AddNextTo(&board.at(index + 1));
        } else if (index == (height * width) - 1) {
            board.at(index).AddNextTo(&board.at(index - width));
            board.at(index).AddNextTo(&board.at(index - width - 1));
            board.at(index).AddNextTo(&board.at(index - 1));
        } else if (index > 0 && index < width - 1) {
            board.at(index).AddNextTo(&board.at(index - 1));
            board.at(index).AddNextTo(&board.at(index + 1));
            board.at(index).AddNextTo(&board.at(index + width - 1));
            board.at(index).AddNextTo(&board.at(index + width));
            board.at(index).AddNextTo(&board.at(index + width + 1));
        } else if (index > (height * width) - width && index < (height * width) - 1) {
            board.at(index).AddNextTo(&board.at(index - width - 1));
            board.at(index).AddNextTo(&board.at(index - width));
            board.at(index).AddNextTo(&board.at(index - width + 1));
            board.at(index).AddNextTo(&board.at(index - 1));
            board.at(index).AddNextTo(&board.at(index + 1));
        } else if (index % width == 0) {
            board.at(index).AddNextTo(&board.at(index + 1));
            board.at(index).AddNextTo(&board.at(index + 1 - width));
            board.at(index).AddNextTo(&board.at(index + 1 + width));
            board.at(index).AddNextTo(&board.at(index + width));
            board.at(index).AddNextTo(&board.at(index - width));
        } else if ((index + 1) % width == 0) {
            board.at(index).AddNextTo(&board.at(index - 1));
            board.at(index).AddNextTo(&board.at(index - width));
            board.at(index).AddNextTo(&board.at(index + width));
            board.at(index).AddNextTo(&board.at(index - 1 - width));
            board.at(index).AddNextTo(&board.at(index - 1 + width));
        } else {
            board.at(index).AddNextTo(&board.at(index - 1));
            board.at(index).AddNextTo(&board.at(index - 1 + width));
            board.at(index).AddNextTo(&board.at(index - 1 - width));
            board.at(index).AddNextTo(&board.at(index + 1));
            board.at(index).AddNextTo(&board.at(index + 1 + width));
            board.at(index).AddNextTo(&board.at(index + 1 - width));
            board.at(index).AddNextTo(&board.at(index + width));
            board.at(index).AddNextTo(&board.at(index - width));
        }
    }
}

void Board::GetNextTo() {
    for(unsigned int row = 0; row < board.size(); row++) {
        if(!(board.at(row).IsMine())) {
            int counter = 0;
            int size = board.at(row).GetNextTo().size();
            for(int col = 0; col < board.at(row).GetCount(); col++) {
                Tile* i = board.at(row).GetNextTo(col);
                if(i->IsMine() == mine) {
                    counter++;
                }
            }
            if(counter == 1) {
                board.at(row).SetMineNextTo(1);
            }
            else if(counter == 2) {
                board.at(row).SetMineNextTo(2);
            }
            else if(counter == 3) {
                board.at(row).SetMineNextTo(3);
            }
            else if(counter == 4) {
                board.at(row).SetMineNextTo(4);
            }
            else if(counter == 5) {
                board.at(row).SetMineNextTo(5);
            }
            else if(counter == 6) {
                board.at(row).SetMineNextTo(6);
            }
            else if(counter == 7) {
                board.at(row).SetMineNextTo(7);
            }
            else if(counter == 8) {
                board.at(row).SetMineNextTo(8);
            }
            else {
                board.at(row).SetMine(empty);
            }
        }
    }
}

vector<int> Board::digit(int num) {
    vector <int> digits;
    if(num < -9) {
        digits.push_back(10);
        int var = (num * -1) / 10;
        digits.push_back(var);
        var = (num * -1) % 10;
        digits.push_back(var);
    }
    else if(num < 0) {
        digits.push_back(10);
        digits.push_back(0);
        digits.push_back(num * -1);
    }
    else if(num < 100) {
        digits.push_back(0);
        int var = num / 10;
        digits.push_back(var);
        var = num % 10;
        digits.push_back(var);
    }
    else if(num < width * height) {
        int var = (num * -1) / 10;
        digits.push_back(var);
        var = (num * 100) % 10;
        digits.push_back(var);
        var = num % 10;
        digits.push_back(var);
    }
    return digits;
}

void Board::Reveal(Tile *tile) {
    bool endGame = tile->Reveal();
    if(endGame) {
        SetGameDone();
    }
}

void Board::SwitchFlag(Tile *tile) {
    tile->SwitchFlag(debug);
}

void Board::SetFlag(int flag) {
    Board::flag = flag;
}

bool Board::GetWin() {
    int counter = 0;
    bool reveal, mine;
    for(unsigned int index = 0; index < GetSize(); index++) {
        if(board.at(index).GetCondition() == reveal) {
            counter++;
        }
    }
    if(GetSize() - counter - mineNumber == 0) {
        for(unsigned int index = 0; index < board.size(); index++) {
            board.at(index).SetLeftClick(false);
            board.at(index).SetRightClick(false);
            if(board.at(index).GetHiddenCondition() == mine) {
                board.at(index).SetSprite("flag");
            }
        }
        win = true;
        return true;
    }
    return false;
}

int Board::GetFlag() {
    flagNumber = 0;
    bool flagged;
    for(unsigned int index = 0; index < GetSize(); index++) {
        if(board.at(index).GetCondition() == flagged) {
            flagNumber++;
        }
        return flagNumber;
    }
}

int Board::GetMine() {
    return mineNumber;
}
