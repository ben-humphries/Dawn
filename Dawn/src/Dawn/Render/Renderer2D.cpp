#include "Renderer2D.h"

#include "glad/glad.h"

namespace Dawn
{
    struct Vertex {
        Vec3 position;
        Vec4 color;
        Vec2 texCoord;
        uint8_t texIndex;
    };

    const size_t MAX_QUADS = 1000;
    const size_t MAX_VERTICES = MAX_QUADS * 4;
    const size_t MAX_INDICES = MAX_QUADS * 6;

    const size_t MAX_TEXTURES = 16;  //Should be dependent on GPU's number of texture slots

    uint32_t vbo;
    uint32_t vao;
    uint32_t ebo;
    uint32_t shaderProgram;

    Vertex* vertices;
    Vertex* currentVertexPtr = vertices;

    uint32_t* indices;

    Vec2 texCoords[4];

    Vec3 quadVertexPositions[4] = {
        Vec3(0.5f, 0.5f, 0.0f),
        Vec3(0.5f, -0.5f, 0.0f),
        Vec3(-0.5f, -0.5f, 0.0f),
        Vec3(-0.5f, 0.5f, 0.0f)};

    Texture* currentBatchTextureArray[MAX_TEXTURES];

    size_t currentBatchQuads = 0;
    size_t currentBatchTextures = 1;  //First texture is reserved for no texture
    size_t currentBatches = 0;

    void Renderer2D::Init()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //glEnable(GL_DEPTH_TEST);

        //Shader Compilation

        const char* vertexShaderSource =
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "layout (location = 1) in vec4 aColor;\n"
            "layout (location = 2) in vec2 aTexCoord;\n"
            "layout (location = 3) in float aTexIndex;\n"

            "out vec4 color;\n"
            "out vec2 texCoord;\n"
            "out float texIndex;\n"

            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "   color = aColor;\n"
            "   texCoord = aTexCoord;\n"
            "   texIndex = aTexIndex;\n"

            "}\0";

        const char* fragmentShaderSource =
            "#version 330 core \n"

            "out vec4 FragColor;\n"

            "in vec4 color;\n"
            "in vec2 texCoord;\n"
            "in float texIndex;\n"

            "uniform sampler2D inputTextures[16];\n"
            "void main()\n"
            "{\n"
            "   int index = int(texIndex);\n"
            "   if (index == 0) {\n"
            "       FragColor = color;\n"
            "   }\n"
            "   else {\n"
            "       FragColor = color * texture(inputTextures[index], texCoord);\n"
            "   }\n"
            "}\0";

        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        //Initialize vertices
        vertices = new Vertex[MAX_VERTICES];

        //Initialize indices
        indices = new uint32_t[MAX_INDICES];

        int offset = 0;
        for (int i = 0; i < MAX_INDICES; i += 6) {
            indices[i + 0] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 3;

            indices[i + 3] = offset + 1;
            indices[i + 4] = offset + 2;
            indices[i + 5] = offset + 3;

            offset += 4;
        }

        //Initialize texCoords
        texCoords[0] = Vec2(1.0f, 0.0f);
        texCoords[1] = Vec2(1.0f, 1.0f);
        texCoords[2] = Vec2(0.0f, 1.0f);
        texCoords[3] = Vec2(0.0f, 0.0f);

        //Initialize array object
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        //Initialize vertex buffer object
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * MAX_VERTICES, vertices, GL_DYNAMIC_DRAW);

        //Initialize index buffer object
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * MAX_INDICES, indices, GL_STATIC_DRAW);

        //Set Buffer Layout
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(Vec3)));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(Vec3) + sizeof(Vec4)));

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 1, GL_UNSIGNED_BYTE, false, sizeof(Vertex), (void*)(sizeof(Vec3) + sizeof(Vec4) + sizeof(Vec2)));

        //Initialize texture array
        for (int i = 0; i < MAX_TEXTURES; i++) {
            currentBatchTextureArray[i] = nullptr;
        }
    }

    void Renderer2D::Terminate()
    {
        delete[] vertices;
        delete[] indices;
        glDeleteProgram(shaderProgram);
    }

    void Renderer2D::StartFrame()
    {
        currentVertexPtr = vertices;
    }

    void Renderer2D::Flush()
    {
        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * MAX_VERTICES, vertices);

        glUseProgram(shaderProgram);

        for (int i = 1; i < currentBatchTextures; i++) {
            glActiveTexture(GL_TEXTURE0 + i);
            currentBatchTextureArray[i]->bind();
        }
        glActiveTexture(GL_TEXTURE0);

        GLint location = glGetUniformLocation(shaderProgram, "inputTextures");
        int* samplers = new int[MAX_TEXTURES];
        for (int i = 0; i < MAX_TEXTURES; i++) {
            samplers[i] = i;
        }
        glUniform1iv(location, MAX_TEXTURES, samplers);

        delete[] samplers;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

        //TODO: Once there is benchmarking, see if using the actual number vs. the MAX_INDICES makes a difference
        glDrawElements(GL_TRIANGLES, currentBatchQuads * 6, GL_UNSIGNED_INT, 0);

        currentBatchQuads = 0;
        currentBatchTextures = 1;
        currentVertexPtr = vertices;
        currentBatches++;
    }

    void Renderer2D::EndFrame()
    {
        Flush();
        currentBatches = 0;
    }

    void Renderer2D::DrawQuad(Vec3 position, float rotation, Vec3 scale, Vec4 color, Texture* texture)
    {
        Mat4 translationMatrix = GetTranslationMatrix(position);
        Mat4 rotationMatrix = GetRotationMatrix(Vec3(0, 0, -1), rotation);
        Mat4 scaleMatrix = GetScaleMatrix(scale);

        Mat4 modelMatrix = GetModelMatrix(translationMatrix, rotationMatrix, scaleMatrix);

        int texIndex;
        bool alreadyLoaded = false;
        if (!texture)
            texIndex = 0;
        else {
            //Check if texture is already in the array
            for (int i = 0; i < MAX_TEXTURES; i++) {
                if (currentBatchTextureArray[i] == texture) {
                    texIndex = i;
                    alreadyLoaded = true;
                    break;
                }
            }

            if (!alreadyLoaded) {
                texIndex = currentBatchTextures;
                currentBatchTextureArray[currentBatchTextures++] = texture;
            }
        }

        for (int i = 0; i < 4; i++) {
            Vec4 vPosition = Vec4(quadVertexPositions[i].x, quadVertexPositions[i].y, quadVertexPositions[i].z, 1);
            vPosition = modelMatrix * vPosition;
            currentVertexPtr->position = Vec3(vPosition.x, vPosition.y, vPosition.z);
            currentVertexPtr->color = color;
            currentVertexPtr->texCoord = texCoords[i];
            currentVertexPtr->texIndex = texIndex;

            currentVertexPtr++;
        }
        currentBatchQuads++;

        if (currentBatchQuads >= MAX_QUADS || currentBatchTextures >= MAX_TEXTURES)
            Flush();
    }
}  // namespace Dawn