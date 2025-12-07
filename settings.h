#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "constants.h"

sf::FloatRect sfxToggleBounds();
sf::FloatRect musicToggleBounds();
void drawSettings(sf::RenderWindow &window, sf::Font &font, bool musicMuted, bool sfxMuted);

sf::FloatRect musicToggleBounds() {
    sf::Vector2f musicToggleCenter = sf::Vector2f(880.f, 255.f);
	return sf::FloatRect(musicToggleCenter.x - settingsToggleRadius, musicToggleCenter.y - settingsToggleRadius, settingsToggleRadius * 2.f, settingsToggleRadius * 2.f);
}

sf::FloatRect sfxToggleBounds() {
    sf::Vector2f sfxToggleCenter = sf::Vector2f(880.f, 345.f);
	return sf::FloatRect(sfxToggleCenter.x - settingsToggleRadius, sfxToggleCenter.y - settingsToggleRadius, settingsToggleRadius * 2.f, settingsToggleRadius * 2.f);
}

void drawToggleRow(sf::RenderWindow &window, sf::Font &font, const std::string &label, const sf::Vector2f &textPos, const sf::Vector2f &circleCenter, bool enabled) {
	sf::Text text(label, font, 32);
	text.setFillColor(sf::Color::White);
	text.setPosition(textPos);
	window.draw(text);

	float radius = 18.f;
	sf::CircleShape circle(radius);
	circle.setPosition(circleCenter.x - radius, circleCenter.y - radius);
	circle.setFillColor(enabled ? sf::Color::White : sf::Color::Transparent);
	circle.setOutlineColor(sf::Color::White);
	circle.setOutlineThickness(3.f);
	window.draw(circle);
}

void drawSettings(sf::RenderWindow &window, sf::Font &font, bool musicMuted, bool sfxMuted) {
	sf::RectangleShape settingOverlay(sf::Vector2f(WIDTH, HEIGHT));
	settingOverlay.setFillColor(sf::Color(0, 0, 0, 140));
	window.draw(settingOverlay);

	sf::RectangleShape backButton(sf::Vector2f(buttonWidth, buttonHeight));
	backButton.setPosition((ButtonBackX - buttonWidth), ButtonBackY);
	backButton.setFillColor(sf::Color(50,50,50,220));
	backButton.setOutlineColor(sf::Color::White);
	backButton.setOutlineThickness(2.f);
	window.draw(backButton);

	//Text labels
	sf::Text settingsTitle("Settings", font, 48);
	settingsTitle.setFillColor(sf::Color::White);
	settingsTitle.setPosition((WIDTH/2 - 80), 80.f);
	window.draw(settingsTitle);

	sf::Text backMenuText("Back", font, 28);
	backMenuText.setFillColor(sf::Color::White);
	backMenuText.setPosition((ButtonBackX - buttonWidth + 20), (ButtonBackY + 16));
	window.draw(backMenuText);

	drawToggleRow(window, font, "Mute Background Music", sf::Vector2f(240.f, 225.f), sf::Vector2f(880.f, 255.f), musicMuted);
	drawToggleRow(window, font, "Mute Sound Effects", sf::Vector2f(240.f, 315.f), sf::Vector2f(880.f, 345.f), sfxMuted);
}

#endif
