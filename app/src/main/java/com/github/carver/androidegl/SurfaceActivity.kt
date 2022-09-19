package com.github.carver.androidegl

import android.os.Bundle
import android.view.SurfaceView
import android.view.TextureView
import android.view.View
import android.view.ViewGroup
import androidx.appcompat.app.AppCompatActivity
import com.github.carver.androidegl.egl.NativeRenderer

class SurfaceActivity : AppCompatActivity() {

    private val renderer = NativeRenderer()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val viewType = intent.getIntExtra("viewType", 0)
        val contentView: View = if (viewType == 0) {
            val surfaceView = SurfaceView(this)
            renderer.setView(surfaceView)
            surfaceView
        } else {
            val textureView = TextureView(this)
            renderer.setView(textureView)
            textureView
        }
        contentView.layoutParams = ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT)
        setContentView(contentView)
    }

    override fun onResume() {
        super.onResume()
        renderer.onResume()
    }

    override fun onPause() {
        super.onPause()
        renderer.onPause()
    }
}