#include "Framebuffer.h"

#include "glad/glad.h"

#include "Core/Log.h"

namespace Dawn
{
    Framebuffer::Framebuffer(size_t width, size_t height)
        : m_width(width), m_height(height)
    {
        //Framebuffer object
        glGenFramebuffers(1, &m_framebufferHandle);
        glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferHandle);

        //Color texture
        glGenTextures(1, &m_colorTextureHandle);
        glBindTexture(GL_TEXTURE_2D, m_colorTextureHandle);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorTextureHandle, 0);

        //Depth-Stencil texture
        glGenTextures(1, &m_depthStencilTextureHandle);
        glBindTexture(GL_TEXTURE_2D, m_depthStencilTextureHandle);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthStencilTextureHandle, 0);

        //Check creation succeeded
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            LOG("Error in framebuffer status!");
        LOG("All ok");
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    Framebuffer::~Framebuffer()
    {
        glDeleteFramebuffers(1, &m_framebufferHandle);
        glDeleteTextures(1, &m_colorTextureHandle);
        glDeleteTextures(1, &m_depthStencilTextureHandle);
    }

    void Framebuffer::bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferHandle);
    }

    void Framebuffer::unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}