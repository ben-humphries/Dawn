#include "Texture.h"

#include "glad/glad.h"

namespace Dawn
{
    void Texture::bind()
    {
        if (m_textureHandle)
            glBindTexture(GL_TEXTURE_2D, m_textureHandle);
    }
    void Texture::loadFromImage(const Image& image)
    {
        //TODO: Check if texture exists already, and if so, delete it before overwriting.
        glGenTextures(1, &m_textureHandle);
        bind();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getDataPtr());
        glGenerateMipmap(GL_TEXTURE_2D);

        m_width = image.getWidth();
        m_height = image.getHeight();
    }
    void Texture::loadFromFile(const std::string& path)
    {
        Image image = Image(path);
        loadFromImage(image);

        m_width = image.getWidth();
        m_height = image.getHeight();
    }
}