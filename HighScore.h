#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>

#include "Calculations.h"
#include "constants.h"


void drawHighScore(sf::RenderWindow &window, sf::Font &scoreFont, sf::Font &menuFont);
void newHighScore(int newHighScore);

void newHighScore(int newHighScore) {
    int scores[100];
    int len = 0;
    for (int i = 0; i < 100; i++) scores[i] = 0;

    std::ifstream readHighscore("HighScore.txt");
    if (readHighscore) {
        int line;
        while (readHighscore >> line && len < 100) {
            if (!line) continue;
            if (len >= 100) break;
            scores[len++] = line;
        }
    }
    readHighscore.close();

    if (len < 100 && newHighScore != 0) scores[len++] = newHighScore;
    else scores[99] = newHighScore;

    RevSorting(scores);

    if (len > 10) len = 10;

    std::ofstream writeHighscore("HighScore.txt");
    if (writeHighscore) {
        for (int i = 0; i < len; i++) {
            writeHighscore << IntegerToString(scores[i]);
            if (i + 1 < len) writeHighscore << std::endl;
        }
    }
    writeHighscore.close();
}

void drawHighScore(sf::RenderWindow &window, sf::Font &scoreFont, sf::Font &menuFont) {
    sf::RectangleShape HighScoreOverlay(sf::Vector2f(WIDTH, HEIGHT));
	HighScoreOverlay.setFillColor(sf::Color(0, 0, 0, 140));
	window.draw(HighScoreOverlay);

    sf::RectangleShape BackToMenuButton;
    BackToMenuButton.setSize(sf::Vector2f(300, 80));
    BackToMenuButton.setPosition(BackToMenuButtonX, BackToMenuButtonY);
    BackToMenuButton.setFillColor(sf::Color(30,30,30,200));
    BackToMenuButton.setOutlineColor(sf::Color::White);
    BackToMenuButton.setOutlineThickness(3.f);

    sf::Text BackToMenuText("Back", menuFont, 30);
    BackToMenuText.setPosition(BackToMenuButtonX + 45, BackToMenuButtonY + 23);
    BackToMenuText.setFillColor(sf::Color::White);

    std::ifstream readHighscore("HighScore.txt");
    int line;
    int yDown = 0;
    int standing = 1;
    
    newHighScore(0);
    sf::Text HighScoreText("", scoreFont, 30);
    while (readHighscore >> line) {
        if (standing == 1) HighScoreText.setString(IntegerToString(standing) + "st  " + IntegerToString(line));
        else if (standing == 2) HighScoreText.setString(IntegerToString(standing) + "nd  " + IntegerToString(line));
        else if (standing == 3) HighScoreText.setString(IntegerToString(standing) + "rd  " + IntegerToString(line));
        else HighScoreText.setString(IntegerToString(standing) + "th  " + IntegerToString(line));
        HighScoreText.setPosition(HighScoreDispX, 25 + yDown);
        HighScoreText.setFillColor(sf::Color::White);
        window.draw(HighScoreText);
        yDown += 50;
        standing++;
    }
    readHighscore.close();
    window.draw(BackToMenuButton);
    window.draw(BackToMenuText);
}

#endif
