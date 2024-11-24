#pragma once
#include <cmath>
#include <iostream>

class vector3
{
public:
    constexpr vector3(double _a, double _b, double _c) : a(_a), b(_b), c(_c){}

    constexpr double operator*(const vector3& rhs) const
    {
        return a * rhs.a + b * rhs.b + c * rhs.c;
    }
    constexpr vector3 operator*(double rhs) const
    {
        return vector3(a * rhs, b * rhs, c * rhs);
    }
    double length() const
    {
        return std::sqrt(a * a + b * b + c * c);
    }

    void print() const
    {
        std::cout << "a: " << a << " b: " << b << " c: " << c << '\n';
    }

    double a = 0.0;
    double b = 0.0;
    double c = 0.0;
};

class vector2
{
public:
    constexpr vector2(double _a, double _b) : a(_a), b(_b) {}

    constexpr double operator*(const vector2& rhs) const
    {
        return a * rhs.a + b * rhs.b;
    }
    constexpr vector2 operator*(double rhs) const
    {
        return vector2(a * rhs, b * rhs);
    }
    double length() const
    {
        return std::sqrt(a * a + b * b);
    }

    void print() const
    {
        std::cout << "a: " << a << " b: " << b << '\n';
    }

    double a = 0.0;
    double b = 0.0;
};