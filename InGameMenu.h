#ifndef INGAMEMENU_H
#define INGAMEMENU_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.h"

void drawPauseButton(sf::RenderWindow &window);
void drawInGameMenu(sf::RenderWindow &window, sf::Font &font);

// Draw a small pause icon (two vertical bars) at top-right corner
void drawPauseButton(sf::RenderWindow &window) {

	sf::RectangleShape bg(sf::Vector2f(WIDTH_BUTTON_IN_G_MENU, HEIGHT_BUTTON_IN_G_MENU));
	bg.setPosition(X_BUTTON_IN_G_MENU, Y_BUTTON_IN_G_MENU);
	bg.setFillColor(sf::Color(0, 0, 0, 150));
	bg.setOutlineColor(sf::Color::White);
	bg.setOutlineThickness(2.f);
	window.draw(bg);

	// two bars
	sf::RectangleShape bar1(sf::Vector2f(8.f, 24.f));
	bar1.setPosition(X_BUTTON_IN_G_MENU + 8.f, Y_BUTTON_IN_G_MENU + 8.f);
	bar1.setFillColor(sf::Color::White);
	window.draw(bar1);

	sf::RectangleShape bar2(sf::Vector2f(8.f, 24.f));
	bar2.setPosition(X_BUTTON_IN_G_MENU + 24.f, Y_BUTTON_IN_G_MENU + 8.f);
	bar2.setFillColor(sf::Color::White);
	window.draw(bar2);
}

// Draw the in-game pause menu with buttons: Resume, Save, Settings, Quit
void drawInGameMenu(sf::RenderWindow &window, sf::Font &font) {
	// semi-transparent overlay
	sf::RectangleShape overlay(sf::Vector2f((float)WIDTH, (float)HEIGHT));
	overlay.setFillColor(sf::Color(0, 0, 0, 140));
	window.draw(overlay);

	// Draw menu buttons using the same constants as main menu
	sf::RectangleShape playButton(sf::Vector2f((float)buttonWidth, (float)buttonHeight));
	playButton.setPosition((float)(ButtonX - buttonWidth), (float)ButtonPlayY);
	playButton.setFillColor(sf::Color(50,50,50,220));
	playButton.setOutlineColor(sf::Color::White);
	playButton.setOutlineThickness(2.f);
	window.draw(playButton);

	sf::RectangleShape settingButton(sf::Vector2f((float)buttonWidth, (float)buttonHeight));
	settingButton.setPosition((float)(ButtonX - buttonWidth), (float)ButtonSettingY);
	settingButton.setFillColor(sf::Color(50,50,50,220));
	settingButton.setOutlineColor(sf::Color::White);
	settingButton.setOutlineThickness(2.f);
	window.draw(settingButton);

	sf::RectangleShape saveButton(sf::Vector2f((float)buttonWidth, (float)buttonHeight));
	saveButton.setPosition((float)(ButtonX - buttonWidth), (float)ButtonSaveY);
	saveButton.setFillColor(sf::Color(50,50,50,220));
	saveButton.setOutlineColor(sf::Color::White);
	saveButton.setOutlineThickness(2.f);
	window.draw(saveButton);

	sf::RectangleShape exitButton(sf::Vector2f((float)buttonWidth, (float)buttonHeight));
	exitButton.setPosition((float)(ButtonX - buttonWidth), (float)ButtonExitY);
	exitButton.setFillColor(sf::Color(50,50,50,220));
	exitButton.setOutlineColor(sf::Color::White);
	exitButton.setOutlineThickness(2.f);
	window.draw(exitButton);

	// Text labels
	sf::Text title("Paused", font, 48);
	title.setFillColor(sf::Color::White);
	title.setPosition((float)(WIDTH/2 - 80), 80.f);
	window.draw(title);

	sf::Text resumeText("Resume", font, 28);
	resumeText.setFillColor(sf::Color::White);
	resumeText.setPosition((float)(ButtonX - buttonWidth + 20), (float)(ButtonPlayY + 16));
	window.draw(resumeText);

	sf::Text settingText("Settings", font, 28);
	settingText.setFillColor(sf::Color::White);
	settingText.setPosition((float)(ButtonX - buttonWidth + 20), (float)(ButtonSettingY + 16));
	window.draw(settingText);

	sf::Text saveText("Save", font, 28);
	saveText.setFillColor(sf::Color::White);
	saveText.setPosition((float)(ButtonX - buttonWidth + 20), (float)(ButtonSaveY + 16));
	window.draw(saveText);

	sf::Text backMenuText("Menu", font, 28);
	backMenuText.setFillColor(sf::Color::White);
	backMenuText.setPosition((float)(ButtonX - buttonWidth + 20), (float)(ButtonExitY + 16));
	window.draw(backMenuText);
}

#endif