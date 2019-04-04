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
//    int seed = 13217;
//    seed = 472;
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
    Curve curve(5.f, window.getSize().x, yGen);

    ////INITIALIZE CHARACTER
    //determine if our character is upside-down or not
    bool characterUp = true;
    int yOrigin = 50;
    sf::RectangleShape shape(sf::Vector2f(30.f, 50.f));
    shape.setFillColor(sf::Color(68, 196, 164));
    //create a bool allows our character to flip by toggling
    //between 50 and 0 in main loop
    Character character(shape, curve);

    ////OBSTACLE
    sf::Vector2f position, positionNext;
    sf::RectangleShape obstacleShape1(sf::Vector2f(50.f, 50.f));
    obstacleShape1.setFillColor(sf::Color::Red);
    sf::RectangleShape obstacleShape2(sf::Vector2f(50.f, 50.f));
    obstacleShape2.setFillColor(sf::Color::Yellow);
    sf::RectangleShape obstacleShape3(sf::Vector2f(50.f, 50.f));
    obstacleShape3.setFillColor(sf::Color::Green);

    Obstacle obstacle1(obstacleShape1, position, positionNext),
             obstacle2(obstacleShape2, position, positionNext),
             obstacle3(obstacleShape3, position, positionNext);
    obstacle1.setSpeedThreshold(300.f);
    obstacle2.setSpeedThreshold(500.f);
    obstacle3.setSpeedThreshold(600.f);

    ////CLOCK
    long int clock1 = 0, clock2 = 0, clock3 = 0, clock4 = 0, clock5 = 0, clock6 = 0, clock7 = 0;

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
        ///////FLIP CHARACTER
        yOrigin = (characterUp ? 50 : 0);
        shape.setOrigin(15, yOrigin);

        ///////MOVE CHARACTER
        //game's special logic
        if (character.getAngle() > 0) {
            if (characterUp == true)
                character.addMoveSpeed(1);
            else character.addMoveSpeed(1);
        }
        else {
            if (characterUp == true)
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

        if (obstacle1.isUsed == false && character.getMoveSpeed() > obstacle1.getSpeedThreshold()) {
            position     = {curve.getXAppend(), curve.getYAppend()};
            positionNext = {curve.getXAppendNext(), curve.getYAppendNext()};
            Obstacle obstacles1(obstacleShape1, position, positionNext);
            obstacle1.isUsed = true;
        }

        if (obstacle1.isUsed)
            ++clock1;
        if (clock1 == 189) {
                obstacle1.isUsed = false;
                clock1 = 0;
        }

        if (obstacle2.isUsed == false && character.getMoveSpeed() > obstacle2.getSpeedThreshold()) {
            position     = {curve.getXAppend(), curve.getYAppend()};
            positionNext = {curve.getXAppendNext(), curve.getYAppendNext()};
            Obstacle obstacles2(obstacleShape2, position, positionNext);
            obstacle2.isUsed = true;
        }

        if (obstacle2.isUsed)
            ++clock2;
        if (clock2 == 289) {
                obstacle2.isUsed = false;
                clock2 = 0;
        }

        if (obstacle3.isUsed == false && character.getMoveSpeed() > obstacle3.getSpeedThreshold()) {
            position     = {curve.getXAppend(), curve.getYAppend()};
            positionNext = {curve.getXAppendNext(), curve.getYAppendNext()};
            Obstacle obstacles3(obstacleShape3, position, positionNext);
            obstacle3.isUsed = true;
        }

        if (obstacle3.isUsed)
            ++clock3;
        if (clock3 == 241) {
                obstacle3.isUsed = false;
                clock3 = 0;
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            //close the window
            if (event.type == sf::Event::Closed)
                window.close();
            //if player presses any button
            else if (event.type == sf::Event::KeyPressed) {
                //flip character
                characterUp = !characterUp;
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
        // window.draw(obstacle4);
        // window.draw(obstacle5);
        // window.draw(obstacle6);
        // window.draw(obstacle7);
        window.setView(window.getDefaultView());
        //window.draw(moveSpeedText);
        window.display();
    }//end main loop
}
