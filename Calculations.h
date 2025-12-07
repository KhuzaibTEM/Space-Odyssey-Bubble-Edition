#ifndef ANGLECALC_H
#define ANGLECALC_H

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "constants.h"

float FindAngle(sf::Vector2i mousePos, sf::Vector2f spritePos);
float RadianToDegree(float Number);
float DegreeToRadian(float Number);
float rounding(float Number);
std::string IntegerToString(int num);

float FindAngle(sf::Vector2i mousePos, sf::Vector2f spritePos) {
    // Calculate the angle between the sprite and the mouse cursor
    float dx = mousePos.x - spritePos.x;
    float dy = mousePos.y - spritePos.y;
    float angle = RadianToDegree(std::atan2(dy, dx));

    // Since We don't want the plane to be moving all 360 or 180 but rather in an obtuse angle
    if (angle > -150 && angle < -30) return angle;
    else if (angle < 150 && angle > 30) return -angle;
    else if (angle < -150 || angle > 150) return -150;
    else if (angle > - 30 && angle < 30) return -30;
    return angle;
}

float RadianToDegree(float Num) {
    return (Num * 180 / pi);
}
float DegreeToRadian(float Num) {
    return (Num * pi / 180);
}

float rounding(float num) {
    if (num - static_cast<int>(num) >= 0.5) return static_cast<int>(num) + 1;
    else return static_cast<int>(num);
}

std::string IntegerToString(int num) {
    std::string ans = "";
    int size10 = 1;
    int temp = num;
    int size = 0;
    while (temp > 0) {
        size10 *= 10;
        temp /= 10;
        size++;
    }
    size10 /= 10;
    for (int i = 0; i < size; i++) {
        ans += static_cast<char>(num/size10 + 48);
        num %= size10;
        size10 /= 10;
    }
    return ans;
}

#endif
