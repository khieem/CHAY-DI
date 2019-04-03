#pragma once

#include <SFML/System/Vector2.hpp>

namespace math {
	const double pi = 3.14159265358979323846;
	const double deg_per_rad = 180 / pi;
	const double rad_per_dec = pi / 180;
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
    return float(std::atan(d.y / d.x) * deg_per_rad);
}
