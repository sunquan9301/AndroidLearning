package com.scott;

import android.content.res.AssetManager;

import com.scott.basic.AppContext;
import com.scott.basic.shaders.IRender;
import com.scott.nativecode.IAssignType;
import com.scott.nativecode.NativeRenderJni;

public class NativeRender implements IRender {
    NativeRenderJni nativeRenderJni;
    String vertexShaderAssetName;
    String fragmentShaderAssetName;

    public NativeRender(String vertexShaderAssetName,String fragmentShaderAssetName) {
        this.vertexShaderAssetName = vertexShaderAssetName;
        this.fragmentShaderAssetName = fragmentShaderAssetName;
    }

    @Override
    public void init() {
        AssetManager assetManager = AppContext.basicContext.getAssets();
        nativeRenderJni = new NativeRenderJni();
        nativeRenderJni.init(assetManager, IAssignType.LearnOpenGL.ASSIGN_LEARN_OPENGL_SHADER_SIMPLE_SHADER,vertexShaderAssetName,fragmentShaderAssetName);
    }

    @Override
    public void onSurfaceCreated() {
        nativeRenderJni.onSurfaceCreated();
    }

    @Override
    public void onSurfaceChanged(int width, int height) {
        nativeRenderJni.onSurfaceChanged(width,height);
    }

    @Override
    public void onDrawFrame() {
        nativeRenderJni.onDrawFrame();

    }

    @Override
    public void onSurfaceDestroyed() {
        nativeRenderJni.onDestroy();
    }
}
