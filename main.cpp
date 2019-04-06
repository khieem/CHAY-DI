#include "Character.h"
#include "Curve.h"
#include "Obstacle.h"
#include "ImprovedPerlinNoise.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    //render window
    sf::RenderWindow window(sf::VideoMode(800, 500), "CHAY DI!!!");
    window.setFramerateLimit(60);

    //initialize properties for the curve
    ImprovedPerlinNoise noiseGen;
    auto yGen = [&](float x) {
        const float xScale = 2e-3f;
        const float yMagnitude1 = 20;
        const float yMagnitude2 = 130;
        const float yMagnitude3 = 60;
        const float yMagnitude4 = 50;

        const float xScaled = x * xScale;
        return float(yMagnitude1 * noiseGen.noise(xScaled * 0) +
                     yMagnitude2 * noiseGen.noise(xScaled * 1) +
                     yMagnitude3 * noiseGen.noise(xScaled * 0.8) +
                     yMagnitude4 * noiseGen.noise(xScaled * 1));
    };

    //create the in-sight curve with the properties initialized
    Curve curve(2.f, window.getSize().x, yGen);

    ////INITIALIZE CHARACTER
    sf::Texture manTexture;
    manTexture.loadFromFile("character.png");
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
//    sf::RectangleShape obstacleShape1(sf::Vector2f(50.f, 50.f));
//    obstacleShape1.setFillColor(sf::Color::Red);
//    sf::RectangleShape obstacleShape2(sf::Vector2f(50.f, 50.f));
//    obstacleShape2.setFillColor(sf::Color::Yellow);
//    sf::RectangleShape obstacleShape3(sf::Vector2f(50.f, 50.f));
//    obstacleShape3.setFillColor(sf::Color::Green);

    Obstacle obstacle1(obs1, position, positionNext),
             obstacle2(obs2, position, positionNext),
             obstacle3(obs3, position, positionNext);

    ////CLOCK
    sf::Clock clock1, clock2, clock3, clockPlayed;
    sf::Time  time1,  time2,  time3,  timePlayed;

    sf::View view = window.getView();
    view.setCenter(120, 0);
    curve.syncWithView(view);

    //load font
    sf::Font font;
    if (!font.loadFromFile("MAIAN.ttf")) {
        std::cout << "Cannot open MAIAN.ttf\n";
        return 1;
    }//end loading font

//    sf::Text seedText("Seed: " + std::to_string(seed), font, 1);
//    seedText.setPosition(0, 0);
//    seedText.setFillColor(sf::Color::Black);
   // sf::Text moveSpeedText(
   //     "Move speed: " + std::to_string(character.getMoveSpeed()), font, 16);
   // moveSpeedText.setPosition(0, 16);
   // moveSpeedText.setFillColor(sf::Color::Black);
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
    //main loop
    while (window.isOpen()) {
        window.clear(sf::Color(53, 49, 74));

        ///////MOVE CHARACTER
        if (character.getAngle() > 0) {
            if (character.up == true)
                character.addMoveSpeed(1);
            else character.addMoveSpeed(1);
        }
        else {
            if (character.up == true)
                character.addMoveSpeed(-1.f);
            else character.addMoveSpeed(1.f);
        } //end if

        sf::Time elapsed = clock.restart();
        float moveAmount = 0;
        moveAmount += character.getMoveSpeed() * elapsed.asSeconds();
        //most important statement! makes player feel like character is moving
        view.move(character.move(moveAmount));
        //generate continuous curve as character moves
        curve.syncWithView(view);

        ////GENERATE OBSTACLES
        timePlayed = clockPlayed.getElapsedTime();
        time1 = clock1.getElapsedTime();
        if (time1.asMilliseconds() > rand()%498+2267 && timePlayed.asSeconds() > 10) {
            position     = {curve.getXAppend(), curve.getYAppend()};
            positionNext = {curve.getXAppendNext(), curve.getYAppendNext()};
            Obstacle obstacle1_(obs1, position, positionNext);
            clock1.restart();
        };

        time2 = clock2.getElapsedTime();
        if (time2.asMilliseconds() > rand()%975+3040 && timePlayed.asSeconds() > 17) {
            position     = {curve.getXAppend(), curve.getYAppend()};
            positionNext = {curve.getXAppendNext(), curve.getYAppendNext()};
            Obstacle obstacle2_(obs2, position, positionNext);
            clock2.restart();
        }

        time3 = clock3.getElapsedTime();
        if (time3.asMilliseconds() > rand()%1000+4373 && timePlayed.asSeconds() > 27) {
            position     = {curve.getXAppend(), curve.getYAppend()};
            positionNext = {curve.getXAppendNext(), curve.getYAppendNext()};
            Obstacle obstacle3_(obs3, position, positionNext);
            clock3.restart();
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            //close the window
            if (event.type == sf::Event::Closed)
                window.close();
            //if player presses any button
            else if (event.type == sf::Event::KeyPressed) {
                //flip character
                character.up = !character.up;
            } // end if
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
        }


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

        window.setView(view);
        window.draw(curve);
        window.draw(character);
        window.draw(obstacle1);
        window.draw(obstacle2);
        window.draw(obstacle3);
        window.setView(window.getDefaultView());
        //window.draw(moveSpeedText);
        window.display();
    }//end main loop
}
