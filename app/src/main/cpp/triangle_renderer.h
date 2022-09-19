#ifndef ANDROIDEGL_TRIANGLE_RENDERER_H
#define ANDROIDEGL_TRIANGLE_RENDERER_H

#include <GLES3/gl3.h>

// 绘制一个三角形
class TriangleRenderer {
public:
    TriangleRenderer();
    ~TriangleRenderer();
    void OnDraw() const;

private:
    GLuint vbo_, vao_;
    GLuint shaderProgram_;
    const char *vertexSrc_ = "#version 300 es\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    const char *fragmentSrc_ = "#version 300 es\n"
                                       "precision mediump float;\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\n\0";
};


#endif //ANDROIDEGL_TRIANGLE_RENDERER_H
