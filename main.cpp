#include "Character.h"
#include "Curve.h"
#include "ImprovedPerlinNoise.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    //render window
    sf::RenderWindow window(sf::VideoMode(800, 500), "Infinite Curve");
    window.setFramerateLimit(60);

    //initialize properties for the curve
    ImprovedPerlinNoise noiseGen;
    int seed = 13217;
    seed = 472;
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

    //create the in-sight curve with the properties initialzed
    Curve curve(5.f, window.getSize().x, yGen);

    //initialize character
    sf::RectangleShape shape({20, 30});
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(10, 30);
    Character character(shape, curve);

    sf::View view = window.getView();
    view.setCenter(-5, 5);
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
//    sf::Text moveSpeedText(
//        "Move speed: " + std::to_string(character.getMoveSpeed()), font, 16);
//    moveSpeedText.setPosition(0, 16);
//    moveSpeedText.setFillColor(sf::Color::Black);
//    sf::Text curvePointsText{
//        "Curve points: " + std::to_string(curve.getPointsCount()), font, 16};
//    curvePointsText.setPosition(0, 32);
//    curvePointsText.setFillColor(sf::Color::Black);
//    sf::Text positionText{
//        "Position: " + std::to_string(character.getPosition().x) + ", " +
//            std::to_string(character.getPosition().y),
//        font, 16};
//    positionText.setPosition(0, 48);
//    positionText.setFillColor(sf::Color::Black);

    sf::Clock clock;
    //main loop
    while (window.isOpen()) {
        ///////MOVE CHARACTER
        sf::Time elapsed = clock.restart();
        float moveAmount = 0;
        //calculate the distance which character moves after every loop
        moveAmount += character.getMoveSpeed() * elapsed.asSeconds();
        //most important statement! makes player feel like character is moving
        view.move(character.move(moveAmount));
        //create continuous curve as character moves
        curve.syncWithView(view);
        ///////END MOVING CHARACTER

        sf::Event event;
        while (window.pollEvent(event)) {
            //close the window
            if (event.type == sf::Event::Closed)
                window.close();
            //if player presses any button
            else if (event.type == sf::Event::KeyPressed) {
                //flip character
                std::cout << "FLIP!\n";
            }
//            else if (event.type == sf::Event::KeyPressed)
//            {
//                if (event.key.code == sf::Keyboard::Up)
//                {
//                    character.addMoveSpeed(10.f);
//                    moveSpeedText.setString(
//                        "Move speed: " +
//                        std::to_string(character.getMoveSpeed()));
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
//            curvePointsText.setString("Curve points: " +
//                                      std::to_string(curve.getPointsCount()));
//            positionText.setString(
//                "Position: " + std::to_string(character.getPosition().x) +
//                ", " + std::to_string(character.getPosition().y));
//        }

        window.setView(view);
        window.clear(sf::Color::White);
        window.draw(curve);
        window.draw(character);
        window.setView(window.getDefaultView());
//        window.draw(seedText);
//        window.draw(moveSpeedText);
//        window.draw(curvePointsText);
//        window.draw(positionText);
        window.display();
    }//end main loop
}
