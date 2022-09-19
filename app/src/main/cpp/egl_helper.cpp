#include <android/native_window_jni.h>

#include "egl_helper.h"
#include "logcat.h"

void EGLHelper::Init() {
    // 获取 EGLDisplay 对象，建立与本地窗口系统的连接
    eglDisplay_ = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    EGLint version[2];
    // 初始化 EGL
    if (!eglInitialize(eglDisplay_, &version[0], &version[1])) {
        LogE("eglInitialize failed, error=%d", eglGetError());
        return;
    }

    const EGLint attrList[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            EGL_DEPTH_SIZE, 16,
            EGL_STENCIL_SIZE, 8,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT_KHR,
            EGL_NONE
    };
    EGLint num_config;
    // 确定配置信息
    if (!eglChooseConfig(eglDisplay_, attrList, &eglConfig_, 1, &num_config)) {
        LogE("eglChooseConfig failed, error=%d", eglGetError());
    }

    const EGLint contextAttrList[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
    eglContext_ = eglCreateContext(eglDisplay_, eglConfig_, nullptr, contextAttrList);
}

bool EGLHelper::IsReadyToDraw() const {
    return isReadyToDraw;
}

void EGLHelper::SwapBuffers() {
    // 交换缓冲，将绘制内容显示到屏幕上。
    if (!eglSwapBuffers(eglDisplay_, eglSurface_)) {
        LogE("eglSwapBuffers failed, code=%d", eglGetError());
    }
}

void EGLHelper::CreateSurface(ANativeWindow *window) {
    window_ = window;
    // 创建渲染表面 EGLSurface，创建屏幕上渲染区域
    eglSurface_ = eglCreateWindowSurface(eglDisplay_, eglConfig_, window, nullptr);
    // 绑定上下文
    if (!eglMakeCurrent(eglDisplay_, eglSurface_, eglSurface_, eglContext_)) {
        LogE("eglMakeCurrent failed, code=%d", eglGetError());
        isReadyToDraw = false;
    } else {
        isReadyToDraw = true;
    }
}

// 释放 EGLSurface
void EGLHelper::DestroySurface() {
    if (window_) {
        ANativeWindow_release(window_);
    }
    eglMakeCurrent(eglDisplay_, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

    //销毁surface
    if (eglSurface_ != EGL_NO_SURFACE) {
        eglDestroySurface(eglDisplay_, eglSurface_);
        eglSurface_ = EGL_NO_SURFACE;
    }
}

void EGLHelper::GetSize(int &width, int &height) {
    int w, h;
    eglQuerySurface(eglDisplay_, eglSurface_, EGL_WIDTH, &w);
    eglQuerySurface(eglDisplay_, eglSurface_, EGL_HEIGHT, &h);
    width = w;
    height = h;
}

// 释放 EGLContext 和 EGLDisplay
void EGLHelper::Release() {
    if (eglContext_ != EGL_NO_CONTEXT) {
        eglDestroyContext(eglDisplay_, eglContext_);
        eglContext_ = EGL_NO_CONTEXT;
    }
    if (eglDisplay_ != EGL_NO_DISPLAY) {
        eglTerminate(eglDisplay_);
        eglDisplay_ = EGL_NO_DISPLAY;
    }
}