#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <unordered_map>
#include "Random.h"
#include "TextureManager.h"
#include "Tile.h"
#include "Board.h"
using namespace std;
/*
int main() {
    TextureManager::SetImagesDirectory("images/");
    sf::Texture texture;

    unordered_map<string, sf::Texture> textures;
    //textures["space"].loadFromFile("images/space.png");
    //textures["station"].loadFromFile("images/station.png");
    //textures["asteroid"].loadFromFile("images/asteroid.png");
    sf::Sprite digitsSprite(TextureManager::GetTexture("digits"));
    sf::Sprite face_winSprite(TextureManager::GetTexture("face_happy"));
    sf::Sprite face_loseSprite(TextureManager::GetTexture("face_lose"));
    //sf::Sprite clearButton(TextureManager::GetTexture("btnClear"));
    sf::Sprite playerShip(TextureManager::GetTexture("ship"));
    //window.draw(playerShip);
    cout << "Hello, World!" << std::endl;
    TextureManager::Clear();
    return 0;
}
*/
#include <SFML/Graphics.hpp>

void ReadFile(const char* fileName, map <string, int>& configs) {
    ifstream file(fileName);
    if (file.is_open()) {
        int width, height, mineNumber;
        string tempwidth, tempheight, temp;

        file >> tempwidth;
        width = stoi(tempwidth);
        configs.emplace("width", width);
        file >> tempheight;
        height = stoi(tempheight);
        configs.emplace("height", height);
        file >> temp;
        mineNumber = stoi(temp);
        configs.emplace("mineNumber", mineNumber);
    }
    file.close();
}

