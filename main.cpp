#include <ctime>
#include "Bubbles.h"
#include "Calculations.h"
#include "CollisionAction.h"
#include "MainMenu.h"
#include "InGameMenu.h"
#include "SavingGame.h"
#include "settings.h"
#include "HighScore.h"
#include "SFML/Audio.hpp"

int main() {

    srand(time(NULL));
    
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Space Odyssey: Bubble Edition");
    

    // 0 = Main Menu
    // 1 = Play Game
    // 2 = Exit
    // 3 = In Game Menu
    // 4 = Settings
    // 5 = View High Score
    int gameState = 0;
    int prevGameState = 0;

    //Load Sound & Music
    sf::SoundBuffer CollisionBuffer;
    CollisionBuffer.loadFromFile("./Sounds/hitSound.ogg");
    sf::Sound CollisionSound;
    CollisionSound.setBuffer(CollisionBuffer);

    sf::SoundBuffer shootBuffer;
    shootBuffer.loadFromFile("./Sounds/shoot.ogg");
    sf::Sound shootSound;
    shootSound.setBuffer(shootBuffer);

    sf::Music BgMusic;
    BgMusic.openFromFile("./Sounds/SpaceTheme.ogg");
    BgMusic.setVolume(defaultMusicVolume);
    BgMusic.setLoop(true);
    BgMusic.play();
    shootSound.setVolume(defaultSfxVolume);
    CollisionSound.setVolume(defaultSfxVolume);


    //Load Fonts
    sf::Font ScoreFont;
    ScoreFont.loadFromFile("./Fonts/ArcadeClassic.ttf");
    

    int score = 0;
    sf::Text mainText("Score " + IntegerToString(score), ScoreFont, GameFontSize);
    mainText.setPosition(50, 680);
    
    sf::Font menuFont;
    menuFont.loadFromFile("./Fonts/Blox2.ttf");


    //Loading the Sprites, Background & Texture

    sf::Texture plane;
    plane.loadFromFile("./Sprites/plane/Plane.png");

    sf::Sprite plane_sprite(plane);

    sf::Texture BackGround;
    BackGround.loadFromFile("./Background/Background.png");

    sf::Sprite bg(BackGround);

    sf::Texture Bubbles;
    Bubbles.loadFromFile("./Sprites/Bubbles/Bubbles.png");

    sf::Sprite BubbleSpriteTop(Bubbles);

    // Ball as a sprite
    sf::Sprite BallToShoot(Bubbles);
    
    BallToShoot.setScale(ballScaleFactor, ballScaleFactor);
    // origin at center of the 64x64 frame
    BallToShoot.setOrigin(originalFrameSize / 2.f, originalFrameSize / 2.f);

    // We'll keep a "current color index" that represents the next shot
    int nextBallColorIndex = rand() % 4;
    // Pre-set the BallToShoot textureRect to nextBallColorIndex (so the preview shows it)
    BallToShoot.setTextureRect(sf::IntRect(nextBallColorIndex * 64, 0, 64, 64));

    // Handling Error via Clock of clicking menu leading to a pre shoot of a bubble
    sf::Clock clockMenuError;

    // Handling error for settings circle click registering multiple times
    sf::Clock settingsClickClock;
    

    //Animation Logic for Sprite --> Plane (Since plane is 48x48 size, you can see the division of 48)
    sf::IntRect first_frame(0, 0, 48, 48);
    sf::IntRect second_frame(48, 0, 48, 48);
    sf::IntRect third_frame(96, 0, 48, 48);
    sf::IntRect fourth_frame(144, 0, 48, 48);
    
    sf::Clock clock;
    
    float animationLoopSpeed = 0.1f;
    int FrameNow = 0;
    sf::IntRect arrayFrames[] = {first_frame, second_frame, third_frame, fourth_frame};



    //Setting attributes to the Sprites & Shapes
    plane_sprite.setPosition(630.f, 550.f);
    plane_sprite.setScale(4.f,4.f);

    bg.setScale(2.f,2.f);

    // Set the sprite's origin to its center for proper rotation
    plane_sprite.setOrigin(plane_sprite.getLocalBounds().width / 8, plane_sprite.getLocalBounds().height / 8);

    bool MenuErrorNextShoot = false;
    bool musicMuted = false;
    bool sfxMuted = false;
    int shotsWithoutClear = 0;

    // Track if the ball is moving
    bool ballActive = false; 

    // Velocity of the ball
    sf::Vector2f BallVelocity(0.f, 0.f);

    
    sf::Sprite bubbleGrid[MAX_ROWS][MAX_COLS];
    bool occupied[MAX_ROWS][MAX_COLS];
    int currentRowCount = 3; // Initial No. of Rows of Bubbles

    GridMaker(bubbleGrid, occupied, BubbleSpriteTop);

    //Main Loop
    while (window.isOpen()) {
        sf::Event event;
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }
        if (gameState == 0) {
            if (event.type == sf::Event::MouseButtonPressed) {

                // Play Button
                if (mousePos.x >= ButtonX && mousePos.x <= ButtonX + buttonWidth &&
                    mousePos.y >= ButtonPlayY && mousePos.y <= ButtonPlayY + buttonHeight) {
                    prevGameState = gameState;
                    gameState = 1;
                    MenuErrorNextShoot = true;
                    clockMenuError.restart();
                }

                // Setting Button
                if (mousePos.x >= ButtonX && mousePos.x <= ButtonX + buttonWidth &&
                    mousePos.y >= ButtonSettingY && mousePos.y <= ButtonSettingY + buttonHeight) {
                    prevGameState = gameState;
                    gameState = 4;
                }

                // View Highscore Button
                else if (mousePos.x >= ButtonHighScoreX && mousePos.x <= ButtonHighScoreX + buttonWidth &&
                    mousePos.y >= ButtonHighScoreY && mousePos.y <= ButtonHighScoreY + buttonHeight) {
                    prevGameState = gameState;
                    gameState = 5;
                }

                // Load Button
                if (mousePos.x >= ButtonX && mousePos.x <= ButtonX + buttonWidth &&
                    mousePos.y >= ButtonSaveY && mousePos.y <= ButtonSaveY + buttonHeight) {

                    if (loadGame("SaveFile.txt", bubbleGrid, occupied, score, currentRowCount, Bubbles)) {
                        std::cout << "Loaded SaveFile.txt" << std::endl;
                        prevGameState = gameState;
                        gameState = 1;
                        MenuErrorNextShoot = true;
                        clockMenuError.restart();
                    } 
                    else std::cout << "No savefile found or failed to load" << std::endl;
                }

                // Exit Button
                if (mousePos.x >= ButtonX && mousePos.x <= ButtonX + buttonWidth &&
                    mousePos.y >= ButtonExitY && mousePos.y <= ButtonExitY + buttonHeight) {
                    prevGameState = gameState;
                    gameState = 2;
                }
            }
        }


        window.clear();
        window.draw(bg);

        
        if (gameState == 0) {
            drawMainMenu(window, menuFont);
        }
        else if (gameState == 1) {
            // Draw pause button during gameplay
            drawPauseButton(window);

            // Get mouse position relative to the window
            sf::Vector2f planePos = plane_sprite.getPosition();

            // Handle pause button click (prevent immediate shooting)
            if (event.type == sf::Event::MouseButtonPressed &&
                mousePos.x >= pauseX && mousePos.x <= pauseX + pauseW &&
                mousePos.y >= pauseY && mousePos.y <= pauseY + pauseH) {
                prevGameState = gameState;
                gameState = 3;
                MenuErrorNextShoot = true;
                clockMenuError.restart();
            }

            float angle = FindAngle(mousePos, planePos);

            //std::cout << angle << std::endl;
            plane_sprite.setRotation(angle + 90); // 90 degree added for adjustment of sprite

            if (event.type == sf::Event::MouseButtonPressed && !ballActive && !MenuErrorNextShoot) {
                if (!sfxMuted) shootSound.play();
                ballActive = true;

                // Set the ball's initial velocity based on the angle
                float speed = 0.5f; // Speed of Ball

                BallToShoot.setPosition(planePos.x, planePos.y); // Start from the sprite's position

                // Use the nextBallColorIndex for this shot
                BallToShoot.setTextureRect(sf::IntRect(nextBallColorIndex * 64, 0, 64, 64));

                // Prepare the following shot's color immediately
                nextBallColorIndex = rand() % 4;

                BallVelocity.x = std::cos(DegreeToRadian(angle)) * speed;
                BallVelocity.y = std::sin(DegreeToRadian(angle)) * speed;
            }
            else if (event.type == sf::Event::MouseButtonPressed && MenuErrorNextShoot && clockMenuError.getElapsedTime().asSeconds() > 0.25) MenuErrorNextShoot = false;

            bool shotResolvedThisFrame = false;
            bool clearedClusterThisShot = false;

            // Update ball position if active
            if (ballActive) {
                sf::Vector2f position = BallToShoot.getPosition();
                BallToShoot.setPosition(position.x + BallVelocity.x, position.y + BallVelocity.y);

                // Check if the ball is off-screen
                if (position.x < 0 || position.x > window.getSize().x || position.y > window.getSize().y) {
                    ballActive = false;
                }

                // Collision detection & Action
                bool placed = false;
                for (int row = 0; row < currentRowCount && !placed; row++) {
                    for (int col = 0; col < MAX_COLS && !placed; col++) {
                        if (!occupied[row][col]) continue;
                        if (BallToShoot.getGlobalBounds().intersects(bubbleGrid[row][col].getGlobalBounds())) {
                            bool cleared = false;
                            if (placeNearestNeighborAndHandle(row, col, BallToShoot, BubbleSpriteTop, bubbleGrid, occupied, currentRowCount, ballActive, placed, score, CollisionSound, cleared)) {
                                clearedClusterThisShot = clearedClusterThisShot || cleared;
                                shotResolvedThisFrame = true;
                                break;
                            }
                            bool fallbackCleared = false;
                            if (fallbackColumnPlace(col, BallToShoot, BubbleSpriteTop, bubbleGrid, occupied, currentRowCount, ballActive, placed, score, CollisionSound, fallbackCleared)) {
                                clearedClusterThisShot = clearedClusterThisShot || fallbackCleared;
                                shotResolvedThisFrame = true;
                                break;
                            }
                        }
                    }
                }

                if (!placed && position.y <= 0.f) {
                    bool topCleared = false;
                    if (placeAtTopIfReached(position, BallToShoot, BubbleSpriteTop, bubbleGrid, occupied, currentRowCount, ballActive, score, CollisionSound, topCleared)) {
                        clearedClusterThisShot = clearedClusterThisShot || topCleared;
                        shotResolvedThisFrame = true;
                    }
                }
            }

            if (!ballActive && shotResolvedThisFrame) {
                if (clearedClusterThisShot) {
                    shotsWithoutClear = 0;
                } else {
                    shotsWithoutClear++;
                    if (shotsWithoutClear >= 5) {
                        pushNewRow(bubbleGrid, occupied, BubbleSpriteTop, currentRowCount);
                        shotsWithoutClear = 0;
                    }
                }
            }

            if (clock.getElapsedTime().asSeconds() > animationLoopSpeed) {
                FrameNow = (FrameNow + 1) % 4;
                plane_sprite.setTextureRect(arrayFrames[FrameNow]);
                clock.restart();
            }
            if (ballActive) window.draw(BallToShoot);
            else {
                // preview sprite to show the next bubble that will be shot
                sf::Sprite preview(Bubbles);
                preview.setTextureRect(sf::IntRect(nextBallColorIndex * 64, 0, 64, 64));
                preview.setScale(ballScaleFactor, ballScaleFactor);
                preview.setOrigin(originalFrameSize / 2.f, originalFrameSize / 2.f);

                // position it slightly in front of the plane so user can see it
                sf::Vector2f previewPos = plane_sprite.getPosition();
                previewPos.y -= 30.f; // offset upward a bit
                preview.setPosition(previewPos);
                window.draw(preview);
            }

            // Draw the bubbles (draw only occupied cells)
            for (int row = 0; row < currentRowCount; row++) {
                for (int col = 0; col < MAX_COLS; col++) {
                    if (occupied[row][col]) window.draw(bubbleGrid[row][col]);
                }
            }
            window.draw(plane_sprite);

            // Update score display each frame
            mainText.setString("Score " + IntegerToString(score));
            window.draw(mainText);
            
            if (currentRowCount > 8) window.close();
            else if (currentRowCount == 0) {
                newHighScore(score);
                window.close();
            }
        }
        else if (gameState == 2) window.close();

        // Paused state: draw in game menu and handle its clicks
        else if (gameState == 3) {

            drawInGameMenu(window, menuFont);

            // Handle clicks while paused
            if (event.type == sf::Event::MouseButtonPressed) {

                // Resume
                if (mousePos.x >= ButtonX - buttonWidth && mousePos.x <= ButtonX &&
                    mousePos.y >= ButtonPlayY && mousePos.y <= ButtonPlayY + buttonHeight) {
                    prevGameState = gameState;
                    gameState = 1;
                    MenuErrorNextShoot = true;
                    clockMenuError.restart();
                }

                // Settings
                else if (mousePos.x >= ButtonX - buttonWidth && mousePos.x <= ButtonX &&
                    mousePos.y >= ButtonSettingY && mousePos.y <= ButtonSettingY + buttonHeight) {
                    prevGameState = gameState;
                    gameState = 4;
                }

                // Save
                else if (mousePos.x >= ButtonX - buttonWidth && mousePos.x <= ButtonX &&
                    mousePos.y >= ButtonSaveY && mousePos.y <= ButtonSaveY + buttonHeight) {
                    if (saveGame("SaveFile.txt", bubbleGrid, occupied, score, currentRowCount)) {
                        std::cout << "Game saved to SaveFile.txt" << std::endl;
                    } 
                    else std::cout << "Failed to save game" << std::endl;
                }

                // Quit to main menu
                else if (mousePos.x >= ButtonX - buttonWidth && mousePos.x <= ButtonX &&
                    mousePos.y >= ButtonExitY && mousePos.y <= ButtonExitY + buttonHeight) {
                    
                    prevGameState = gameState;
                    gameState = 0;
                }
            }
        }

        // View settings
        else if (gameState == 4) {
            drawSettings(window, menuFont, musicMuted, sfxMuted);

            if (event.type == sf::Event::MouseButtonPressed) {
                bool allowToggle = settingsClickClock.getElapsedTime().asSeconds() >= settingsClickCooldown;
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                if (mousePos.x >= ButtonBackX - buttonWidth && mousePos.x <= ButtonBackX &&
                    mousePos.y >= ButtonBackY && mousePos.y <= ButtonBackY + buttonHeight) {
                    gameState = prevGameState;
                }
                else if (allowToggle && musicToggleBounds().contains(mousePosF)) {
                    musicMuted = !musicMuted;
                    BgMusic.setVolume(musicMuted ? 0.f : defaultMusicVolume);
                    settingsClickClock.restart();
                }
                else if (allowToggle && sfxToggleBounds().contains(mousePosF)) {
                    sfxMuted = !sfxMuted;
                    float newVolume = sfxMuted ? 0.f : defaultSfxVolume;
                    shootSound.setVolume(newVolume);
                    CollisionSound.setVolume(newVolume);
                    settingsClickClock.restart();
                }
            }
        }

        // Viewing Highscores
        else if (gameState == 5) {
            drawHighScore(window, ScoreFont, menuFont);
            if (event.type == sf::Event::MouseButtonPressed) {
                if (mousePos.x >= BackToMenuButtonX && mousePos.x <= BackToMenuButtonX + buttonWidth &&
                    mousePos.y >= BackToMenuButtonY && mousePos.y <= BackToMenuButtonY + buttonHeight) {
                    prevGameState = gameState;
                    gameState = 0;
                }
            }   
        }
        window.display();
    }
}
