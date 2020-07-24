package com.scott.views

import android.os.Build
import android.os.Bundle
import android.os.Environment
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import java.io.File


class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_cardview)

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT) {
            val files: Array<File> = getExternalFilesDirs(Environment.MEDIA_MOUNTED)
            for (file in files) {
                Log.e("file_dir", file.getAbsolutePath())
            }
        }

    }
}