int main() {
    map<string, int> configs;
    ReadFile("boards/config.cfg", configs);
    auto height1 = configs.find("height");
    int height = height1->second;
    int heightWindow = (height * 32) + 100;
    auto width1 = configs.find("width");
    int width = width1->second;
    int widthWindow = width * 32;
    auto temp1 = configs.find("mineNumber");
    int mineNumber = temp1->second;
    int minesLeft = mineNumber;
    int tileNumber = height * width;
    sf::Sprite hiddenTile(TextureManager::GetTexture("tile_hidden"));
    sf::Texture texture;
    sf::RenderWindow window(sf::VideoMode(widthWindow , heightWindow ), "Minesweeper");

    Board board = Board(width, height, mineNumber);
    board.RandomBoard();
    board.SetMineNumber(mineNumber);

    sf::Sprite debugger(TextureManager::GetTexture("debug"));
    debugger.setPosition((widthWindow / 2) + 96, heightWindow - 100);
    sf::Vector2f debugPos = debugger.getPosition();
    sf::Sprite test1(TextureManager::GetTexture("test_1"));
    test1.setPosition((widthWindow / 2) + 160, heightWindow - 100);
    sf::Vector2f test1Pos = test1.getPosition();
    sf::Sprite test2(TextureManager::GetTexture("test_2"));
    test2.setPosition((widthWindow / 2) + 224, heightWindow - 100);
    sf::Vector2f test2Pos = test2.getPosition();
    sf::Sprite test3(TextureManager::GetTexture("test_3"));
    test3.setPosition((widthWindow / 2) + 288, heightWindow - 100);
    sf::Vector2f test3Pos = test3.getPosition();
    sf::Sprite faceHappy(TextureManager::GetTexture("face_happy"));
    faceHappy.setPosition((widthWindow / 2) - 32, heightWindow - 100);
    sf::Vector2f facePos = faceHappy.getPosition();
    unordered_map<string, sf::Texture> textures;
    sf::Sprite digitsSprite(TextureManager::GetTexture("digits"));
    digitsSprite.setPosition(32, heightWindow - 100);
    sf::Sprite flag(TextureManager::GetTexture("flag"));
    vector<sf::IntRect> rectDigit;
    for (int index = 0; index < 211; index += 21) {
        rectDigit.push_back(sf::IntRect(index, 0, 21, 32));
    }
    vector<int> numbers = board.digit(board.GetMine());
    vector<sf::Sprite> displayDigits;
    for (int row = 0, col = 50; row < 3; row++) {
        displayDigits.push_back(sf::Sprite(digitsSprite));
        displayDigits.at(row).setPosition(col, heightWindow - 100);
        col += 21;
        displayDigits.at(row).setTextureRect(rectDigit.at(numbers.at(row)));
    }
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i location = sf::Mouse::getPosition(window);
                    sf::Vector2f locationF = static_cast<sf::Vector2f>(location);
                    sf::Vector2i test1 = sf::Mouse::getPosition(window);
                    sf::Vector2i test2 = sf::Mouse::getPosition(window);
                    sf::Vector2i test3 = sf::Mouse::getPosition(window);
                    sf::Vector2i randomPos = sf::Mouse::getPosition(window);
                    sf::Vector2i debugPos = sf::Mouse::getPosition(window);
                    if (location.y < height * 32) {
                        Tile *current = &board.GetTile(25 * (location.y / 32) + (location.x / 32));
                        board.Reveal(current);
                        board.GetGameDone();
                        if (board.GetWin()) {
                            faceHappy.setTexture(TextureManager::GetTexture("face_win"));
                            for (int index = 0; index < 3; index++) {
                                numbers.at(index) = 0;
                                displayDigits.at(index).setTextureRect(rectDigit.at(numbers.at(index)));
                            }
                        }
                        if (board.GetGameDone()) {
                            faceHappy.setTexture(TextureManager::GetTexture("face_lose"));
                        }
                    }
                    else if ((location.x >= (widthWindow / 2) + 96 && location.x < (widthWindow / 2) + 160) &&
                                 (location.y >= (heightWindow - 100) && location.y < heightWindow + 64)) {
                        board.SetDebug(!(board.IsDebug()));
                        board.Debug();
                    }
                    else if ((location.x >= (widthWindow / 2) + 160 && location.x < (widthWindow / 2) + 224) &&
                                 (location.y >= (heightWindow - 100) && location.y < heightWindow + 64)) {
                        board.InitialBoard(1);
                        faceHappy.setTexture(TextureManager::GetTexture("face_happy"));
                        numbers = SetUp::number(board.GetMine() - board.GetFlag());
                        for (int index = 0; index < 3; index++) {
                            displayDigits.at(index).setTextureRect(rectDigit.at(numbers.at(index)));
                        }

                    }
                    else if ((location.x >= (widthWindow / 2) + 224 && location.x < (widthWindow / 2) + 288) &&
                                 (location.y >= (heightWindow - 100) && location.y < heightWindow + 64)) {
                        board.InitialBoard(2);
                        for(unsigned int index = 0; index < board.GetSize(); index++) {
                            sf::Sprite tile(TextureManager::GetTexture("tile_hidden"));
                            tile.setPosition(board.GetTile(index).GetLocation());
                            window.draw(tile);
                            window.draw(board.GetTile(index).GetSprite());
                        }
                    }
                    else if ((location.x >= (widthWindow / 2) + 288)  && (location.y >= (heightWindow - 100) )) {
                        board.InitialBoard(3);
                        faceHappy.setTexture(TextureManager::GetTexture("face_happy"));
                        numbers = SetUp::number(board.GetMine() - board.GetFlag());
                        for (int index = 0; index < 3; index++) {
                            displayDigits.at(index).setTextureRect(rectDigit.at(numbers.at(index)));
                        }

                    }
                    else if ((location.x >= (widthWindow / 2 ) - 32 && location.x < (widthWindow / 2) + 64) &&
                        (location.y >= (heightWindow - 100) && location.y < heightWindow + 64)) {
                        board.RandomBoard();
                        faceHappy.setTexture(TextureManager::GetTexture("face_happy"));
                        numbers = SetUp::number(board.GetMine() - board.GetFlag());
                        for (int index = 0; index < 3; index++) {
                            displayDigits.at(index).setTextureRect(rectDigit.at(numbers.at(index)));
                        }
                    }
                    else if (event.mouseButton.button == sf::Mouse::Right) {
                            sf::Vector2i location = sf::Mouse::getPosition(window);
                            if (location.y < height * 32) {
                                Tile *currentLocation = &board.GetTile(25 * (location.y / 32) + (location.x / 32));
                                board.SwitchFlag(currentLocation);
                                numbers = SetUp::number(board.GetMine() - board.GetFlag());
                                for (int index = 0; index < 3; index++) {
                                    displayDigits.at(index).setTextureRect(rectDigit.at(numbers.at(index)));
                                }
                            }
                    }
                }
            }
        }
        window.clear();
        window.draw(debugger);
        window.draw(test1);
        window.draw(test2);
        window.draw(test3);
        window.draw(faceHappy);
        for(unsigned int index = 0; index < board.GetSize(); index++) {
            sf::Sprite tile(TextureManager::GetTexture("tile_hidden"));
            tile.setPosition(board.GetTile(index).GetLocation());
            window.draw(tile);
            window.draw(board.GetTile(index).GetSprite());
        }
        for (int index = 0; index < 3; index++) {
            window.draw(displayDigits.at(index));
        }
        for (unsigned int index = 0; index < board.GetSize(); index++) {
            window.draw(board.GetTile(index).GetSprite());
        }
        window.display();
    }

    TextureManager::Clear();
    return 0;
}
