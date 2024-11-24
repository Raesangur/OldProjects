#include <cmath>
#include <iostream>
#include "vector3.h"

template <typename vector>
vector orthogonalProjection(const vector& u, const vector& v)
{
    double projection = u * v;
    double length = v.length() * v.length();

    return v * (projection / length);
}

vector3 matrixProduct(const vector3& u, const vector3& v)
{
    double a = u.b * v.c - v.b * u.c;
    double b = -(u.a * v.c - v.a * u.c);
    double c = u.a * v.b - v.a * u.b;

    return vector3(a, b, c);
}

template <typename vector>
double angle(const vector& u, const vector& v)
{
    double projection = u * v;
    double length = u.length() * v.length();

    return std::acos(projection / length) * (180/3.14159265358979323846264338327) ;
}

int main()
{
    vector3 u = { 1, 0, 0 };
    vector3 v = { 1, 0, 0 };

    vector3 uv = matrixProduct(u, v);
    uv.print();

    std::cin.get();
}
