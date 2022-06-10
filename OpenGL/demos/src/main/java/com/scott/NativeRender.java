package com.scott;

import android.content.res.AssetManager;

import com.scott.basic.AppContext;
import com.scott.basic.shaders.IRender;
import com.scott.nativecode.IType;
import com.scott.nativecode.NativeRenderJni;

public class NativeRender implements IRender {
    String vertexShaderAssetName;
    String fragmentShaderAssetName;

    public NativeRender(String vertexShaderAssetName,String fragmentShaderAssetName) {
        this.vertexShaderAssetName = vertexShaderAssetName;
        this.fragmentShaderAssetName = fragmentShaderAssetName;
    }

    @Override
    public void init() {
        AssetManager assetManager = AppContext.basicContext.getAssets();
        NativeRenderJni.getIns().init(assetManager, IType.AssignType.ASSIGN_LEARN_OPENGL_SHADER_SIMPLE_SHADER,vertexShaderAssetName,fragmentShaderAssetName);
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
