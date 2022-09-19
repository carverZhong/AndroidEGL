#ifndef ANDROIDEGL_NATIVE_RENDERER_H
#define ANDROIDEGL_NATIVE_RENDERER_H

#include <memory>
#include "egl_helper.h"
#include "triangle_renderer.h"

class NativeRenderer {
public:
    NativeRenderer();
    void OnSurfaceCreate(ANativeWindow *window);
    void OnSurfaceDestroy();
    void DoFrame();

private:
    std::unique_ptr<EGLHelper> eglHelper_;
    TriangleRenderer *triangleRenderer_;
};



#endif //ANDROIDEGL_NATIVE_RENDERER_H
