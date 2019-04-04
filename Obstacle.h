#pragma once

#include "Common.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <time.h>

class Obstacle : public sf::Drawable {
public:
	bool up;
	bool isUsed;

	Obstacle(sf::Shape& shape) : shape(shape)
	{
        position = sf::Vector2f(0,0);
        positionNext = sf::Vector2f(0,0);
	}

	Obstacle(sf::Shape& shape, const sf::Vector2f& position_, const sf::Vector2f& positionNext_)
	: shape(shape), position(position_), positionNext(positionNext_)
	{
	    srand(time(NULL));
	    up = rand()%2;
		shape.setPosition(position);
		if (up == 1) shape.setOrigin(50, 50);
		else shape.setOrigin(0, 0);
		fixRotation();
		isUsed = false;
	}

	void fixRotation() {
		angle = angleSlope(position, positionNext);
		float phi = (up ? 0 : 90);
		shape.setRotation(angle + phi);
	}

	float getAngle() const {return angle;}

    void setSpeedThreshold(const float& speed) {speedThreshold = speed;}

    float getSpeedThreshold() const {return speedThreshold;}

private:
	sf::Shape& shape;
	float angle;
	sf::Vector2f position, positionNext;
	float speedThreshold;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(shape, states);
    }
};

