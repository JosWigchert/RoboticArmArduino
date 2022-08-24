#pragma once

struct Point3D : Printable
{
    float x;
    float y;
    float z;

    float length()
    {
        return sqrt(x * x + y * y + z * z);
    }

    float distance(Point3D point)
    {
        return sqrt(x - point.x * x - point.x + y - point.y * y - point.y + z - point.z * z - point.z);
    }

    #pragma region Point3D Operators

    Point3D operator+(const Point3D& point) const
    {
        Point3D result;

        result.x += point.x;
        result.y += point.y;
        result.z += point.z;

        return result;
    }

    Point3D operator-(const Point3D& point) const
    {
        Point3D result;

        result.x -= point.x;
        result.y -= point.y;
        result.z -= point.z;

        return result;
    }

    Point3D operator*(const Point3D& point) const
    {
        Point3D result;

        result.x *= point.x;
        result.y *= point.y;
        result.z *= point.z;

        return result;       
    }

    Point3D operator/(const Point3D& point) const
    {
        Point3D result;

        result.x /= point.x;
        result.y /= point.y;
        result.z /= point.z;

        return result;       
    }

    #pragma endregion Point3D Operators

    #pragma region Float Operators

    Point3D operator+(const float val) const
    {
        Point3D result;

        result.x += val;
        result.y += val;
        result.z += val;

        return result;
    }

    Point3D operator-(const float val) const
    {
        Point3D result;

        result.x -= val;
        result.y -= val;
        result.z -= val;

        return result;
    }

    Point3D operator*(const float val) const
    {
        Point3D result;

        result.x *= val;
        result.y *= val;
        result.z *= val;

        return result;       
    }

    Point3D operator/(const float val) const
    {
        Point3D result;

        result.x /= val;
        result.y /= val;
        result.z /= val;

        return result;       
    }

    #pragma endregion Float Operators

    size_t printTo(Print& p) const 
    {
        size_t r = 0;

        r += p.print("x: ");
        r += p.print(x);
        r += p.print(" y: ");
        r += p.print(y);
        r += p.print(" z: ");
        r += p.print(z);
        return r;
    }
};
