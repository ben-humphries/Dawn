#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace Dawn
{
    Image::Image()
    {
    }
    Image::Image(int width, int height)
        : m_width(width), m_height(height)
    {
        //Fill data with all white
    }

    Image::Image(const std::string& path)
    {
        loadFromFile(path);
    }

    Image::~Image()
    {
        stbi_image_free(m_data);
    }

    bool Image::loadFromFile(const std::string& path)
    {
        m_data = stbi_load(path.c_str(), &m_width, &m_height, &m_numChannels, 0);

        return m_data != nullptr;
    }

    void Image::setPixel(int x, int y, Vec4 color)
    {
    }

    Vec4 Image::getPixel(int x, int y)
    {
        return Vec4();
    }
}