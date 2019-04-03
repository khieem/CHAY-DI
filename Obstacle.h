#pragma once

#include "Common.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Obstacle : public sf::Drawable {
public:
	Obstacle(sf::Shape& shape, const sf::Vector2f& position_, const sf::Vector2f& positionNext_)
	: shape(shape), position(position_), positionNext(positionNext_)
	{
		shape.setPosition(position);
		fixRotation();
	}

	void fixRotation() {
		angle = angleSlope(position, positionNext);
		shape.setRotation(angle-90);
	}

	float getAngle() const {
        return angle;
    }

    void setSpeedThreshold(const float& speed) {
    	speedThreshold = speed;
    }

private:
	sf::Shape& shape;
	float angle;
	sf::Vector2f position, positionNext;
	float speedThreshold;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(shape, states);
    }
};

