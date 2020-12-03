#pragma once
#include "DawnPCH.h"

#include "Math/Math.h"

namespace Dawn
{
    class Camera
    {
    };

    class OrthographicCamera : public Camera
    {
       public:
        OrthographicCamera(float left, float right, float bot, float top);

        void setPosition(const Vec3& position)
        {
            m_position = position;
            recalculateMatrices();
        }

        void setRotation(float rotation)
        {
            m_rotation = rotation;
            recalculateMatrices();
        }

        void setProjection(float left, float right, float bot, float top);

        const Mat4& getViewMatrix() const
        {
            return m_viewMatrix;
        }

        const Mat4& getProjectionMatrix() const
        {
            return m_projectionMatrix;
        }

        const Mat4& getViewProjectionMatrix() const
        {
            return m_viewProjectionMatrix;
        }

       private:
        void recalculateMatrices();

        Mat4 m_viewMatrix;
        Mat4 m_projectionMatrix;
        Mat4 m_viewProjectionMatrix;

        Vec3 m_position;
        float m_rotation;
    };

    class PerspectiveCamera : public Camera
    {
    };
}