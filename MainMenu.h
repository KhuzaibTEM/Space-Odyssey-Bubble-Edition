#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.h"

void drawMainMenu(sf::RenderWindow &window, sf::Font &font) {

    sf::RectangleShape playButton;
    playButton.setSize(sf::Vector2f(300, 80));
    playButton.setPosition(ButtonX, ButtonPlayY);
    playButton.setFillColor(sf::Color(30,30,30,200));
    playButton.setOutlineColor(sf::Color::Blue);
    playButton.setOutlineThickness(3.f);

    sf::RectangleShape saveButton;
    saveButton.setSize(sf::Vector2f(300, 80));
    saveButton.setPosition(ButtonX, ButtonSaveY);
    saveButton.setFillColor(sf::Color(30,30,30,200));
    saveButton.setOutlineColor(sf::Color::Yellow);
    saveButton.setOutlineThickness(3.f);

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

    sf::Text saveText("Save", font, 30);
    saveText.setPosition(615, 345);
    saveText.setFillColor(sf::Color::White);

    sf::Text quitText("Quit", font, 30);
    quitText.setPosition(615, 455);
    quitText.setFillColor(sf::Color::White);

    // Draw buttons and labels (each once)
    window.draw(playButton);
    window.draw(saveButton);
    window.draw(exitButton);

    window.draw(title);
    window.draw(playText);
    window.draw(saveText);
    window.draw(quitText);
}

#endif