#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.h"

void drawMainMenu(sf::RenderWindow &window, sf::Font &font);

void drawMainMenu(sf::RenderWindow &window, sf::Font &font) {

    sf::RectangleShape playButton;
    playButton.setSize(sf::Vector2f(300, 80));
    playButton.setPosition(ButtonX, ButtonPlayY);
    playButton.setFillColor(sf::Color(30,30,30,200));
    playButton.setOutlineColor(sf::Color::Blue);
    playButton.setOutlineThickness(3.f);

    sf::RectangleShape loadButton;
    loadButton.setSize(sf::Vector2f(300, 80));
    loadButton.setPosition(ButtonX, ButtonSaveY);
    loadButton.setFillColor(sf::Color(30,30,30,200));
    loadButton.setOutlineColor(sf::Color::Yellow);
    loadButton.setOutlineThickness(3.f);

    sf::RectangleShape settingButton;
    settingButton.setSize(sf::Vector2f(300, 80));
    settingButton.setPosition(ButtonX, ButtonSettingY);
    settingButton.setFillColor(sf::Color(30,30,30,200));
    settingButton.setOutlineColor(sf::Color::Green);
    settingButton.setOutlineThickness(3.f);

    sf::RectangleShape HighScoreButton;
    HighScoreButton.setSize(sf::Vector2f(300, 80));
    HighScoreButton.setPosition(ButtonHighScoreX, ButtonHighScoreY);
    HighScoreButton.setFillColor(sf::Color(30,30,30,200));
    HighScoreButton.setOutlineColor(sf::Color::Magenta);
    HighScoreButton.setOutlineThickness(3.f);

    sf::RectangleShape exitButton;
    exitButton.setSize(sf::Vector2f(300, 80));
    exitButton.setPosition(ButtonX, ButtonExitY);
    exitButton.setFillColor(sf::Color(30,30,30,200));
    exitButton.setOutlineColor(sf::Color::Red);
    exitButton.setOutlineThickness(3.f);

    sf::Text title("Space Odyssey: Bubble Edition", font, 50);
    title.setPosition(310, 100);
    title.setFillColor(sf::Color::White);

    sf::Text playText("Play", font, 30);
    playText.setPosition(615, 225);
    playText.setFillColor(sf::Color::White);

    sf::Text settingText("Settings", font, 30);
    settingText.setPosition(592, 345);
    settingText.setFillColor(sf::Color::White);

    sf::Text HighScoreText("High Scores", font, 30);
    HighScoreText.setPosition(ButtonHighScoreX + 75, ButtonHighScoreY + 23);
    HighScoreText.setFillColor(sf::Color::White);

    sf::Text loadText("Load", font, 30);
    loadText.setPosition(615, 455);
    loadText.setFillColor(sf::Color::White);

    sf::Text quitText("Quit", font, 30);
    quitText.setPosition(615, 565);
    quitText.setFillColor(sf::Color::White);

    // Draw buttons and labels (each once)
    window.draw(playButton);
    window.draw(settingButton);
    window.draw(HighScoreButton);
    window.draw(loadButton);
    window.draw(exitButton);

    window.draw(title);
    window.draw(playText);
    window.draw(settingText);
    window.draw(HighScoreText);
    window.draw(loadText);
    window.draw(quitText);
}

#endif
