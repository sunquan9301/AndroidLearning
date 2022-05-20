package com.scott.nativecode;

import android.content.res.AssetManager;

/**
 * 1. 添加NativeRenderJNI
 * 2. add CMakeLists
 * 3. add cpp code
 * 4. NativeLoaderLibrary
 */
public class NativeRenderJni {
    public native void init(AssetManager assetManager, int assignType, String vertexShaderAssetName, String fragmentShaderAssetName);
    public native void onSurfaceCreated();
    public native void onSurfaceChanged(int width, int height);
    public native void onDrawFrame();
    public native void onDestroy();
}

