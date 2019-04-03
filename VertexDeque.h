#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <algorithm>

class VertexContiguousDeque : public sf::Drawable
{
public:
    VertexContiguousDeque(sf::PrimitiveType type, size_t vertexCount = 0): 
    mPtr(vertexCount ? new sf::Vertex[vertexCount] : nullptr),
    mPrimitiveType(type),
    mSize(vertexCount)
    {}

    ~VertexContiguousDeque() {
        delete[] mPtr;
    }

    size_t getVertexCount() const {
        return mSize;
    }

    sf::Vertex& operator[](size_t index) {
        return mPtr[index + mSpaceFront];
    }

    const sf::Vertex& operator[](size_t index) const {
        return mPtr[index + mSpaceFront];
    }

    void resize(size_t vertexCount) {
        if (vertexCount > mSize) {
            size_t capacity = mSpaceFront + mSize + mSpaceBack;

            if (vertexCount > capacity) {
                expand(vertexCount, false);
                // Reset sizes
                mSize = vertexCount;
                mSpaceFront = mSpaceBack = 0; // sf::Vertex is trivial class
            }
            else {
                centerize(vertexCount - mSize);
                // Reset spaces
                mSize = vertexCount;
                mSpaceBack = capacity - mSize - mSpaceFront;
            }
        }
        else
            // Simply decrease mSize since sf::Vertex is trivial
            mSize = vertexCount;
    }

    void append(const sf::Vertex& vertex) {
        if (!mSpaceBack) expand(mSize * 3);
        mPtr[mSpaceFront + mSize] = vertex;
        mSpaceBack--;
        mSize++;
    }

    void prepend(const sf::Vertex& vertex) {
        if (!mSpaceFront) expand(mSize * 3);
        mPtr[mSpaceFront - 1] = vertex;
        mSpaceFront--;
        mSize++;
    }

    void setPrimitiveType(sf::PrimitiveType type) {
        mPrimitiveType = type;
    }

    sf::PrimitiveType getPrimitiveType() const {
        return mPrimitiveType;
    }

    void removeFirst() {
        if (!mSize) return;
        mSpaceFront++;
        mSize--;
    }

    void removeLast() {
        if (!mSize) return;
        mSpaceBack++;
        mSize--;
    }

private:
    sf::Vertex* mPtr = nullptr;
    size_t mSize = 0;
    size_t mSpaceFront = 0;
    size_t mSpaceBack = 0;
    sf::PrimitiveType mPrimitiveType = sf::Points;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        if (mSize) target.draw(mPtr + mSpaceFront, mSize, mPrimitiveType, states);
    }

    void expand(size_t newCapacity, bool centerCopy = true) {
        size_t capacity = mSpaceFront + mSize + mSpaceBack;
        if (newCapacity <= capacity) return centerize();

        auto newPtr = new sf::Vertex[newCapacity];
        // Copy vertices from current holder to new one
        size_t newSpaceFront = centerCopy ? (newCapacity - mSize) / 2 : 0;
        std::copy(mPtr + mSpaceFront, mPtr + mSpaceFront + mSize,
                  newPtr + newSpaceFront);
        // Swap pointers and delete swapped pointer
        std::swap(mPtr, newPtr);
        delete[] newPtr;
        // Reset spaces
        mSpaceFront = newSpaceFront;
        mSpaceBack = newCapacity - mSize - mSpaceFront;
    }
    
    void centerize(size_t deltaSize = 0) {
        auto pRead = mPtr + mSpaceFront;
        size_t capacity = mSpaceFront + mSize + mSpaceBack;
        size_t newSpaceFront = (capacity - mSize - deltaSize) / 2;
        auto pWrite = mPtr + newSpaceFront;
        for (size_t i = 0; i < mSize; ++i) *pWrite++ = *pRead++;
        // Reset spaces
        mSpaceFront = newSpaceFront;
        mSpaceBack = capacity - mSize - mSpaceFront;
    }
};
