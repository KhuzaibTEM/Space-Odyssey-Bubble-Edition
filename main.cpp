#include <ctime>
#include "Bubbles.h"
#include "AngleCalc.h"
#include "CollisionAction.h"
#include "MainMenu.h"
#include "InGameMenu.h"

int main() {

    srand(time(NULL));
    
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Space Odyssey: Bubble Edition");
    

    // 0 = Main Menu
    // 1 = Play Game
    // 2 = Exit
    // 3 = In Game Menu
    int gameState = 0;

    //Load Fonts
    sf::Font subFont;
    subFont.loadFromFile("./Fonts/ArcadeClassic.ttf");
    

    int score = 0;
    sf::Text mainText("Score " + std::to_string(score), subFont, GameFontSize);
    mainText.setPosition(50, 680);
    
    sf::Font menuFont;
    menuFont.loadFromFile("./Fonts/Blox2.ttf");


    //Loading the Sprites & Shapes

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

    //Animation Logic for Sprite --> Plane
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

    //Ball.setFillColor(sf::Color::White);
    // Ball.setPosition(550.f, 600.f);

    // Set the sprite's origin to its center for proper rotation
    plane_sprite.setOrigin(plane_sprite.getLocalBounds().width / 8, plane_sprite.getLocalBounds().height / 8);
    //Ball.setOrigin(plane_sprite.getLocalBounds().width / 8, plane_sprite.getLocalBounds().height / 8);

    bool MenuErrorNextShoot = false;

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
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }
        if (gameState == 0) {
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                // Play Button
                if (mousePos.x >= ButtonX && mousePos.x <= ButtonX + buttonWidth &&
                    mousePos.y >= ButtonPlayY && mousePos.y <= ButtonPlayY + buttonHeight) {
                    gameState = 1;
                    MenuErrorNextShoot = true;
                    clockMenuError.restart();
                }

                // Setting Button
                if (mousePos.x >= ButtonX && mousePos.x <= ButtonX + buttonWidth &&
                    mousePos.y >= ButtonSettingY && mousePos.y <= ButtonSettingY + buttonHeight) {
                    // Will add setting functionality later
                }

                // Load Button
                if (mousePos.x >= ButtonX && mousePos.x <= ButtonX + buttonWidth &&
                    mousePos.y >= ButtonSaveY && mousePos.y <= ButtonSaveY + buttonHeight) {
                    // Will add save functionality later
                }

                // Exit Button
                if (mousePos.x >= ButtonX && mousePos.x <= ButtonX + buttonWidth &&
                    mousePos.y >= ButtonExitY && mousePos.y <= ButtonExitY + buttonHeight) {
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
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f planePos = plane_sprite.getPosition();

            // Handle pause button click (prevent immediate shooting)
            const int pauseX = WIDTH - 60;
            const int pauseY = HEIGHT - 60;
            const int pauseW = 40;
            const int pauseH = 40;
            if (event.type == sf::Event::MouseButtonPressed &&
                mousePos.x >= pauseX && mousePos.x <= pauseX + pauseW &&
                mousePos.y >= pauseY && mousePos.y <= pauseY + pauseH) {
                // Enter paused state
                gameState = 3;
                MenuErrorNextShoot = true;
                clockMenuError.restart();
            }

            float angle = FindAngle(mousePos, planePos);

            std::cout << angle << std::endl;

            plane_sprite.setRotation(angle + 90); // 90 degree added for adjustment of sprite

            if (event.type == sf::Event::MouseButtonPressed && !ballActive && !MenuErrorNextShoot) {
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
            else if (event.type == sf::Event::MouseButtonPressed && MenuErrorNextShoot && clockMenuError.getElapsedTime().asSeconds() > 1) MenuErrorNextShoot = false;

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
                            if (placeNearestNeighborAndHandle(row, col, BallToShoot, BubbleSpriteTop, bubbleGrid, occupied, currentRowCount, ballActive, placed, score)) {
                                break;
                            }
                            if (fallbackColumnPlace(col, BallToShoot, BubbleSpriteTop, bubbleGrid, occupied, currentRowCount, ballActive, placed, score)) {
                                break;
                            }
                        }
                    }
                }

                if (!placed && position.y <= 0.f) {
                    placeAtTopIfReached(position, BallToShoot, BubbleSpriteTop, bubbleGrid, occupied, currentRowCount, ballActive, score);
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
            mainText.setString("Score " + std::to_string(score));
            window.draw(mainText);
            
            if (currentRowCount > 8) window.close();
            else if (currentRowCount == 0) window.close();
        }
        else if (gameState == 2) window.close();

        // Paused state: draw menu and handle its clicks
        else if (gameState == 3) {

            drawInGameMenu(window, menuFont);

            // Handle clicks while paused
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                // Resume
                if (mousePos.x >= ButtonX - buttonWidth && mousePos.x <= ButtonX &&
                    mousePos.y >= ButtonPlayY && mousePos.y <= ButtonPlayY + buttonHeight) {
                    gameState = 1;
                    MenuErrorNextShoot = true;
                    clockMenuError.restart();
                }

                // Settings (toggle settings panel)
                else if (mousePos.x >= ButtonX - buttonWidth && mousePos.x <= ButtonX &&
                    mousePos.y >= ButtonSettingY && mousePos.y <= ButtonSettingY + buttonHeight) {
                    // To be added
                }

                // Save (write a simple save file)
                else if (mousePos.x >= ButtonX - buttonWidth && mousePos.x <= ButtonX &&
                    mousePos.y >= ButtonSaveY && mousePos.y <= ButtonSaveY + buttonHeight) {
                    // To be written
                }

                // Quit to main menu
                else if (mousePos.x >= ButtonX - buttonWidth && mousePos.x <= ButtonX &&
                    mousePos.y >= ButtonExitY && mousePos.y <= ButtonExitY + buttonHeight) {
                    gameState = 0;
                }
            }
        }
        window.display();
    }
}
