#include "native_renderer.h"
#include "logcat.h"
#include <GLES3/gl3.h>

NativeRenderer::NativeRenderer() {
    eglHelper_ = std::make_unique<EGLHelper>();
}

void NativeRenderer::OnSurfaceCreate(ANativeWindow *window) {
    eglHelper_->Init();
    eglHelper_->CreateSurface(window);
    if (eglHelper_->IsReadyToDraw()) {
        int w, h;
        eglHelper_->GetSize(w, h);
        glViewport(0, 0, w, h);
        triangleRenderer_ = new TriangleRenderer();
    }
}

void NativeRenderer::OnSurfaceDestroy() {
    delete triangleRenderer_;
    eglHelper_->DestroySurface();
    eglHelper_->Release();
}

void NativeRenderer::DoFrame() {
    if (eglHelper_->IsReadyToDraw()) {
        if (triangleRenderer_) {
            triangleRenderer_->OnDraw();
        }
        eglHelper_->SwapBuffers();
    }
}