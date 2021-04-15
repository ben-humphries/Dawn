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
        OrthographicCamera(float aspectRatio, float size);

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

        void setSize(float size)
        {
            m_size = size;
            setProjection(-m_aspectRatio * m_size, m_aspectRatio * m_size, -1.0 * m_size, 1.0 * m_size);
        }
        void setAspectRatio(float aspectRatio)
        {
            m_aspectRatio = aspectRatio;
            setProjection(-m_aspectRatio * m_size, m_aspectRatio * m_size, -1.0 * m_size, 1.0 * m_size);
        }

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
        void setProjection(float left, float right, float bot, float top);

        Mat4 m_viewMatrix;
        Mat4 m_projectionMatrix;
        Mat4 m_viewProjectionMatrix;

        Vec3 m_position;
        float m_rotation;

        float m_aspectRatio;
        float m_size;
    };

    class PerspectiveCamera : public Camera
    {
    };
}