#include "Character.h"
#include "Curve.h"
#include "Obstacle.h"
#include "ImprovedPerlinNoise.h"
#include "Collision.h"
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>

//float viewX = 120, viewY = 0;o

int main() {
    //render window
    sf::RenderWindow window(sf::VideoMode(800, 500), "CHAY DI!!!");
    window.setFramerateLimit(60);

    sf::Texture gmovrM_t;
    gmovrM_t.loadFromFile("gmovr_menu.png");
    sf::Sprite gmovrM_s;
    gmovrM_s.setTexture(gmovrM_t);

    sf::Texture mainM_t;
    mainM_t.loadFromFile("main_menu.png");
    sf::Sprite mainM_s;
    mainM_s.setTexture(mainM_t);

    sf::Font font;
    if (!font.loadFromFile("MAIAN.ttf")) {
        std::cout << "Cannot open MAIAN.ttf\n";
        return 1;
    }

//    sf::Text mainM_text;
//    mainM_text.setFont(font);
//    mainM_text.setString(L"Bam phim bat ki...");
//    mainM_text.setCharacterSize(20);
//    mainM_text.setFillColor(sf::Color::Red);
//    mainM_text.setStyle(sf::Text::Bold | sf::Text::Underlined);

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
    //instruction1_s.setColor(sf::Color(255,255,255,insAlpha));

    sf::Texture youReady_t;
    youReady_t.loadFromFile("youReady.png");
    sf::Sprite youReady_s;
    youReady_s.setTexture(youReady_t);
    int readyAlpha = 0;

    //instruction_s.setPosition(200.f, 500.f);


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

    //create the in-sight curve with the properties initialized
    Curve curve(1.f, window.getSize().x, yGen);


    ////INITIALIZE CHARACTER
    sf::Texture manTexture;
    manTexture.loadFromFile("character.png");
    manTexture.setSmooth(true);
    sf::Sprite man;
    man.setTexture(manTexture);
    Character character(man, curve);


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

    Obstacle obstacle1(obs1, position, positionNext),
             obstacle2(obs2, position, positionNext),
             obstacle3(obs3, position, positionNext);

    ////PHYSICS
    Physics physics;



    sf::View view = window.getView();
    view.setCenter(120, 0);
    curve.syncWithView(view);




//    sf::Text seedText("Seed: " + std::to_string(seed), font, 1);
//    seedText.setPosition(0, 0);
//    seedText.setFillColor(sf::Color::Black);
//    sf::Text distanceText;
//    //distanceText.setPosition (0.f, 0.f);
//    distanceText.setStyle    (sf::Text::Bold);
//    distanceText.setFillColor(sf::Color::White);

   // sf::Text curvePointsText{
   //     "Curve points: " + std::to_string(curve.getPointsCount()), font, 16};
   // curvePointsText.setPosition(0, 32);
   // curvePointsText.setFillColor(sf::Color::Black);
   // sf::Text positionText{
   //     "Position: " + std::to_string(character.getPosition().x) + ", " +
   //         std::to_string(character.getPosition().y),
   //     font, 16};
   // positionText.setPosition(0, 48);
   // positionText.setFillColor(sf::Color::Black);

    sf::Clock clock;
    sf::Clock clock1, clock2, clock3, clockPlayed;
    sf::Time  time1,  time2,  time3,  timePlayed;

    /*----------------------------------------------------------------------------------
                                      MAIN LOOP
    ----------------------------------------------------------------------------------*/
    bool gameOver = false, collided = false, gameStart = false,
         startRequest = false, gameInstructing = false, gameReady = false;
    int distanceRan = 0;

    while (window.isOpen()) {
        while (!gameOver) {
            sf::Event event;
            while (window.pollEvent(event)) {
                //close the window
                if (event.type == sf::Event::Closed)
                    window.close();
                //if player presses any button
                else if (event.type == sf::Event::KeyPressed) {
                    if (!gameInstructing) {
                        gameInstructing = true;
                        std::cout << "INSTR\n";
                        //startRequest = true;
                    }
                    else if (!gameReady) {
//                        gameStart = true;
//                    distanceRan = 0;
//                    clock1.     restart();
//                    clock2.     restart();
//                    clock3.     restart();
//                    clockPlayed.restart();
                    // startRequest = true;
                        gameReady = true;
                        //gameInstructing = false;
                        std::cout << "READY\n";
                    }

                    else if (!gameStart) {
//                        gameStart = true;
//                        //gameReady = false;
//                        std::cout << "START\n";
//                        view.setCenter(character.getPosition());
//                        distanceRan = 0;
//                        clock1.     restart();
//                        clock2.     restart();
//                        clock3.     restart();
//                        clockPlayed.restart();
                            startRequest = true;

                    }
                    else if (gameStart) {
                        //flip character
                        character.up = !character.up;
                        std::cout << "FLIP\n";
                    }

                } // end if


            }


            if (startRequest && character.getMoveSpeed() > 0.f && character.getMoveSpeed() < 6.f && character.getAngle() > 0 ) {
                     gameStart = true;
                     clock1.     restart();
                     clock2.     restart();
                     clock3.     restart();
                     clockPlayed.restart();
            }
            //std::cout << character.getMoveSpeed() << std::endl;
            ///////MOVE CHARACTER
            sf::Time elapsed = clock.restart();
            physics.a = Physics::G * sin(character.getAngle());
            //if (physics.a >  210) physics.a =  210;
            //if (physics.a < -210) physics.a = -210;
            //std::cout << physics.a << std::endl;
            float instantVeclocity = physics.a * elapsed.asSeconds();
            //std::cout << instantVeclocity << std::endl;
//            if (!gameStart) {
//                view.setCenter(120,0);
//                //instantVeclocity = 0;
//            }
            //physics.a_ms = math::G * cos(character.getAngle()) * math::MUY;
            //physics.a    = physics.a_qt - physics.a_ms;
            //std::cout << physics.a_qt << "    " << physics.a_ms << std::endl;

//            if (character.getAngle() >= 0) {
//
//                if (character.up == true) {
//                    //physics.v += physics.a * elapsed.asSeconds();
//                    character.addMoveSpeed(instantVeclocity);
//                }
//                else {
//                    //physics.v -= physics.a * elapsed.asSeconds();
//                    character.addMoveSpeed(-instantVeclocity);
//                }
//                //std::cout << elapsed.asSeconds() << std::endl;
//            }
//            else {
//                //physics.a = physics.G * sin(character.getAngle());
//
//                if (character.up == true) {
//                    //physics.v += physics.a * elapsed.asSeconds();
//                    character.addMoveSpeed(instantVeclocity);
//                }
//                else {
//                    //physics.v -= physics.a * elapsed.asSeconds();
//                    character.addMoveSpeed(-instantVeclocity);
//                }
//                //std::cout << elapsed.asSeconds() << std::endl;
//            } //end if

            if (!collided)
                if (character.up == true)
                    character.addMoveSpeed(instantVeclocity);
                else
                    character.addMoveSpeed(-instantVeclocity);
            else character.stop();

            //sf::Event start;
            //while (window.pollEvent(start)) {
                // if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                //     gameStart = true;
            //}

            //std::cout << "t : " << elapsed.asSeconds() << "   alpha = " << character.getAngle() << "    a = " << physics.a << "    v = " << character.getMoveSpeed() << std::endl;
            if (!gameStart) {
                view.setCenter(120,0);
                instruction_s.setColor(sf::Color(255, 255, 255, alpha += i));
                if (alpha >= 252) i = -3;
                if (alpha <= 90)  i =  3;
                //if (character.getMoveSpeed() > 200.f) character.setMoveSpeed(200.f);
                //if (character.getMoveSpeed() < -200.f) character.setMoveSpeed(-200.f);
                //curve.syncWithView(view);
            }
    //        sf::Time elapsed = clock.restart();
            float moveAmount = 0;
            //float y0 = curve[0].y;
            // if (character.getMoveSpeed() > 200.f) {

            //     float v0 = character.getMoveSpeed(),
            //           t  = 0,
            //           v0x,
            //           v0y,
            //           x = 0, y = 0;
            //     v0x = v0 * cos(character.getAngle());
            //     v0y = v0 * sin(character.getAngle());

            //     //while (y < curve[0].y) {
            //         t += 0.0165;
            //         //x = curve[0].x + v0x*t;
            //         //y = y0 + v0y*t - math::G*t*t/2.f;
            //     //}
            //     //man.setPosition(x, y);
            //     std::cout << "JUMP!\n";
            // }

            moveAmount += character.getMoveSpeed() * elapsed.asSeconds();
            if (!gameStart) distanceRan = 0;
            distanceRan += abs(moveAmount);
            //distanceText.setString("m: ");
            std::string unit = "m: ";
//            if (distanceRan > 20000) unit = "km: ";
            sf::Text distanceText{unit + std::to_string(distanceRan/20), font, 16};
    //distanceText.setPosition (0.f, 0.f);
            distanceText.setStyle    (sf::Text::Bold);
            distanceText.setFillColor(sf::Color::White);

            view.move(character.move(moveAmount));
            //generate continuous curve as character moves
//            viewX += moveAmount * cos(character.getAngle());
            //viewY += moveAmount * sin(character.getAngle());
            //viewX = clockPlayed.getElapsedTime().asSeconds() * 300;
            //if (viewX < character.getPosition().x) viewX = character.getPosition().x - 40;
            //viewY += clockPlayed.getElapsedTime().asSeconds() *
            //view.setCenter(viewX, viewY);
            curve.syncWithView(view);




            if (gameStart) {
                    //view.setCenter(character.getPosition().x-100, character.getPosition().y);
            //curve.syncWithView(view);
                // sf::Event event;
                // while (window.pollEvent(event)) {
                //     //close the window
                //     if (event.type == sf::Event::Closed)
                //         window.close();
                //     //if player presses any button
                //     else if (event.type == sf::Event::KeyPressed) {
                //         //flip character
                //         character.up = !character.up;
                //     } // end if
                // }

                ////GENERATE OBSTACLES
                timePlayed = clockPlayed.getElapsedTime();
                time1 = clock1.getElapsedTime();
                if (time1.asMilliseconds() > rand()%498+2267 && timePlayed.asSeconds() > 10 && !collided) {
                    position     = {curve.getXAppend(), curve.getYAppend()};
                    positionNext = {curve.getXAppendNext(), curve.getYAppendNext()};
                    Obstacle obstacle1_(obs1, position, positionNext);
                    clock1.restart();
                }

                time2 = clock2.getElapsedTime();
                if (time2.asMilliseconds() > rand()%975+3040 && timePlayed.asSeconds() > 17 && !collided) {
                    position     = {curve.getXAppend(), curve.getYAppend()};
                    positionNext = {curve.getXAppendNext(), curve.getYAppendNext()};
                    Obstacle obstacle2_(obs2, position, positionNext);
                    clock2.restart();
                }

                time3 = clock3.getElapsedTime();
                if (time3.asMilliseconds() > rand()%1000+4373 && timePlayed.asSeconds() > 27 && !collided) {
                    position     = {curve.getXAppend(), curve.getYAppend()};
                    positionNext = {curve.getXAppendNext(), curve.getYAppendNext()};
                    Obstacle obstacle3_(obs3, position, positionNext);
                    clock3.restart();
                }

                if (Collision::PixelPerfectTest(man, obs1) ||
                  Collision::PixelPerfectTest(man, obs2) ||
                  Collision::PixelPerfectTest(man, obs3)) {
                    //view.setCenter(0, 0);
                    //character.stop();
                    collided = true;
                    //physics.a = 0;
                    //gmovrTime = gmovrClock.restart();
                    //std::cout << gmovrTime.asSeconds();
                    //view.setCenter(0, 0);
                    //gameOver = true;
                }
            }
    //            else if (event.type == sf::Event::KeyPressed)
    //            {
    //                if (event.key.code == sf::Keyboard::Up)
    //                {
    //                    character.addMoveSpeed(10.f);
    //                   moveSpeedText.setString(
    //                       "Move speed: " +
    //                       std::to_string(character.getMoveSpeed()));
    //                }
    //                else if (event.key.code == sf::Keyboard::Down)
    //                {
    //                    character.addMoveSpeed(-10.f);
    //                    moveSpeedText.setString(
    //                        "Move speed: " +
    //                        std::to_string(character.getMoveSpeed()));
    //                }
    //            }

//            sf::Clock gmovrClock;
//            sf::Time gmovrTime;


            //if (collided) view.setCenter(character.getPosition().x-90, character.getPosition().y-90);
            //std::cout << character.getMoveSpeed() << std::endl;
            //if (collided) character.stop();

            //if (gmovrTime.asSeconds() == 1.5) gameOver = true;


            //window.setView(view);
            window.clear(sf::Color(40, 40, 40));


            if (!gameReady) {
                if (!gameInstructing)
                    window.draw(mainM_s);
                else {
                    //window.draw(gravityGradient_s);
                    if (insAlpha < 250)
                        insAlpha += 5;
                    instruction1_s.setColor(sf::Color(255, 255, 255, insAlpha));
                    window.draw(instruction1_s);
                }
                window.draw(instruction_s);
            }
            else if (!startRequest){
                if (readyAlpha < 250)
                    readyAlpha += 5;
                youReady_s.setColor(sf::Color(255, 255, 255, readyAlpha));
                window.draw(youReady_s);
            }
            //if (startRequest && character.getMoveSpeed() > 0.f && character.getMoveSpeed() < 6.f && character.getAngle() > 0 )
            //{
             //   character.stop();
               // window.draw(grad_s);
            //}

            window.setView    (view);
            window.draw       (curve);
            window.draw       (character);

            if (gameStart) {
                //window.setView(view);
                window.draw   (obstacle1);
                window.draw   (obstacle2);
                window.draw   (obstacle3);

            }
            window.setView(window.getDefaultView());

            if (startRequest)
                window.draw   (distanceText);
            window.display();
        }//while game is not over


        //window.clear(sf::Color::Black);
        // window.draw            (gmovrM_s);
        // window.display         ();




//        float moveAmount = 0;
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//            moveAmount += character.getMoveSpeed() * elapsed.asSeconds();
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//            moveAmount -= character.getMoveSpeed() * elapsed.asSeconds();
//        if (moveAmount != 0)
//        {
//            view.move(character.move(moveAmount));
//            curve.syncWithView(view);
           // curvePointsText.setString("Curve points: " +
           //                           std::to_string(curve.getPointsCount()));
           // positionText.setString(
           //     "Position: " + std::to_string(character.getPosition().x) +
           //     ", " + std::to_string(character.getPosition().y));
//        }


    }//end main loop
}
