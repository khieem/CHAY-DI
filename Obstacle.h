#pragma once

#include "Common.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <time.h>

class Obstacle : public sf::Drawable {
public:
    bool up = true;
	Obstacle(sf::Sprite& sprite, const sf::Vector2f& position_, const sf::Vector2f& positionNext_)
	: sprite(sprite), position(position_), positionNext(positionNext_)
	{
	    srand(time(NULL));
	    up = rand()%2;
		sprite.setPosition(position);
        sprite.setOrigin(70, 70);
		fixRotation();
	}

	void fixRotation() {
		angle = angleSlope(position, positionNext);
		float phi = (up ? 0 : 180);
		sprite.setRotation(angle - phi);
	}

	float getAngle() const {return angle;}

private:
	sf::Sprite& sprite;
	float angle;
	sf::Vector2f position, positionNext;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(sprite, states);
    }
};

