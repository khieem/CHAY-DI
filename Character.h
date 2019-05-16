#pragma once

#include "Curve.h"
#include "Physics.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Character : public sf::Drawable
{
public:
    bool up = true;

    Character(sf::Sprite& sprite, const Curve& curve, float moveSpeed = 100.f)
    : sprite(sprite),
      moveSpeed(moveSpeed),
      curve(curve),
      segmentIndex(0),
      segmentPercentage(0)
    {
        sprite.setPosition(curve[0]);
        sprite.setOrigin(25, 50);
        fixRotation();
    }

    sf::Vector2f move(float amount) {
        if (amount == 0) return {};
        return amount > 0 ? moveRight(amount) : moveLeft(-amount);
    }

    sf::Vector2f moveLeft(float moveAmt) {
        auto const& a = curve[segmentIndex];
        auto const& b = curve[segmentIndex + 1];
        float segmentLen = Physics::distance(a, b) * segmentPercentage;
        if (moveAmt < segmentLen) {
            segmentPercentage -= moveAmt / segmentLen;
            auto newPos = Physics::lerp(a, b, segmentPercentage);
            auto moveDist = newPos - sprite.getPosition();
            sprite.move(moveDist);
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
        float segmentLen = Physics::distance(a, b) * (1 - segmentPercentage);
        if (moveAmt < segmentLen) {
            segmentPercentage += moveAmt / segmentLen;
            auto newPos = Physics::lerp(a, b, segmentPercentage);
            auto moveDist = newPos - sprite.getPosition();
            sprite.move(moveDist);
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
        angle = Physics::angleSlope(a, b);
        float phi = (up ? 0 : 180);
        sprite.setRotation(angle + phi);
    }

    void addMoveSpeed(const float& amount) {
        moveSpeed += amount;
    }

    float getMoveSpeed() const {
        return moveSpeed;
    }

    sf::Vector2f getPosition() const {
        return sprite.getPosition();
    }

    float getAngle() const {
        return angle * Physics::RAD_PER_DEG;
    }

    void stop() {
        setMoveSpeed(0.f);
    }

    void setMoveSpeed(float v) {
        moveSpeed = v;
    }

private:
    sf::Sprite& sprite;
    float moveSpeed;
    const Curve& curve;
    int segmentIndex;
    float segmentPercentage;
    float angle;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(sprite, states);
    }
};
