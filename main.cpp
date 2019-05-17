#include "Character.h"
#include "Curve.h"
#include "Obstacle.h"
#include "ImprovedPerlinNoise.h"
#include "Collision.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdlib.h>
#include <iostream>

int highScore = 0;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 500), "CHAY DI!!!");
    window.setFramerateLimit(60);

    sf::Texture background_t;
    background_t.loadFromFile("background.png");
    sf::Sprite background_s;
    background_s.setTexture(background_t);
    background_s.setPosition(-30.f, 0.f);

    sf::Texture gmovrM_t;
    gmovrM_t.loadFromFile("gmovr_menu.png");
    sf::Sprite gmovrM_s;
    gmovrM_s.setTexture(gmovrM_t);
    int gmovrMAlpha = 0;

    sf::Texture mainM_t;
    mainM_t.loadFromFile("main_menu.png");
    sf::Sprite mainM_s;
    mainM_s.setTexture(mainM_t);

    sf::SoundBuffer tapBuffer;
    tapBuffer.loadFromFile("tap.wav");
    sf::Sound tap;
    tap.setBuffer(tapBuffer);
    tap.setVolume(20.f);

    sf::SoundBuffer vutBuffer;
    vutBuffer.loadFromFile("vutt.wav");
    sf::Sound vut;
    vut.setBuffer(vutBuffer);
    vut.setVolume(20.f);

    sf::SoundBuffer bettBuffer;
    bettBuffer.loadFromFile("dung.wav");
    sf::Sound bett;
    bett.setBuffer(bettBuffer);
    //bett.setVolume(20.f);

    sf::SoundBuffer itsBuffer;
    itsBuffer.loadFromFile("ichs.wav");
    sf::Sound its;
    its.setBuffer(itsBuffer);
    //its.setVolume(20.f);

    sf::SoundBuffer xengBuffer;
    xengBuffer.loadFromFile("xengg.wav");
    sf::Sound xeng;
    xeng.setBuffer(xengBuffer);
    xeng.setVolume(50.f);

    sf::SoundBuffer heheheBuffer;
    heheheBuffer.loadFromFile("he he he.wav");
    sf::Sound hehehe;
    hehehe.setBuffer(heheheBuffer);
    hehehe.setPitch(0.5);

    sf::SoundBuffer uaBuffer;
    uaBuffer.loadFromFile("udiedmotherfuka.wav");
    sf::Sound uaaa;
    uaaa.setBuffer(uaBuffer);
    uaaa.setVolume(40.f);
    //uaaa.play();

    sf::Music startMusic;
    startMusic.openFromFile("start sound.wav");
    startMusic.play();
    startMusic.setLoop(true);

    sf::Music playMusic;
    playMusic.openFromFile("play sound.wav");
    playMusic.setVolume(30.f);

    sf::Font font;
    if (!font.loadFromFile("Something Strange.ttf")) {
        std::cout << "Cannot open font\n";
        return 1;
    }

    sf::Text scoreText("", font, 25);
    scoreText.setPosition(282.f, 269.f);

    sf::Text highScoreText("", font, 25);
    highScoreText.setPosition(546.f, 269.f);

    sf::Texture instruction_t;
    instruction_t.loadFromFile("instruction.png");
    sf::Sprite instruction_s;
    instruction_s.setTexture(instruction_t);
    int alpha = 0, i = 0;

    sf::Texture instruction1_t;
    instruction1_t.loadFromFile("instruction1.png");
    sf::Sprite instruction1_s;
    instruction1_s.setTexture(instruction1_t);
    int insAlpha = 0;

    sf::Texture youReady_t;
    youReady_t.loadFromFile("youReady.png");
    sf::Sprite youReady_s;
    youReady_s.setTexture(youReady_t);
    int readyAlpha = 0;

    ////OBSTACLE
    sf::Vector2f position, positionNext;

    sf::Texture tree;
    tree.loadFromFile("obstacle1.png");
    sf::Sprite obs1;
    obs1.setTexture(tree);

    sf::Texture shit;
    shit.loadFromFile("obstacle2.png");
    sf::Sprite obs2;
    obs2.setTexture(shit);

    sf::Texture rock;
    rock.loadFromFile("obstacle3.png");
    sf::Sprite obs3;
    obs3.setTexture(rock);

    sf::Texture darkness_t;
    darkness_t.loadFromFile("darkness.png");
    sf::Sprite darkness_s;
    darkness_s.setTexture(darkness_t);
    darkness_s.setPosition(-1800.f, -500.f);


    //initialize properties for the curve
    ImprovedPerlinNoise noiseGen;
    auto yGen = [&](float x) {
        const float xScale      = 2e-3f;
        const float yMagnitude1 = 20;
        const float yMagnitude2 = 130;
        const float yMagnitude3 = 60;
        const float yMagnitude4 = 50;

        const float xScaled =  x * xScale;
        return float(yMagnitude1 * noiseGen.noise(xScaled * 0) +
                     yMagnitude2 * noiseGen.noise(xScaled * 1) +
                     yMagnitude3 * noiseGen.noise(xScaled * 0.8) +
                     yMagnitude4 * noiseGen.noise(xScaled * 1));
    };
    Curve curve(1.f, window.getSize().x, yGen);


    ////INITIALIZE CHARACTER
    sf::Texture manTexture;
    manTexture.loadFromFile("character.png");
    manTexture.setSmooth(true);
    sf::Sprite man;
    man.setTexture(manTexture);
    Character character(man, curve);


    Obstacle obstacle1(obs1, position, positionNext),
             obstacle2(obs2, position, positionNext),
             obstacle3(obs3, position, positionNext);

    ////PHYSICS
    Physics physics;
    sf::View view = window.getView();
    view.setCenter(120, 0);
    curve.syncWithView(view);

    sf::Clock clock;
    sf::Clock clock1, clock2, clock3, clockPlayed, clockBefore1, clockBefore2, clockBefore3;
    sf::Time  time1,  time2,  time3,  timePlayed, timeBefore1, timeBefore2, timeBefore3;

    bool gameOver = false, collided = false, collided1End = true, collided2End = true, gameStart = false,
         startRequest = false, gameInstructing = false, gameReady = false;
    int distanceRan = 0;
    float maxSpeed = 0.f, speedLimit = 200.f;

    /*----------------------------------------------------------------------------------
                                      MAIN LOOP
    ----------------------------------------------------------------------------------*/

    while (window.isOpen()) {
        while (!gameOver) {
            sf::Event event1;
            while (window.pollEvent(event1)) {
                if (event1.type == sf::Event::Closed)
                    window.close();
                else if (event1.type == sf::Event::MouseButtonPressed || event1.type == sf::Event::KeyPressed) {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                        if (gameStart) {
                            character.up = !character.up;
                            character.sprite.scale(-1,1);
                            vut.play();
                        }
                        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                        if (localPosition.x >= 359 && localPosition.x <= 440 && localPosition.y >= 431 && localPosition.y <= 470 || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                            if (!gameInstructing) {
                                gameInstructing = true;
                                tap.play();
                            }

                            else if (!gameReady) {
                                gameReady = true;
                                tap.play();
                            }
                            else if (!gameStart) {
                                startRequest = true;
                                xeng.play();
                                startMusic.stop();
                                playMusic.play();
                            }
                        }
                    }
                }
            }


            if (startRequest && character.getMoveSpeed() > 0.f && character.getMoveSpeed() < 10.f && character.getAngle() > 0) {
                gameStart = true;
                clock1.     restart();
                clock2.     restart();
                clock3.     restart();
                clockPlayed.restart();
            }

            if (abs(character.getMoveSpeed()) < 30.f && character.getAngle() < 0)
                character.sprite.setScale(-1, 1);
            if (abs(character.getMoveSpeed()) < 30.f && character.getAngle() > 0)
                character.sprite.setScale(1,1);


            ///////MOVE CHARACTER
            sf::Time elapsed = clock.restart();
            physics.a = Physics::G * sin(character.getAngle());

            float instantVeclocity = physics.a * elapsed.asSeconds();
            if (speedLimit < 800.f)
                speedLimit += timePlayed.asSeconds() * 2;
            if (abs(character.getMoveSpeed()) > speedLimit) {
                instantVeclocity = 0;
            }

            collided = Collision::PixelPerfectTest(man, obs1) || Collision::PixelPerfectTest(man, obs2) || Collision::PixelPerfectTest(man, obs3);

            if (Collision::PixelPerfectTest(man, obs2) && collided1End) {
                bett.play();
                collided1End = false;
            }
            if ((Collision::PixelPerfectTest(man, obs1) || Collision::PixelPerfectTest(man, obs3)) && collided2End) {
                its.play();
                collided2End = false;
            }
            if (collided) {
                character.stop();
                playMusic.stop();
            }
            else {
                if (character.up == true)
                    character.addMoveSpeed(instantVeclocity);
                else
                    character.addMoveSpeed(-instantVeclocity);
            }

            if (character.getMoveSpeed() > maxSpeed)
                maxSpeed = character.getMoveSpeed();
            if (!gameStart) {
                view.setCenter(120,0);
                instruction_s.setColor(sf::Color(255, 255, 255, alpha += i));
                if (alpha >= 252) i = -3;
                if (alpha <= 90)  i =  3;
                if (character.getMoveSpeed() > 200.f) character.setMoveSpeed(200.f);
            }

            float moveAmount = 0;
            moveAmount += character.getMoveSpeed() * elapsed.asSeconds();
            if (!gameStart) distanceRan = 0;
            distanceRan += abs(moveAmount);
            int score = distanceRan/40;
            if (score > highScore) highScore = score;

            std::string unit = "distance   ";
            sf::Text distanceText{unit + std::to_string(score), font, 25};
            distanceText.setPosition(645.f, 10.f);
            distanceText.setFillColor(sf::Color::White);

            scoreText.setString(std::to_string(score) + "m");
            highScoreText.setString(std::to_string(highScore) + "m");

            view.move(character.move(moveAmount));
            curve.syncWithView(view);


            if (gameStart) {
                ////GENERATE OBSTACLES
                timePlayed = clockPlayed.getElapsedTime();
                time1 = clock1.getElapsedTime();
                timeBefore1 = clockBefore1.getElapsedTime();
                if (time1.asMilliseconds() > rand()%498+2267 && timePlayed.asSeconds() > 10 && !collided && timeBefore1.asSeconds() > 0.5) {
                    position     = {curve.getXAppend(), curve.getYAppend()};
                    positionNext = {curve.getXAppendNext(), curve.getYAppendNext()};
                    Obstacle obstacle1(obs1, position, positionNext);
                    clock1.restart();
                    clockBefore2.restart();
                    clockBefore3.restart();
                }

                time2 = clock2.getElapsedTime();
                timeBefore2 = clockBefore2.getElapsedTime();
                if (time2.asMilliseconds() > rand()%975+3040 && timePlayed.asSeconds() > 17 && !collided && timeBefore2.asSeconds() > 0.5) {
                    position     = {curve.getXAppend(), curve.getYAppend()};
                    positionNext = {curve.getXAppendNext(), curve.getYAppendNext()};
                    Obstacle obstacle2(obs2, position, positionNext);
                    clock2.restart();
                    clockBefore1.restart();
                    clockBefore3.restart();
                }

                time3 = clock3.getElapsedTime();
                timeBefore3 = clockBefore3.getElapsedTime();
                if (time3.asMilliseconds() > rand()%1000+4373 && timePlayed.asSeconds() > 27 && !collided && timeBefore3.asSeconds() > 0.5) {
                    position     = {curve.getXAppend(), curve.getYAppend()};
                    positionNext = {curve.getXAppendNext(), curve.getYAppendNext()};
                    Obstacle obstacle3(obs3, position, positionNext);
                    clock3.restart();
                    clockBefore1.restart();
                    clockBefore2.restart();
                }

                float darknessMoved = elapsed.asSeconds() * maxSpeed * 4 / 5;
                if (collided) {
                    darknessMoved = 17.f;
                }

                darkness_s.move(darknessMoved, 0.f);
                if (darkness_s.getPosition().x >= view.getCenter().x - 500.f) {
                    gameOver = true;
                    playMusic.stop();
                    hehehe.play();
                    startMusic.play();
                }
                if (darkness_s.getPosition().x <  view.getCenter().x - 2000.f)
                    darkness_s.setPosition(view.getCenter().x-2000.f, -500.f);

                float backgroundMoved = elapsed.asSeconds() * character.getMoveSpeed() / 5;
                if (gameStart) background_s.move(-backgroundMoved, 0.f);


            }

            window.clear(sf::Color(11, 51, 24));
            window.draw(background_s);

            if (!gameReady) {
                if (!gameInstructing)
                    window.draw(mainM_s);
                else {
                    if (insAlpha < 250) insAlpha += 5;
                    instruction1_s.setColor(sf::Color(255, 255, 255, insAlpha));
                    window.draw(instruction1_s);
                }
                window.draw(instruction_s);
            }
            else if (!startRequest){
                if (readyAlpha < 250) readyAlpha += 5;
                youReady_s.setColor(sf::Color(255, 255, 255, readyAlpha));
                window.draw(youReady_s);
            }

            window.setView    (view);
            window.draw       (curve);
            window.draw       (character);

            if (gameStart) {
                window.draw   (obstacle1);
                window.draw   (obstacle2);
                window.draw   (obstacle3);
                window.draw   (darkness_s);

            }
            window.setView(window.getDefaultView());

            if (startRequest) window.draw   (distanceText);
            window.display();
        }//while game is not over

        sf::Event event2;
        while (window.pollEvent(event2)) {
            if (event2.type == sf::Event::Closed)
                window.close();
            else if (event2.type == sf::Event::MouseButtonPressed || event2.type == sf::Event::KeyPressed) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) /*|| sf::Keyboard::isKeyPressed(sf::Keyboard::Space)*/) {
                    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                    std::cout << localPosition.x << "   " << localPosition.y << std::endl;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) gameOver = false;
            }
        }

        if (gmovrMAlpha < 250) gmovrMAlpha += 2;
        gmovrM_s.setColor(sf::Color(255, 255, 255, gmovrMAlpha));
        window.draw(gmovrM_s);
        window.draw(scoreText);
        window.draw(highScoreText);
        window.display();



    }//end main loop
}
