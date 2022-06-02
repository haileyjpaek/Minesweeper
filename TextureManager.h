//
// Created by Hailey Paek on 4/13/22.
//
#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;

class TextureManager
{
    static unordered_map<string, sf::Texture> textures;
    static void LoadTexture(string textureName);
    //static string imagesDirectory;
public:
    static sf::Texture& GetTexture(string textureName);
    //static void SetImagesDirectory(string directoryPath);
    static void Clear();
};
