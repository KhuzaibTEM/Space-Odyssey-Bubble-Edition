#ifndef SAVINGGAME_H
#define SAVINGGAME_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "constants.h"

bool saveGame(const std::string &filename, sf::Sprite bubbleGrid[][MAX_COLS], bool occupied[][MAX_COLS], int score, int currentRowCount);
bool loadGame(const std::string &filename, sf::Sprite bubbleGrid[][MAX_COLS], bool occupied[][MAX_COLS], int &score, int &currentRowCount, sf::Texture &bubblesTexture);

// Save the game to a simple text format
// Format:
// <score>\n
// <currentRowCount>\n
// Then MAX_ROWS lines each with MAX_COLS ints (-1 = empty, n = color index)
bool saveGame(const std::string &filename, sf::Sprite bubbleGrid[][MAX_COLS], bool occupied[][MAX_COLS], int score, int currentRowCount) {
    std::ofstream out(filename);
    if (!out) return false;
    out << score << std::endl;
    out << currentRowCount << std::endl;
    for (int r = 0; r < MAX_ROWS; r++) {
        for (int c = 0; c < MAX_COLS; c++) {
            if (!occupied[r][c]) out << -1;
            else {
                int left = bubbleGrid[r][c].getTextureRect().left;
                int colorIndex = left / 64;
                out << colorIndex;
            }
            if (c + 1 < MAX_COLS) out << " ";
        }
        out << std::endl;
    }
    out.close();

    return true;
}

bool loadGame(const std::string &filename, sf::Sprite bubbleGrid[][MAX_COLS], bool occupied[][MAX_COLS], int &score, int &currentRowCount, sf::Texture &bubblesTexture) {
    std::ifstream in(filename);
    if (!in) return false;
    if (!(in >> score)) return false;
    if (!(in >> currentRowCount)) return false;
    std::string line;
    std::getline(in, line); // consume end of second line
    for (int r = 0; r < MAX_ROWS; r++) {
        if (!std::getline(in, line)) break;
        std::istringstream iss(line);
        for (int c = 0; c < MAX_COLS; c++) {
            int v = -1;
            if (!(iss >> v)) v = -1;
            if (v < 0) {
                occupied[r][c] = false;
            } 
            else {
                occupied[r][c] = true;
                bubbleGrid[r][c].setTexture(bubblesTexture);
                bubbleGrid[r][c].setTextureRect(sf::IntRect(v * 64, 0, 64, 64));
                // Ensure the sprite is positioned correctly in the grid
                bubbleGrid[r][c].setPosition((float)(c * 64), (float)(r * 64));
            }
        }
    }
    in.close();
    // Debug: print first row values
    std::cout << "Loaded save: score=" << score << " rows=" << currentRowCount << std::endl;
    return true;
}

#endif
