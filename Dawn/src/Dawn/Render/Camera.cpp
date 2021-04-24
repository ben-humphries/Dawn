#include "Camera.h"

namespace Dawn
{
    OrthographicCamera::OrthographicCamera(float aspectRatio, float size)
        : m_position(0, 0, 0), m_rotation(0)
    {
        m_viewMatrix = Mat4();
        m_aspectRatio = aspectRatio;
        m_size = size;
        setProjection(-m_aspectRatio * m_size, m_aspectRatio * m_size, -1.0 * m_size, 1.0 * m_size);
    }

    void OrthographicCamera::setProjection(float left, float right, float bot, float top)
    {
        m_projectionMatrix = Ortho(left, right, bot, top, -1.0f, 1000.0f);
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }

    void OrthographicCamera::recalculateMatrices()
    {
        //m_viewMatrix = LookAt(m_position, Vec3(m_position.x, m_position.y, 1), Vec3(0, 1, 0));

        Mat4 translation = GetTranslationMatrix(Vec3(-m_position.x, -m_position.y, -m_position.z));
        Mat4 rotation = GetRotationMatrix(Vec3(0, 0, 1), -m_rotation);

        m_viewMatrix = rotation * translation;
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }
}  // namespace Dawn