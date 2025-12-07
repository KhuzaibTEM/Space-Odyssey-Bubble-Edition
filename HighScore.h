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
        std::string line;
        while (std::getline(readHighscore, line) && len < 100) {
            if (line.empty()) continue;
            if (len >= 100) break;
            scores[len++] = stringToInteger(line);
        }
    }
    readHighscore.close();

    if (len < 100) scores[len++] = newHighScore;
    else scores[99] = newHighScore;

    RevSorting(scores);

    if (len > 20) len = 20;

    std::ofstream writeHighscore("HighScore.txt");
    if (writeHighscore) {
        for (int i = 0; i < len; i++) {
            writeHighscore << IntegerToString(scores[i]);
            if (i + 1 < len) writeHighscore << std::endl;
        }
    }
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
    std::string line;
    int yDown = 0;
    int standing = 1;
    sf::Text HighScoreText("", scoreFont, 30);
    while (std::getline(readHighscore, line)) {
        if (standing == 1) HighScoreText.setString(IntegerToString(standing) + "st  " + line);
        else if (standing == 2) HighScoreText.setString(IntegerToString(standing) + "nd  " + line);
        else if (standing == 3) HighScoreText.setString(IntegerToString(standing) + "rd  " + line);
        else HighScoreText.setString(IntegerToString(standing) + "th  " + line);
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