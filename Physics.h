#pragma once

#include <SFML/System/Vector2.hpp>

namespace math {
	const double PI = 3.14159265358979323846;
	const double DEG_PER_RAD = 180 / PI;
	const double RAD_PER_DEG = PI / 180;
} // namespace math

float distance(const sf::Vector2f& a, const sf::Vector2f& b) {
    auto d = b - a;
    return std::sqrt(d.x * d.x + d.y * d.y);
}

sf::Vector2f lerp(const sf::Vector2f& a, const sf::Vector2f& b, const float& percentage) {
	return (1 - percentage) * a + percentage * b;
}

float angleSlope(const sf::Vector2f& a, const sf::Vector2f& b) {
    using namespace math;
    auto d = b - a;
    return float(std::atan(d.y / d.x) * DEG_PER_RAD);
}

class Physics {
public:
    Physics() : a(0), ax(0), v(0), Fms(0), F(0) {}

    float a;
	float ax;
	float v;
	float Fms;
	float F;
	float G = 500;
	float M = 200;
};
