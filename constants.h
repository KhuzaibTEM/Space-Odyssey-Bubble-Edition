#ifndef CONSTANTS_H
#define CONSTANTS_H

const int WIDTH = 1280;
const int HEIGHT = 720;
const int MAX_ROWS = 20;
const int MAX_COLS = 20;

const float pi = 3.14159f;

const int GameFontSize = 20;

const int ButtonX = 500;
const int ButtonPlayY = 200; 
const int ButtonSettingY = 320; 
const int ButtonSaveY = 430; 
const int ButtonExitY = 540;

const int buttonWidth = 300;
const int buttonHeight = 80;

const float WIDTH_BUTTON_IN_G_MENU = 40.f;
const float HEIGHT_BUTTON_IN_G_MENU = 40.f;
const float X_BUTTON_IN_G_MENU = WIDTH - 60.f;
const float Y_BUTTON_IN_G_MENU = HEIGHT - 60.f;

const float desiredBallDiameter = 20.f;
const float originalFrameSize = 64.f;   // each bubble tile is 64x64
const float ballScaleFactor = desiredBallDiameter / originalFrameSize;


#endif
