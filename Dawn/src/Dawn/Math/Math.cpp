#include "Math.h"

#include <math.h>

namespace Dawn
{
    /////VEC2/////
    Vec2::Vec2()
    {
        x = 0;
        y = 0;
    }

    Vec2::Vec2(float value)
    {
        x = value;
        y = value;
    }

    Vec2::Vec2(float xv, float yv)
    {
        x = xv;
        y = yv;
    }

    Vec2 Vec2::operator+(const Vec2& v) const
    {
        return Vec2(
            this->x + v.x,
            this->y + v.y);
    }

    Vec2 Vec2::operator-(const Vec2& v) const
    {
        return Vec2(
            this->x - v.x,
            this->y - v.y);
    }

    Vec2 Vec2::operator*(const Vec2& v) const
    {
        return Vec2(
            this->x * v.x,
            this->y * v.y);
    }

    Vec2 Vec2::operator/(const Vec2& v) const
    {
        return Vec2(
            this->x / v.x,
            this->y / v.y);
    }

    /////VEC3/////

    Vec3::Vec3()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    Vec3::Vec3(float value)
    {
        x = value;
        y = value;
        z = value;
    }

    Vec3::Vec3(float xv, float yv, float zv)
    {
        x = xv;
        y = yv;
        z = zv;
    }

    Vec3 Vec3::operator+(const Vec3& v) const
    {
        return Vec3(
            this->x + v.x,
            this->y + v.y,
            this->z + v.z);
    }

    Vec3 Vec3::operator-(const Vec3& v) const
    {
        return Vec3(
            this->x - v.x,
            this->y - v.y,
            this->z - v.z);
    }

    Vec3 Vec3::operator*(const Vec3& v) const
    {
        return Vec3(
            this->x * v.x,
            this->y * v.y,
            this->z * v.z);
    }

    Vec3 Vec3::operator/(const Vec3& v) const
    {
        return Vec3(
            this->x / v.x,
            this->y / v.y,
            this->z / v.z);
    }

    /////VEC4/////

    Vec4::Vec4()
    {
        x = 0;
        y = 0;
        z = 0;
        w = 0;
    }

    Vec4::Vec4(float value)
    {
        x = value;
        y = value;
        z = value;
        w = value;
    }

    Vec4::Vec4(float xv, float yv, float zv, float wv)
    {
        x = xv;
        y = yv;
        z = zv;
        w = wv;
    }

    Vec4 Vec4::operator+(const Vec4& v) const
    {
        return Vec4(
            this->x + v.x,
            this->y + v.y,
            this->z + v.z,
            this->w + v.w);
    }

    Vec4 Vec4::operator-(const Vec4& v) const
    {
        return Vec4(
            this->x - v.x,
            this->y - v.y,
            this->z - v.z,
            this->w - v.w);
    }

    Vec4 Vec4::operator*(const Vec4& v) const
    {
        return Vec4(
            this->x * v.x,
            this->y * v.y,
            this->z * v.z,
            this->w * v.w);
    }

    Vec4 Vec4::operator/(const Vec4& v) const
    {
        return Vec4(
            this->x / v.x,
            this->y / v.y,
            this->z / v.z,
            this->w / v.w);
    }

    /////MAT4/////

    Mat4::Mat4()
    {
        for (int i = 0; i < 16; i++) {
            values[i] = 0;
        }

        values[0] = 1;
        values[5] = 1;
        values[10] = 1;
        values[15] = 1;
    }

    float Mat4::Get(int x, int y)
    {
        return values[y + 4 * x];
    }

    void Mat4::Set(int x, int y, float val)
    {
        values[y + 4 * x] = val;
    }

    float* Mat4::getPtr()
    {
        return values;
    }

