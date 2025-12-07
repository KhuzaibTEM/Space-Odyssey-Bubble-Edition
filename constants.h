#ifndef CONSTANTS_H
#define CONSTANTS_H


const int WIDTH = 1280;
const int HEIGHT = 720;
const int MAX_ROWS = 20;
const int MAX_COLS = 20;

const float pi = 3.14159f;

const int GameFontSize = 20;

const float defaultMusicVolume = 30.f;
const float defaultSfxVolume = 80.f;

const int ButtonX = 500;
const int ButtonPlayY = 200; 
const int ButtonSettingY = 320; 
const int ButtonSaveY = 430; 
const int ButtonExitY = 540;

const int ButtonHighScoreX = 950;
const int ButtonHighScoreY = 610;

const int HighScoreDispX = ButtonX;

const int BackToMenuButtonX = 100;
const int BackToMenuButtonY = ButtonHighScoreY;

const int pauseX = WIDTH - 60;
const int pauseY = HEIGHT - 60;
const int pauseW = 40;
const int pauseH = 40;

const int ButtonBackX = 370;
const int ButtonBackY = 70;

const int buttonWidth = 300;
const int buttonHeight = 80;

const float WIDTH_BUTTON_IN_G_MENU = 40.f;
const float HEIGHT_BUTTON_IN_G_MENU = 40.f;
const float X_BUTTON_IN_G_MENU = WIDTH - 60.f;
const float Y_BUTTON_IN_G_MENU = HEIGHT - 60.f;

const float settingsToggleRadius = 18.f;

const float settingsClickCooldown = 0.25f;

const float desiredBallDiameter = 20.f;
const float originalFrameSize = 64.f;   // each bubble tile is 64x64
const float ballScaleFactor = desiredBallDiameter / originalFrameSize;


#endif
