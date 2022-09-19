package com.github.carver.androidegl.egl

import android.os.Handler
import android.os.HandlerThread
import android.os.Message
import android.view.Choreographer
import android.view.Surface
import android.view.SurfaceView
import android.view.TextureView
import java.lang.ref.WeakReference

class NativeRenderer: ISurfaceCallback, Choreographer.FrameCallback {

    private var nativePtr: Long = -1L
    private val glHandler: Handler
    private val glCallback = GLCallback(this)
    @Volatile
    private var isResume = false
    @Volatile
    private var isSurfaceReady = false


    init {
        val handlerThread = HandlerThread("gl-thread")
        handlerThread.start()
        glHandler = Handler(handlerThread.looper, glCallback)
    }

    override fun onSurfaceCreated(surface: Surface) {
        glHandler.sendMessage(Message.obtain().apply {
            what = MsgType.SURFACE_CREATE.ordinal
            obj = surface
        })
    }

    override fun onSurfaceDestroyed() {
        glHandler.sendMessage(Message.obtain().apply {
            what = MsgType.SURFACE_DESTROY.ordinal
        })
    }

    override fun doFrame(frameTimeNanos: Long) {
        glHandler.sendEmptyMessage(MsgType.DO_FRAME.ordinal)
        Choreographer.getInstance().postFrameCallback(this)
    }

    fun setView(surfaceView: SurfaceView) {
        glHandler.sendEmptyMessage(MsgType.INIT.ordinal)
        ISurfaceCallback.adapter(surfaceView, this)
    }

    fun setView(textureView: TextureView) {
        glHandler.sendEmptyMessage(MsgType.INIT.ordinal)
        ISurfaceCallback.adapter(textureView, this)
    }

    fun onResume() {
        isResume = true
        Choreographer.getInstance().postFrameCallback(this)
    }

    fun onPause() {
        isResume = false
        Choreographer.getInstance().removeFrameCallback(this)
    }

    private external fun nCreateNativeRenderer(): Long
    private external fun nSurfaceCreate(nativePtr: Long, surface: Surface)
    private external fun nSurfaceDestroy(nativePtr: Long)
    private external fun nDoFrame(nativePtr: Long)

    private class GLCallback(surface: NativeRenderer): Handler.Callback {

        private val weakSurfaceRef = WeakReference(surface)

        override fun handleMessage(msg: Message): Boolean {
            val surface = weakSurfaceRef.get() ?: return false
            when (msg.what) {
                MsgType.INIT.ordinal -> {
                    surface.nativePtr = surface.nCreateNativeRenderer()
                }
                MsgType.SURFACE_CREATE.ordinal -> {
                    surface.nSurfaceCreate(surface.nativePtr, msg.obj as Surface)
                    surface.isSurfaceReady = true
                }
                MsgType.SURFACE_DESTROY.ordinal -> {
                    surface.nSurfaceDestroy(surface.nativePtr)
                    surface.isSurfaceReady = true
                }
                MsgType.DO_FRAME.ordinal -> {
                    if (surface.isResume && surface.isSurfaceReady) {
                        surface.nDoFrame(surface.nativePtr)
                    }
                }
            }
            return true
        }
    }

    private enum class MsgType {
        INIT,
        SURFACE_CREATE,
        SURFACE_DESTROY,
        DO_FRAME
    }

    companion object {
        init {
            System.loadLibrary("and_egl")
        }
    }
}