#include <jni.h>
#include <android/native_window_jni.h>
#include "native_renderer.h"

extern "C"
JNIEXPORT jlong JNICALL
Java_com_github_carver_androidegl_egl_NativeRenderer_nCreateNativeRenderer(JNIEnv *env,
                                                                           jobject thiz) {
    auto ptr = new NativeRenderer();
    return reinterpret_cast<long>(ptr);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_github_carver_androidegl_egl_NativeRenderer_nSurfaceCreate(JNIEnv *env,
                                                                    jobject thiz,
                                                                    jlong native_ptr,
                                                                    jobject surface) {
    auto ptr = reinterpret_cast<NativeRenderer*>(native_ptr);
    if (ptr) {
        ANativeWindow *window = ANativeWindow_fromSurface(env, surface);
        ptr->OnSurfaceCreate(window);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_github_carver_androidegl_egl_NativeRenderer_nSurfaceDestroy(JNIEnv *env, jobject thiz,
                                                                     jlong native_ptr) {
    auto ptr = reinterpret_cast<NativeRenderer*>(native_ptr);
    if (ptr) {
        ptr->OnSurfaceDestroy();
        delete ptr;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_github_carver_androidegl_egl_NativeRenderer_nDoFrame(JNIEnv *env, jobject thiz,
                                                              jlong native_ptr) {
    auto ptr = reinterpret_cast<NativeRenderer*>(native_ptr);
    if (ptr) {
        ptr->DoFrame();
    }
}