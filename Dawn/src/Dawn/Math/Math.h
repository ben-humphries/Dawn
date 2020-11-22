#pragma once

namespace Dawn
{
    //TODO: tell compiler never to insert padding so that types are consistent with ImGui/other libraries.
    //      Note that this may have poor cache implications so more research needs to be done first.
    struct Vec2 {
        float x;
        float y;

        Vec2();
        Vec2(float value);
        Vec2(float xv, float yv);

        Vec2 operator+(const Vec2& v) const;
        Vec2 operator-(const Vec2& v) const;
        Vec2 operator*(const Vec2& v) const;
        Vec2 operator/(const Vec2& v) const;
    };

    struct Vec3 {
        float x;
        float y;
        float z;

        Vec3();
        Vec3(float value);
        Vec3(float xv, float yv, float zv);

        Vec3 operator+(const Vec3& v) const;
        Vec3 operator-(const Vec3& v) const;
        Vec3 operator*(const Vec3& v) const;
        Vec3 operator/(const Vec3& v) const;
    };

    struct Vec4 {
        float x;
        float y;
        float z;
        float w;

        Vec4();
        Vec4(float value);
        Vec4(float xv, float yv, float zv, float wv);

        Vec4 operator+(const Vec4& v) const;
        Vec4 operator-(const Vec4& v) const;
        Vec4 operator*(const Vec4& v) const;
        Vec4 operator/(const Vec4& v) const;
    };

    struct Mat4 {
        float values[16];

        Mat4();

        float Get(int x, int y) const;
        void Set(int x, int y, float val);
        float* getPtr();

        Mat4 operator*(const Mat4& m) const;
        Vec4 operator*(const Vec4& v) const;
    };

    //TODO: Maybe put these functions in a Math namespace?
    float Radians(float degrees);
    float Mod(float f, float m);

    float Dot(const Vec3& a, const Vec3& b);
    Vec3 Cross(const Vec3& a, const Vec3& b);

    Vec2 Noramlize(const Vec2& v);
    Vec3 Normalize(const Vec3& v);
    Vec4 Normalize(const Vec4& v);

    Mat4 LookAt(const Vec3& eye, const Vec3& center, const Vec3& up);
    Mat4 Perspective(float fov, float aspect, float near, float far);
    Mat4 GetTranslationMatrix(const Vec3& v);
    //TODO: make this use euler angles
    Mat4 GetRotationMatrix(const Vec3& axis, const float theta);
    Mat4 GetScaleMatrix(const Vec3& v);

    Mat4 GetModelMatrix(
        const Mat4& translationMatrix,
        const Mat4& rotationMatrix,
        const Mat4& scaleMatrix);
}