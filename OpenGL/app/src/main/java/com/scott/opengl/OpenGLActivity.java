package com.scott.opengl;

import android.os.Bundle;
import android.view.WindowManager;
import android.widget.RelativeLayout;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.scott.nativecode.IType;
import com.scott.nativecode.NativeRenderJni;

public class OpenGLActivity extends AppCompatActivity {

    RelativeLayout container;
    DefaultGLSurfaceView glSurfaceView;
    RelativeLayout btnOpts;
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS);
        setContentView(R.layout.activity_opengl);
        initViews();
        bindActions();
    }

    private void bindActions() {
        findViewById(R.id.btn_up).setOnClickListener(view-> NativeRenderJni.getIns().onOptClick(IType.OptType.OPT_UP));
        findViewById(R.id.btn_down).setOnClickListener(view-> NativeRenderJni.getIns().onOptClick(IType.OptType.OPT_DOWN));
        findViewById(R.id.btn_left).setOnClickListener(view-> NativeRenderJni.getIns().onOptClick(IType.OptType.OPT_LEFT));
        findViewById(R.id.btn_right).setOnClickListener(view-> NativeRenderJni.getIns().onOptClick(IType.OptType.OPT_RIGHT));
        findViewById(R.id.btn_rotate_left).setOnClickListener(view-> NativeRenderJni.getIns().onOptClick(IType.OptType.OPT_ROTATE_LEFT));
        findViewById(R.id.btn_rotate_right).setOnClickListener(view-> NativeRenderJni.getIns().onOptClick(IType.OptType.OPT_ROTATE_RIGHT));
    }

    private void initViews() {
        int demoType = getIntent().getIntExtra("demoType", IType.AssignType.ASSIGN_LEARN_OPENGL_TRIANGLE_SIMPLE);
        glSurfaceView = new DefaultGLSurfaceView(this, demoType);
        container = findViewById(R.id.rl_container);
        container.addView(glSurfaceView);
        btnOpts = findViewById(R.id.rl_opts);
        btnOpts.bringToFront();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        glSurfaceView.onDestroy();
    }
}
