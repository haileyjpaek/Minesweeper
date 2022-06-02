//
// Created by Hailey Paek on 4/14/22.
//

#include "Tile.h"
#include "TextureManager.h"
#include <vector>
#include <iostream>
using namespace std;

Tile::Tile(sf::Vector2f _spot, const char* texture) {
    sprite = sf::Sprite(TextureManager::GetTexture(texture));
    sprite.setPosition(_spot.x, _spot.y);
    spot = _spot;
    condition = hidden;
    hiddenCondition = hidCondition;
    hidden = true;
    flagged = false;
    mine = false;
    leftClick = true;
    rightClick = true;
}

bool Tile::GetCondition() {
    return condition;
}

bool Tile::GetHiddenCondition() {
    return hiddenCondition;
}

void Tile::SetCondition(bool changes) {
    condition = changes;
}

void Tile::SetHiddenCondition(bool hiddenChanges) {
    hiddenCondition = hiddenChanges;
}

const sf::Sprite& Tile::GetSprite() {
    return sprite;
}

void Tile::SetSprite(const char *texture) {
    sprite.setTexture(TextureManager::GetTexture(texture));
    sprite.setPosition(spot);
}
const sf::Vector2f &Tile::GetLocation() const {
    return spot;
}

bool Tile::IsMine() const {
    return mine;
}

void Tile::SetMine(bool mine) {
    Tile::mine = mine;
}

bool Tile::Reveal() {
    if(hidden) {
        if(mine && !reveal1) {
            SetSprite("mine");
            return true;
        }
        else if(mineNextTo == 1) {
            SetSprite("number_1");
            return false;
        }
        else if(mineNextTo == 2) {
            SetSprite("number_2");
            return false;
        }
        else if(mineNextTo == 3) {
            SetSprite("number_3");
            return false;
        }
        else if(mineNextTo == 4) {
            SetSprite("number_4");
            return false;
        }
        else if(mineNextTo == 5) {
            SetSprite("number_5");
            return false;
        }
        else if(mineNextTo == 6) {
            SetSprite("number_6");
            return false;
        }
        else if(mineNextTo == 7) {
            SetSprite("number_7");
            return false;
        }
        else if(mineNextTo == 8) {
            SetSprite("number_8");
            return false;
        }
        else {
            SetSprite("tile_revealed");
            rightClick = false;
            leftClick = false;
            return false;
        }
    }
    return false;
}

void Tile::SetLeftClick(bool option) {
    if(option == true) {
        leftClick = true;
    }
    else if(option == false) {
        leftClick = false;
    }
}

void Tile::SetRightClick(bool option) {
    if(option == true) {
        rightClick = true;
    }
    else if(option == false) {
        rightClick = false;
    }
}

void Tile::SwitchFlag(bool debug) {
    if(rightClick) {
        if(condition == hidden) {
            leftClick = false;
            condition = flagged;
            SetSprite("flag");
        }
        else if(condition == flagged && debug && hidden == mine) {
            leftClick = true;
            condition = hidden;
            SetSprite("mine");
        }
        else if(condition == flagged) {
            leftClick = true;
            condition = hidden;
            SetSprite("tile_hidden");
        }
    }
}

unsigned int Tile::GetCount() {
    return nextTo.size();
}

bool Tile::IsFlag() const {
    return flagged;
}

void Tile::AddNextTo(Tile *_nextTo) {
    nextTo.push_back(_nextTo);
}

const vector<Tile *> &Tile::GetNextTo() const {
    return nextTo;
}

Tile* Tile::GetNextTo(unsigned int _nextTo) {
    return nextTo.at(_nextTo);
}

void Tile::SetMineNextTo(int mineNextTo) {
    Tile::mineNextTo = mineNextTo;
}

void Tile::RevealNextTo() {
    for(int index = 0; index < nextTo.size(); index++) {
        if(nextTo[index]->IsMine()) {
            continue;
        }
        else {
            nextTo[index]->Reveal();
            for(int col = 0; col < nextTo[index]->nextTo.size(); col++) {
                if(nextTo[index]->nextTo[col]->IsMine()) {
                    continue;
                }
                else {
                    nextTo[index]->nextTo[col]->Reveal();
                }
            }
        }
    }
    reveal1 = true;
}
