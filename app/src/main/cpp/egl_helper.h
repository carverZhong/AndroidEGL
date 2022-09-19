#ifndef ANDROIDEGL_EGL_HELPER_H
#define ANDROIDEGL_EGL_HELPER_H

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>
#include <GLES/gl.h>

// 参考 GLSurfaceView.EglHelper
// 用于创建 EGL 环境
class EGLHelper {
public:
    void Init();
    bool IsReadyToDraw() const;
    void CreateSurface(ANativeWindow *window);
    void SwapBuffers();
    void DestroySurface();
    void GetSize(int &width, int &height);
    void Release();

private:
    EGLDisplay eglDisplay_;
    EGLSurface eglSurface_;
    EGLContext eglContext_;
    EGLConfig eglConfig_;
    ANativeWindow *window_;
    bool isReadyToDraw = false;
};


#endif //ANDROIDEGL_EGL_HELPER_H
