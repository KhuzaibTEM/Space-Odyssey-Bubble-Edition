#ifndef COLLISIONACTION_H
#define COLLISIONACTION_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "AngleCalc.h"
#include "constants.h"

void clusterDetectAndHandle(int startRow, int startCol, sf::Sprite bubbleGrid[][MAX_COLS], bool occupied[][MAX_COLS], int &currentRowCount, int &score, sf::Sound& hitSound);
bool placeNearestNeighborAndHandle(int row, int col, sf::Sprite &BallToShoot, sf::Sprite BubbleSpriteTop, sf::Sprite bubbleGrid[][MAX_COLS], bool occupied[][MAX_COLS], int &currentRowCount, bool &ballActive, bool &placed, int &score, sf::Sound& hitSound);
bool fallbackColumnPlace(int col, sf::Sprite &BallToShoot, sf::Sprite BubbleSpriteTop, sf::Sprite bubbleGrid[][MAX_COLS], bool occupied[][MAX_COLS], int &currentRowCount, bool &ballActive, bool &placed, int &score, sf::Sound& hitSound);
bool placeAtTopIfReached(sf::Vector2f &position, sf::Sprite &BallToShoot, sf::Sprite BubbleSpriteTop, sf::Sprite bubbleGrid[][MAX_COLS], bool occupied[][MAX_COLS], int &currentRowCount, bool &ballActive, int &score, sf::Sound& hitSound);

void clusterDetectAndHandle(int startR, int startC, sf::Sprite bubbleGrid[MAX_ROWS][MAX_COLS], bool occupied[MAX_ROWS][MAX_COLS], int &currentRowCount, int &score, sf::Sound& hitSound) {
    int toRemove[MAX_ROWS][MAX_COLS];
    for (int r = 0; r < MAX_ROWS; r++) {
        for (int c = 0; c < MAX_COLS; c++) {
            toRemove[r][c] = 0;
        }
    }
    toRemove[startR][startC] = 1;
    bool changed = true;
    while (changed) {
        changed = false;
        for (int r = 0; r < MAX_ROWS; r++) {
            for (int c = 0; c < MAX_COLS; c++) {
                if (toRemove[r][c]) continue;
                if (!occupied[r][c]) continue;
                int colorHere = bubbleGrid[r][c].getTextureRect().left / 64;
                int DeltaRowSteps4[4] = {-1, 1, 0, 0};
                int DeltaColSteps4[4] = {0, 0, -1, 1};
                for (int k = 0; k < 4; k++) {
                    int neighborRow = r + DeltaRowSteps4[k];
                    int neighborCol = c + DeltaColSteps4[k];
                    if (neighborRow < 0 || neighborRow >= MAX_ROWS || neighborCol < 0 || neighborCol >= MAX_COLS) continue;
                    if (!toRemove[neighborRow][neighborCol]) continue;
                    int colorN = bubbleGrid[neighborRow][neighborCol].getTextureRect().left / 64;
                    if (colorN == colorHere) {
                        toRemove[r][c] = 1;
                        changed = true;
                        break;
                    }
                }
            }
        }
    }
    int members = 0;
    for (int r = 0; r < MAX_ROWS; r++) {
        for (int c = 0; c < MAX_COLS; c++) {
            if (toRemove[r][c]) members++;
        }
    }
    if (members >= 3) {
        for (int r = 0; r < MAX_ROWS; r++) {
            for (int c = 0; c < MAX_COLS; c++) {
                if (toRemove[r][c]) occupied[r][c] = false;
            }
        }
        // increment score by number of removed bubbles
        score += members;
        int highest = 0;
        for (int r = 0; r < MAX_ROWS; r++) {
            for (int c = 0; c < MAX_COLS; c++) {
                if (occupied[r][c] && r + 1 > highest) highest = r + 1;
            }
        }
        hitSound.play();
        currentRowCount = (highest > 0) ? highest : 0;
    }
}

