package com.scott.opengl;

import android.os.Bundle;
import android.view.WindowManager;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.scott.nativecode.IAssignType;

public class OpenGLActivity extends AppCompatActivity {

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS);
        int demoType = getIntent().getIntExtra("demoType", IAssignType.LearnOpenGL.ASSIGN_LEARN_OPENGL_TRIANGLE_SIMPLE);
        setContentView(new DefaultGLSurfaceView(this,demoType));
    }
}
