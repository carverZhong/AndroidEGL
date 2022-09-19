#include "triangle_renderer.h"
#include "logcat.h"

TriangleRenderer::TriangleRenderer() {
    // vertex shader
    auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSrc_, NULL);
    glCompileShader(vertexShader);
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        LogE("vertexShader compile error! \n=%s", infoLog);
    }
    // fragment shader
    auto fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragmentSrc_, NULL);
    glCompileShader(fragShader);
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        LogE("fragShader compile error! \n%s", infoLog);
    }
    // link shaders
    shaderProgram_ = glCreateProgram();
    glAttachShader(shaderProgram_, vertexShader);
    glAttachShader(shaderProgram_, fragShader);
    glLinkProgram(shaderProgram_);
    glGetProgramiv(shaderProgram_, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram_, 512, NULL, infoLog);
        LogE("link program error! \n%s", infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);

    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
    };
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    glBindVertexArray(vao_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TriangleRenderer::OnDraw() const {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram_);
    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

TriangleRenderer::~TriangleRenderer() {
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
    glDeleteProgram(shaderProgram_);
}