bool placeNearestNeighborAndHandle(int row, int col, sf::Sprite &BallToShoot, sf::Sprite BubbleSpriteTop, sf::Sprite bubbleGrid[MAX_ROWS][MAX_COLS], bool occupied[MAX_ROWS][MAX_COLS], int &currentRowCount, bool &ballActive, bool &placed, int &score, sf::Sound& hitSound) {
    int DeltaRowSteps[] = {0, 0, -1, 1, -1, -1, 1, 1};
    int DeltaColSteps[] = {-1, 1, 0, 0, -1, 1, -1, 1};
    int bestRow = -1, bestCol = -1;
    float bestDist2 = 1e9f;
    sf::Vector2f ballCenter = BallToShoot.getPosition();
    for (int i = 0; i < 8; i++) {
        int newRow = row + DeltaRowSteps[i];
        int newCol = col + DeltaColSteps[i];
        if (newRow < 0 || newRow >= MAX_ROWS || newCol < 0 || newCol >= MAX_COLS) continue;
        if (occupied[newRow][newCol]) continue;
        float centerX = newCol * 64.f + 32.f;
        float centerY = newRow * 64.f + 32.f;
        float dx2 = ballCenter.x - centerX;
        float dy2 = ballCenter.y - centerY;
        float dist2 = dx2*dx2 + dy2*dy2;
        if (dist2 < bestDist2) {
            bestDist2 = dist2;
            bestRow = newRow;
            bestCol = newCol;
        }
    }

    if (bestRow != -1) {
        int shotColor = BallToShoot.getTextureRect().left / 64;
        bubbleGrid[bestRow][bestCol] = BubbleSpriteTop;
        bubbleGrid[bestRow][bestCol].setTextureRect(sf::IntRect(shotColor * 64, 0, 64, 64));
        bubbleGrid[bestRow][bestCol].setPosition(bestCol * 64, bestRow * 64);
        occupied[bestRow][bestCol] = true;
        if (bestRow + 1 > currentRowCount) currentRowCount = bestRow + 1;
        clusterDetectAndHandle(bestRow, bestCol, bubbleGrid, occupied, currentRowCount, score, hitSound);
        ballActive = false;
        placed = true;
        return true;
    }
    return false;
}

bool fallbackColumnPlace(int col, sf::Sprite &BallToShoot, sf::Sprite BubbleSpriteTop, sf::Sprite bubbleGrid[MAX_ROWS][MAX_COLS], bool occupied[MAX_ROWS][MAX_COLS], int &currentRowCount, bool &ballActive, bool &placed, int &score, sf::Sound& hitSound) {
    int placeRow = -1;
    for (int r = 0; r < MAX_ROWS; r++) {
        if (!occupied[r][col]) {
            placeRow = r;
            break;
        }
    }
    if (placeRow == -1) {
        placed = true;
        ballActive = false;
        return true;
    }
    int shotColor = BallToShoot.getTextureRect().left / 64;
    bubbleGrid[placeRow][col] = BubbleSpriteTop;
    bubbleGrid[placeRow][col].setTextureRect(sf::IntRect(shotColor * 64, 0, 64, 64));
    bubbleGrid[placeRow][col].setPosition(col * 64, placeRow * 64);
    occupied[placeRow][col] = true;
    if (placeRow + 1 > currentRowCount) currentRowCount = placeRow + 1;
    clusterDetectAndHandle(placeRow, col, bubbleGrid, occupied, currentRowCount, score, hitSound);
    ballActive = false;
    placed = true;
    return true;
}

bool placeAtTopIfReached(sf::Vector2f &position, sf::Sprite &BallToShoot, sf::Sprite BubbleSpriteTop, sf::Sprite bubbleGrid[MAX_ROWS][MAX_COLS], bool occupied[MAX_ROWS][MAX_COLS], int &currentRowCount, bool &ballActive, int &score, sf::Sound& hitSound) {
    int col = static_cast<int>(rounding(position.x / 64.f));
    if (col < 0) col = 0;
    if (col >= MAX_COLS) col = MAX_COLS - 1;
    int placeRow = -1;
    for (int r = 0; r < MAX_ROWS; r++) {
        if (!occupied[r][col]) {
            placeRow = r;
            break;
        }
    }
    if (placeRow != -1) {
        int shotColor = BallToShoot.getTextureRect().left / 64;
        bubbleGrid[placeRow][col] = BubbleSpriteTop;
        bubbleGrid[placeRow][col].setTextureRect(sf::IntRect(shotColor * 64, 0, 64, 64));
        bubbleGrid[placeRow][col].setPosition(col * 64, placeRow * 64);
        occupied[placeRow][col] = true;
        if (placeRow + 1 > currentRowCount) currentRowCount = placeRow + 1;
        clusterDetectAndHandle(placeRow, col, bubbleGrid, occupied, currentRowCount, score, hitSound);
        ballActive = false;
        return true;
    }
    ballActive = false;
    return false;
}

#endif
