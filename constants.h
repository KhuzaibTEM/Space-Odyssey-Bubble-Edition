#ifndef CONSTANTS_H
#define CONSTANTS_H

const int WIDTH = 1280;
const int HEIGHT = 720;
const int MAX_ROWS = 20;
const int MAX_COLS = 20;

const float pi = 3.14159f;

const float desiredBallDiameter = 20.f;
const float originalFrameSize = 64.f;   // each bubble tile is 64x64
const float ballScaleFactor = desiredBallDiameter / originalFrameSize;


#endif