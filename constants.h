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
const int ButtonSaveY = 320; 
const int ButtonExitY = 430;

const int buttonWidth = 300;
const int buttonHeight = 80;

const float desiredBallDiameter = 20.f;
const float originalFrameSize = 64.f;   // each bubble tile is 64x64
const float ballScaleFactor = desiredBallDiameter / originalFrameSize;


#endif
