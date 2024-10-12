#pragma once
#include <cmath>

class Float2 {
public:
    // Constructors
    Float2() : x(0.0f), y(0.0f) {}
    Float2(float x, float y) : x(x), y(y) {}

    // Member variables
    float x;
    float y;

    // Operator overloads for easy manipulation
    Float2 operator+(const Float2& other) const {
        return Float2(x + other.x, y + other.y);
    }

    Float2 operator-(const Float2& other) const {
        return Float2(x - other.x, y - other.y);
    }

    Float2 operator*(float scalar) const {
        return Float2(x * scalar, y * scalar);
    }

    Float2 operator/(float scalar) const {
        if (scalar != 0) {
            return Float2(x / scalar, y / scalar);
        }
        return Float2(0, 0); // Handle division by zero appropriately
    }

    // Length of the vector
    float Length() const {
        return sqrt(x * x + y * y);
    }

    // Normalized version of the vector
    Float2 Normalize() const {
        float length = Length();
        if (length > 0) {
            return *this / length;
        }
        return *this; // Return the original vector if it's zero
    }
};
