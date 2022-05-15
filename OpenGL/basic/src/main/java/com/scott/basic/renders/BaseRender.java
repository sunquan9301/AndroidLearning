package com.scott.basic.renders;

import android.opengl.GLSurfaceView;
import android.util.Log;


import com.scott.basic.shaders.IRender;
import com.scott.basic.utils.Check;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class BaseRender implements GLSurfaceView.Renderer {
    public static final String TAG =  "BaseRender";
    public IRender iRender;
    public BaseRender(IRender shader) {
        this.iRender = shader;
        iRender.init();
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        Log.i(TAG,"onSurfaceCreated");
        iRender.onSurfaceCreated();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        if(Check.SClick.isFastClick(200)){
            return;
        }
        Log.i(TAG,"onSurfaceChanged width = "+width+";height = "+height);
        iRender.onSurfaceChanged(width,height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
//        Log.i(TAG,"onDrawFrame");
        iRender.onDrawFrame();
    }
}