    Mat4 Mat4::operator*(Mat4 m)
    {
        Mat4 f = Mat4();

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                float sum = 0.0f;
                for (int k = 0; k < 4; k++) {
                    sum += this->Get(k, j) * m.Get(i, k);
                }

                f.Set(i, j, sum);
            }
        }

        return f;
    }

    Vec4 Mat4::operator*(Vec4 v)
    {
        float x = this->Get(0, 0) * v.x + this->Get(1, 0) * v.y + this->Get(2, 0) * v.z + this->Get(3, 0) * v.w;
        float y = this->Get(0, 1) * v.x + this->Get(1, 1) * v.y + this->Get(2, 1) * v.z + this->Get(3, 1) * v.w;
        float z = this->Get(0, 2) * v.x + this->Get(1, 2) * v.y + this->Get(2, 2) * v.z + this->Get(3, 2) * v.w;
        float w = this->Get(0, 3) * v.x + this->Get(1, 3) * v.y + this->Get(2, 3) * v.z + this->Get(3, 3) * v.w;

        return Vec4(x, y, z, w);
    }

    //UTIL FUNCTIONS//

    float Radians(float degrees)
    {
        return degrees * 0.0174533f;
    }

    float Mod(float f, float m)
    {
        return fmodf(f, m);
    }
    float Dot(const Vec3& a, const Vec3& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    Vec3 Cross(const Vec3& a, const Vec3& b)
    {
        return Vec3(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x);
    }

    Vec2 Normalize(const Vec2& v)
    {
        return v / sqrt(v.x * v.x + v.y * v.y);
    }

    Vec3 Normalize(const Vec3& v)
    {
        return v / sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }

    Vec4 Normalize(const Vec4& v)
    {
        return v / sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
    }

    Mat4 LookAt(const Vec3& eye, const Vec3& center, const Vec3& up)
    {
        Mat4 m = Mat4();

        Vec3 x, y, z;

        z = Normalize(eye - center);
        x = Cross(up, z);
        y = Normalize(Cross(z, x));

        x = Normalize(x);

        m.Set(0, 0, x.x);
        m.Set(1, 0, x.y);
        m.Set(2, 0, x.z);
        m.Set(3, 0, -Dot(x, eye));

        m.Set(0, 1, y.x);
        m.Set(1, 1, y.y);
        m.Set(2, 1, y.z);
        m.Set(3, 1, -Dot(y, eye));

        m.Set(0, 2, z.x);
        m.Set(1, 2, z.y);
        m.Set(2, 2, z.z);
        m.Set(3, 2, -Dot(z, eye));

        return m;
    }

    Mat4 Perspective(float fov, float aspect, float near, float far)
    {
        Mat4 m = Mat4();

        float f = 1 / tan(fov / 2);

        m.Set(0, 0, f / aspect);
        m.Set(1, 1, f);
        m.Set(2, 2, (far + near) / (near - far));
        m.Set(3, 2, (2 * far * near) / (near - far));
        m.Set(2, 3, -1);
        m.Set(3, 3, 0);

        return m;
    }

    Mat4 GetTranslationMatrix(const Vec3& v)
    {
        Mat4 m = Mat4();
        m.Set(3, 0, v.x);
        m.Set(3, 1, v.y);
        m.Set(3, 2, v.z);

        return m;
    }

    Mat4 GetRotationMatrix(const Vec3& axis, const float theta)
    {
        //https://en.wikipedia.org/wiki/Rotation_matrix#Basic_rotations
        Mat4 m = Mat4();

        float costheta = cos(theta);
        float sintheta = sin(theta);

        m.Set(0, 0, costheta + axis.x * axis.x * (1 - costheta));
        m.Set(1, 0, axis.x * axis.y * (1 - costheta) - axis.z * sintheta);
        m.Set(2, 0, axis.x * axis.z * (1 - costheta) + axis.y * sintheta);
        m.Set(0, 1, axis.y * axis.x * (1 - costheta) + axis.z * sintheta);
        m.Set(1, 1, costheta + axis.y * axis.y * (1 - costheta));
        m.Set(2, 1, axis.y * axis.z * (1 - costheta) - axis.x * sintheta);
        m.Set(0, 2, axis.z * axis.x * (1 - costheta) - axis.y * sintheta);
        m.Set(1, 2, axis.z * axis.y * (1 - costheta) + axis.x * sintheta);
        m.Set(2, 2, costheta + axis.z * axis.z * (1 - costheta));

        return m;
    }

    Mat4 GetScaleMatrix(const Vec3& v)
    {
        Mat4 m = Mat4();

        m.Set(0, 0, v.x);
        m.Set(1, 1, v.y);
        m.Set(2, 2, v.z);

        return m;
    }

    Mat4 GetModelMatrix(
        Mat4& translation_matrix,
        Mat4& rotation_matrix,
        Mat4& scale_matrix)
    {
        return translation_matrix * rotation_matrix * scale_matrix;
    }
}