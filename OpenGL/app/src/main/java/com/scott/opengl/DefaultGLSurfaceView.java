package com.scott.opengl;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.SurfaceHolder;

import com.scott.NativeRender;
import com.scott.basic.renders.BaseWrapRender;

public class DefaultGLSurfaceView extends GLSurfaceView {
    BaseWrapRender baseWrapRender;
    public DefaultGLSurfaceView(Context context) {
        this(context,null);
    }

    public DefaultGLSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    private void init() {
        // Request an OpenGL ES 2.0 compatible context.
        setEGLContextClientVersion(3);
        // Assign our renderer.
//        glSurfaceView.setRenderer(new BaseRender(new DefaultRenderES3_0()));
        baseWrapRender = new BaseWrapRender(new NativeRender("hello_triangle_vertex_shader.glsl","hello_triangle_fragment_shader.glsl"));
        setRenderer(baseWrapRender);
        setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        super.surfaceDestroyed(holder);
        baseWrapRender.onSurfaceDestroyed();
    }
}