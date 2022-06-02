//
// Created by Hailey Paek on 4/14/22.
//

#ifndef PROJECT_MINESWEEPER_TILE_H
#define PROJECT_MINESWEEPER_TILE_H

#endif //PROJECT_MINESWEEPER_TILE_H
#pragma once
#include <iostream>
#include <vector>
#include "TextureManager.h"
using std::vector;
using std::string;

class Tile {
private:
    bool reveal1;
    sf::Vector2f spot;
    vector<Tile*> nextTo;
    sf::Sprite sprite;
    bool leftClick, rightClick;
    bool hidden, flagged;
    bool mine;
    int mineNextTo;
public:
    Tile(sf::Vector2f _spot, const char* texture);
    bool GetCondition();
    bool GetHiddenCondition();
    void SetCondition(bool changes);
    void SetHiddenCondition(bool hiddenChanges);
    const sf::Sprite& GetSprite();
    void SetSprite(const char* texture);
    const sf::Vector2f &GetLocation() const;
    bool IsMine() const;
    void SetMine(bool mine);
    bool Reveal();
    void SetLeftClick(bool option);
    void SetRightClick(bool option);
    void SwitchFlag(bool debug);
    unsigned int GetCount();
    bool IsFlag() const;
    void AddNextTo(Tile* _nextTo);
    const vector<Tile *> &GetNextTo() const;
    Tile* GetNextTo(unsigned int _nextTo);
    void SetMineNextTo(int mineNextTo);
    void RevealNextTo();

    bool condition;
    bool hiddenCondition;
    bool hidCondition;

};