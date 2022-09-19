package com.github.carver.androidegl.egl

import android.graphics.SurfaceTexture
import android.view.Surface
import android.view.SurfaceHolder
import android.view.SurfaceView
import android.view.TextureView

interface ISurfaceCallback {
    fun onSurfaceCreated(surface: Surface)

    fun onSurfaceDestroyed()

    companion object {

        fun adapter(surfaceView: SurfaceView, callback: ISurfaceCallback) {
            surfaceView.holder.addCallback(object : SurfaceHolder.Callback {
                override fun surfaceCreated(holder: SurfaceHolder) {
                }

                override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) {
                    callback.onSurfaceCreated(holder.surface)
                }

                override fun surfaceDestroyed(holder: SurfaceHolder) {
                    callback.onSurfaceDestroyed()
                }

            })
        }

        fun adapter(textureView: TextureView, callback: ISurfaceCallback) {
            textureView.surfaceTextureListener = object : TextureView.SurfaceTextureListener {
                override fun onSurfaceTextureAvailable(texture: SurfaceTexture, p1: Int, p2: Int) {
                    callback.onSurfaceCreated(Surface(texture))
                }

                override fun onSurfaceTextureSizeChanged(texture: SurfaceTexture, width: Int, height: Int) {
                }

                override fun onSurfaceTextureDestroyed(texture: SurfaceTexture): Boolean {
                    callback.onSurfaceDestroyed()
                    return true
                }

                override fun onSurfaceTextureUpdated(texture: SurfaceTexture) {
                    // do nothing
                }
            }
        }
    }
}