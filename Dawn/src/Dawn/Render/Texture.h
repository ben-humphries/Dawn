#pragma once
#include "DawnPCH.h"

#include "Render/Image.h"

namespace Dawn
{
    class Texture
    {
       public:
        void bind();
        void loadFromImage(const Image& image);
        void loadFromFile(const std::string& path);

       private:
        uint32_t m_textureHandle;
    };
}