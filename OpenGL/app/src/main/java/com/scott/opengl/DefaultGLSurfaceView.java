package com.scott.opengl;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.SurfaceHolder;

import com.scott.NativeRender;
import com.scott.NativeRenderV2;
import com.scott.basic.renders.BaseWrapRender;
import com.scott.nativecode.IAssignType;

public class DefaultGLSurfaceView extends GLSurfaceView {
    private BaseWrapRender baseWrapRender;
    public DefaultGLSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public DefaultGLSurfaceView(Context context,int demoType) {
        this(context,null);
        //使用opengl es 3以上版本
        setEGLContextClientVersion(3);
        // Assign our renderer.
//        glSurfaceView.setRenderer(new BaseRender(new DefaultRenderES3_0()));
//        baseWrapRender = new BaseWrapRender(new NativeRender("hello_triangle_vertex_shader.glsl","hello_triangle_fragment_shader.glsl"));
        baseWrapRender = new BaseWrapRender(new NativeRenderV2(demoType));
        setRenderer(baseWrapRender);
        //RENDERMODE_CONTINUOUSLY 1s 60帧
//        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);
        // surface is created, or when requestRender is called.
        setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
    }

    public void onDestroy(){
        baseWrapRender.onSurfaceDestroyed();
    }
}
