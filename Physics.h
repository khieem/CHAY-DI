#pragma once

#include <SFML/System/Vector2.hpp>

class Physics {
public:
    Physics() : a(0) {}

    static float distance(const sf::Vector2f& a, const sf::Vector2f& b) {
        auto d = b - a;
        return std::sqrt(d.x * d.x + d.y * d.y);
    }

    static sf::Vector2f lerp(const sf::Vector2f& a, const sf::Vector2f& b, const float& percentage) {
        return (1 - percentage) * a + percentage * b;
    }

    static float angleSlope(const sf::Vector2f& a, const sf::Vector2f& b) {
        auto d = b - a;
        return float(std::atan(d.y / d.x) * DEG_PER_RAD);
    }


    float a;
    //float ams;

    static constexpr float PI          = 3.14159265358979323846;
	static constexpr float DEG_PER_RAD = 180 / PI;
	static constexpr float RAD_PER_DEG = PI / 180;
	static constexpr float G           = 400;
};
