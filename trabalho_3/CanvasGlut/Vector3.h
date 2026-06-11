#ifndef __VECTOR_3_H__
#define __VECTOR_3_H__

#include <array>
#include <compare>
#include <cmath>
#include <cstdio>

#define PI 3.14159265359f

class Vector3
{
public:
    float x, y, z;

    Vector3()
    {
        x = y = z = 0;
    }

    Vector3(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    void set(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    Vector3 normalize()
    {
        Vector3 v = Vector3(x, y, z);

        float norm = (float)sqrt(x * x + y * y + z * z);

        if (norm == 0.0)
        {
            printf("\n\nNormalize::Divisao por zero");
            v.x = 1;
            v.y = 1;
            v.z = 1;
        }
        else
        {
            v.x /= norm;
            v.y /= norm;
            v.z /= norm;
        }

        return v;
    }

    float magnitude()
    {
        return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    }

    // operator overloads
    Vector3 operator - (const Vector3& v)
    {
        Vector3 aux(x - v.x, y - v.y, z - v.z);
        return(aux);
    }

    Vector3 operator + (const Vector3& v)
    {
        Vector3 aux(x + v.x, y + v.y, z + v.z);
        return(aux);
    }

    Vector3 operator * (const Vector3& v)
    {
        Vector3 aux(x * v.x, y * v.y, z * v.z);
        return(aux);
    }

    bool operator==(const Vector3& v) const
    {
        return (x == v.x && y == v.y && z == v.z);
    }

    Vector3 operator*(float value)
    {
        return Vector3(x * value, y * value, z * value);
    }

    // my funcs
    float dotProduct(Vector3 v)
    {
        // Calculates the dot product
        float val = x * v.x + y * v.y + z * v.z;

        // Turns it into the angle in radians
        val /= (magnitude() * v.magnitude());

        // Clamp to prevent NaN from acos due to floating point inaccuracies
        if (val < -1.0f) val = -1.0f;
        if (val > 1.0f) val = 1.0f;

        val = acos(val);

        return val;
    }

    float dot(Vector3 v)
    {
        float val = x * v.x + y * v.y + z * v.z;
        return val;
    }

    Vector3 crossProduct(const Vector3& v)
    {
        return Vector3(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
    }
};

#endif