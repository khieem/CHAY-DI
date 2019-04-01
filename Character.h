#pragma once

#include "Curve.h"
#include "Character.h"
#include "Common.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Character : public sf::Drawable
{
public:
    Character(sf::Shape& shape, const Curve& curve, float moveSpeed = 300.f)
    : shape(shape),
      moveSpeed(moveSpeed),
      curve(curve),
      segmentIndex{0},
      segmentPercentage{0}
    {
        shape.setPosition(curve[0]);
        fixRotation();
    }

    sf::Vector2f move(float amount) {
        if (amount == 0) return {};
        return amount > 0 ? moveRight(amount) : moveLeft(-amount);
    }

    sf::Vector2f moveLeft(float moveAmt) {
        auto const& a = curve[segmentIndex];
        auto const& b = curve[segmentIndex + 1];
        float segmentLen = distance(a, b) * segmentPercentage;
        if (moveAmt < segmentLen) {
            segmentPercentage -= moveAmt / segmentLen;
            auto newPos = lerp(a, b, segmentPercentage);
            auto moveDist = newPos - shape.getPosition();
            shape.move(moveDist);
            fixRotation();
            return moveDist;
        }
        else {
            moveAmt -= segmentLen;
            segmentIndex--;
            segmentPercentage = 1;
            return moveLeft(moveAmt);
        }
    }

    sf::Vector2f moveRight(float moveAmt) {
        auto const& a = curve[segmentIndex];
        auto const& b = curve[segmentIndex + 1];
        float segmentLen = distance(a, b) * (1 - segmentPercentage);
        if (moveAmt < segmentLen) {
            segmentPercentage += moveAmt / segmentLen;
            auto newPos = lerp(a, b, segmentPercentage);
            auto moveDist = newPos - shape.getPosition();
            shape.move(moveDist);
            fixRotation();
            return moveDist;
        }
        else {
            moveAmt -= segmentLen;
            segmentIndex++;
            segmentPercentage = 0;
            return moveRight(moveAmt);
        }
    }

    void fixRotation() {
        auto const& a = curve[segmentIndex];
        auto const& b = curve[segmentIndex + 1];
        shape.setRotation(angleSlope(a, b));
    }

    void addMoveSpeed(float amount) {
        moveSpeed += amount;
        if (moveSpeed < 0) moveSpeed = 0;
    }

    float getMoveSpeed() const {
        return moveSpeed;
    }

    sf::Vector2f getPosition() const {
        return shape.getPosition();
    }

private:
    sf::Shape& shape;
    float moveSpeed;
    const Curve& curve;
    int segmentIndex;
    float segmentPercentage;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(shape, states);
    }
};
