#pragma once
#include "DawnPCH.h"

#include "Render/Image.h"

namespace Dawn
{
    class Texture
    {
       public:
        //TODO: Add constructors

        void bind();
        void loadFromImage(const Image& image);
        void loadFromFile(const std::string& path);

        int getWidth() const
        {
            return m_width;
        }

        int getHeight() const
        {
            return m_height;
        }

        uint32_t getTextureHandle() const
        {
            return m_textureHandle;
        }

       private:
        uint32_t m_textureHandle;

        int m_width, m_height;
    };
}