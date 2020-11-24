#pragma once

#include "Render/Image.h"
#include <string>

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