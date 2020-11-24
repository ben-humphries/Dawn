#pragma once

#include <string>
#include "Math/Math.h"

namespace Dawn
{
    //TODO: Incomplete. Support images not loaded from a file
    class Image
    {
       public:
        Image();
        Image(int width, int height);
        Image(const std::string& path);

        ~Image();

        bool loadFromFile(const std::string& path);

        void setPixel(int x, int y, Vec4 color);
        Vec4 getPixel(int x, int y);

        int getWidth() const
        {
            return m_width;
        }
        int getHeight() const
        {
            return m_height;
        }

        uint8_t* getDataPtr() const
        {
            return m_data;
        }

       private:
        int m_width, m_height;
        int m_numChannels;
        uint8_t* m_data = nullptr;
    };
}