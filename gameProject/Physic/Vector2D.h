#pragma once
#include <iostream>

class Vector2D
{
private:
    float x;
    float y;

public:
    Vector2D()
        : x(0), y(0)
    {
    }

    Vector2D(float _x, float _y)
        : x(_x), y(_y)
    {
    }

    float getX() const {
        return x;
    }

    void setX(float _x) {
        x = _x;
    }

    float getY() const {
        return y;
    }

    void setY(float _y) {
        y = _y;
    }

    // Cộng vector
    Vector2D operator+(const Vector2D& v2) const
    {
        return Vector2D(x + v2.x, y + v2.y);
    }

    // Trừ vector
    Vector2D operator-(const Vector2D& v2) const
    {
        return Vector2D(x - v2.x, y - v2.y);
    }

    // Nhân vector
    Vector2D operator*(const float c) const
    {
        return Vector2D(x * c, y * c);
    }

    void moveX(float stepX)
    {
        x += stepX;
    }

    inline void moveY(float stepY)
    {
        y += stepY;
    }

    float getLength() const
    {
        return std::sqrt(x * x + y * y);
    }

    Vector2D getNormalized() const
    {
        float length = getLength();
        if (length > 0)
        {
            return Vector2D(x / length, y / length);
        }
        else
        {
            return Vector2D(0, 0);
        }
    }

    void print(const std::string& theObject) const
    {
        std::cout << theObject << " ( " << x << " " << y << " )" << std::endl;
    }

    float distance(const Vector2D& other) const {
        float dx = x - other.getX();
        float dy = y - other.getY();
        return std::sqrt(dx * dx + dy * dy);
    }
};
