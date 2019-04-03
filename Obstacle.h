#pragma once

#include "Curve.h"
#include "Common.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Obstacle : public sf::Drawable {
public:
	Obstacle(sf::Shape& shape, const Curve& curve, int x, int y)
	: shape(shape), curve(curve)
	{
		shape.setPosition(x, y);
		fixRotation();
	}

	void fixRotation() {
		auto const& a = x;
		auto const& b = y;
		angle = angleSlope(x, y);
		shape.setRotation(angle);
	}

private:
	sf::Shape& shape;
	const Curve& curve;
	double angle;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(shape, states);
    }
};

