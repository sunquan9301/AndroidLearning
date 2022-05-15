package com.scott;

import com.scott.basic.shaders.IRender;
import com.scott.nativecode.NativeRenderJni;

public class NativeRender implements IRender {
    NativeRenderJni nativeRenderJni;
    @Override
    public void init() {
        nativeRenderJni = new NativeRenderJni();
        nativeRenderJni.init();
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
}
