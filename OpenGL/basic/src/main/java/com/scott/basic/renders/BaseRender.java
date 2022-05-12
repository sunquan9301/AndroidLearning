package com.scott.basic.renders;

import static android.opengl.GLES20.glViewport;

import android.opengl.GLSurfaceView;


import com.scott.basic.shaders.IShaderProgram;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class BaseRender implements GLSurfaceView.Renderer {
    public IShaderProgram iShaderProgram;
    public BaseRender(IShaderProgram shader) {
        this.iShaderProgram = shader;
        iShaderProgram.initAttributions();
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        iShaderProgram.bindShaderSource();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        glViewport(0, 0, width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        iShaderProgram.onDraw();
    }
}
