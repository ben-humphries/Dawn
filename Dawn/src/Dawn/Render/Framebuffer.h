#pragma once
#include "DawnPCH.h"

namespace Dawn
{
    class Framebuffer
    {
       public:
        Framebuffer(size_t width, size_t height);
        ~Framebuffer();

        void bind();
        void unbind();

        uint32_t getFrameBufferHandle()
        {
            return m_framebufferHandle;
        }

        uint32_t getColorTextureHandle()
        {
            return m_colorTextureHandle;
        }

        uint32_t getDepthStencilTextureHandle()
        {
            return m_depthStencilTextureHandle;
        }

       private:
        uint32_t m_framebufferHandle;
        uint32_t m_colorTextureHandle;
        uint32_t m_depthStencilTextureHandle;

        size_t m_width, m_height;
    };
}