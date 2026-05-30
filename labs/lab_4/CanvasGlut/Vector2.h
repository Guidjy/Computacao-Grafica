#ifndef __VECTOR_2_H__
#define __VECTOR_2_H__

#include <array>
#include <compare>

#define PI   3.14159265359f


class Vector2
{
public:
    float x, y;

    Vector2()
    {
        x = y = 0;
    }

    Vector2(float _x, float _y)
    {
        x = _x;
        y = _y;
    }

    void set(float _x, float _y)
    {
        x = _x;
        y = _y;
    }

    Vector2 normalize()
    {
        Vector2 v = Vector2(x, y);

        float norm = (float)sqrt(x * x + y * y);

        if (norm == 0.0)
        {
            printf("\n\nNormalize::Divisao por zero");
            v.x = 1;
            v.y = 1;
        }
        else
        {
            v.x /= norm;
            v.y /= norm;
        }

        return v;
    }

    float magnitude()
    {
        return sqrt(pow(x, 2) + pow(y, 2));
    }

    // operator overloads
    Vector2 operator - (const Vector2& v)
    {
        Vector2 aux(x - v.x, y - v.y);
        return(aux);
    }

    Vector2 operator + (const Vector2& v)
    {
        Vector2 aux(x + v.x, y + v.y);
        return(aux);
    }

    Vector2 operator * (const Vector2& v)
    {
        Vector2 aux(x * v.x, y * v.y);
        return(aux);
    }

    bool operator==(const Vector2& v) const
    {
        return (x == v.x && y == v.y);
    }

    Vector2 operator*(float value)
    {
        return Vector2(x * value, y * value);
    }

    // my funcs
    float dotProduct(Vector2 v)
    {
        float val = x * v.x + y * v.y;
        val /= magnitude() * v.magnitude();
        val = acos(val);

        // counter-clockwise
        if (y * v.x > x * v.y)
        {
            val = 2 * PI - val;
        }

        return val;
    }
};

#endif
