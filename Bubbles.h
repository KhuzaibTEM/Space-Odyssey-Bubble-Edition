#ifndef BUBBLES_H
#define BUBBLES_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "constants.h"

void GridMaker(sf::Sprite TopBubbleGridInit[][20], bool BubblesOccupiedOnTop[][20], sf::Sprite BubbleSpriteTop);

void GridMaker(sf::Sprite bubbleGrid[][20], bool occupied[][20], sf::Sprite BubbleSpriteTop) {

    // Initialize occupancy and fill first 3 rows with randomized bubbles
    for (int r = 0; r < MAX_ROWS; r++) {
        for (int c = 0; c < MAX_COLS; c++) {
            occupied[r][c] = false;
        }
    }

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 20; col++) {
            int RandomColorSelecter = rand() % 4;
            bubbleGrid[row][col] = BubbleSpriteTop;
            bubbleGrid[row][col].setTextureRect(sf::IntRect(RandomColorSelecter * 64, 0, 64, 64));
            bubbleGrid[row][col].setPosition(col * 64, row * 64); // Position bubbles in grid
            occupied[row][col] = true;
        }
    }
}


#endif
