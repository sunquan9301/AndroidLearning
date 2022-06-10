package com.scott;

import android.content.res.AssetManager;

import com.scott.basic.AppContext;
import com.scott.basic.shaders.IRender;
import com.scott.nativecode.IType;
import com.scott.nativecode.NativeRenderJni;

/**
 * 1. 相比较NativeRender，V2不传入vertexShaderPath和fragmentShaderPath
 * 2. V2会根据type在cpp层面自己定义ShaderPath；即 ShaderPath数据具体的Demo类
 */
public class NativeRenderV2 implements IRender {
    private int assignType = IType.AssignType.ASSIGN_LEARN_OPENGL_TRIANGLE_SIMPLE;

    public NativeRenderV2(int assignType) {
        this.assignType = assignType;
    }

    @Override
    public void init() {
        AssetManager assetManager = AppContext.basicContext.getAssets();
        NativeRenderJni.getIns().initV2(assetManager, assignType);
    }

    @Override
    public void onSurfaceCreated() {
        NativeRenderJni.getIns().onSurfaceCreated();
    }

    @Override
    public void onSurfaceChanged(int width, int height) {
        NativeRenderJni.getIns().onSurfaceChanged(width,height);
    }

    @Override
    public void onDrawFrame() {
        NativeRenderJni.getIns().onDrawFrame();

    }

    @Override
    public void onSurfaceDestroyed() {
        NativeRenderJni.getIns().onDestroy();
    }
}
