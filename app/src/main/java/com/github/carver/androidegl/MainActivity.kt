package com.github.carver.androidegl

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        findViewById<View>(R.id.show_surface_view).setOnClickListener {
            startSurfaceActivity(0)
        }

        findViewById<View>(R.id.show_texture_view).setOnClickListener {
            startSurfaceActivity(1)
        }
    }

    private fun startSurfaceActivity(viewType: Int) {
        val intent = Intent(this, SurfaceActivity::class.java).apply {
            putExtra("viewType", viewType)
        }
        startActivity(intent)
    }
}