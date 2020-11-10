// clang-format off
#define GLEW_STATIC
#include "GL/glew.h"
// clang-format on

#include "Dawn/Application.h"
#include "Dawn/Event.h"
#include "Dawn/Log.h"
#include "Dawn/Window.h"
#include "Dawn/Input.h"

void test(const Dawn::Event& e)
{
    DAWN_LOG(e.toString());
}

void test_keycodes(const Dawn::Event& e)
{
    auto e_k = (const Dawn::KeyPressedEvent&)e;
    if (e_k.getKeyCode() == Dawn::KeyCode::A) {
        DAWN_LOG("Key A was pressed");
    }
}

class Playground : public Dawn::Application
{
   public:
    float vertices[18] =
        {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        };

    unsigned int vao;
    unsigned int vbo;
    unsigned int shaderProgram;

    Playground()
    {
        //Register Event Callbacks
        Dawn::EventHandler::Listen(Dawn::EventType::WindowClosed, test);
        Dawn::EventHandler::Listen(Dawn::EventType::WindowResized, test);
        Dawn::EventHandler::Listen(Dawn::EventType::WindowMoved, test);
        Dawn::EventHandler::Listen(Dawn::EventType::KeyPressed, test);
        Dawn::EventHandler::Listen(Dawn::EventType::KeyReleased, test);
        Dawn::EventHandler::Listen(Dawn::EventType::MouseMoved, test);
        Dawn::EventHandler::Listen(Dawn::EventType::MousePressed, test);
        Dawn::EventHandler::Listen(Dawn::EventType::MouseReleased, test);
        Dawn::EventHandler::Listen(Dawn::EventType::MouseScrolled, test);

        Dawn::EventHandler::Listen(Dawn::EventType::KeyPressed, test_keycodes);

        //Triangle Code
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)(3 * sizeof(float)));

        const char* vertexShaderSource =
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "layout (location = 1) in vec3 aColor;\n"
            "out vec3 color;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "   color = aColor;\n"
            "}\0";

        const char* fragmentShaderSource =
            "#version 330 core \n"
            "out vec4 FragColor;\n"
            "in vec3 color;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(color, 1.0f);\n"
            "}\0";

        unsigned int vertex_shader;
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertex_shader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertex_shader);

        {
            int success;
            glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

            if (!success) DAWN_LOG("vertex shader compilation failed");
        }

        unsigned int fragment_shader;
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(fragment_shader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragment_shader);

        {
            int success;
            glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

            if (!success) DAWN_LOG("fragment shader compilation failed");
        }

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertex_shader);
        glAttachShader(shaderProgram, fragment_shader);
        glLinkProgram(shaderProgram);

        {
            int success;
            char infoLog[512];
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

            if (!success) {
                glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
                DAWN_LOG("shader linking failed, ", infoLog);
            }
        }

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }

    void onUpdate() override
    {
        if (Dawn::Input::GetKeyDown(Dawn::KeyCode::B)) {
            DAWN_LOG("B is being pressed");
        }
        if (Dawn::Input::GetMouseButtonDown(Dawn::MouseCode::Middle)) {
            DAWN_LOG("Middle MB being pressed");
        }

        glClearColor(0.5, 0.3, 0.6, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void onClose() override
    {
    }
};

int main()
{
    Playground playground = Playground();
    playground.start();

    return 0;
}