#pragma once

#include "VertexDeque.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <functional>

class Curve : public sf::Drawable
{
public:
    template <class YGen>
    Curve(float xStep, unsigned screenWidth, YGen&& yGen)
    : xStep(xStep),
      lines(sf::LinesStrip, (int)std::ceil(screenWidth / xStep)),
      indexOffset(0),
      yGen(yGen)
    {
        for (int i = 0; i < lines.getVertexCount(); ++i) {
            lines[i].position = sf::Vector2f{i * xStep, yGen(i * xStep)};
            lines[i].color = sf::Color::White;
        }
    }

    const sf::Vector2f& operator[](int index) const {
        return lines[index - indexOffset].position;
    }

    void syncWithView(const sf::View& view) {
        float left = view.getCenter().x - view.getSize().x / 2;
        float right = view.getCenter().x + view.getSize().x / 2;
        // Append more points
        while (lines[lines.getVertexCount() - 1].position.x < right) {
            xAppend = lines[lines.getVertexCount() - 1].position.x + xStep;
            yAppend = yGen(xAppend);
            lines.append(sf::Vertex(sf::Vector2f(xAppend, yAppend), sf::Color::White));
            // doesn't affect indexOffset
        }
        // Prepend more points
        while (lines[0].position.x > left) {
            float x = lines[0].position.x - xStep;
            float y = yGen(x);
            lines.prepend(sf::Vertex{sf::Vector2f{x, y}, sf::Color::White});
            indexOffset--;
        }
        // Trim right points
        while (lines[lines.getVertexCount() - 1].position.x - xStep > right) {
            lines.removeLast();
            // doesn't affect indexOffset
        }
        // Trim left points
        while (lines[0].position.x + xStep < left) {
            lines.removeFirst();
            indexOffset++;
        }
    }

    size_t getPointsCount() const {
        return lines.getVertexCount();
    }

    double getXAppend() const {
        return xAppend;
    }

    double getYAppend() const {
        return yAppend;
    }

private:
    float xStep;
    VertexContiguousDeque lines;
    int indexOffset;
    std::function<float(float)> yGen;
    double xAppend; //point appended to the right's x
    double yAppend; //point appended to the right's y

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(lines, states);
    }
};
