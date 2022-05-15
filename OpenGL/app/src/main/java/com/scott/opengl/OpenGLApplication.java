package com.scott.opengl;

import android.app.Application;
import android.content.Context;

import com.scott.NativeLibsLoader;

public class OpenGLApplication extends Application {
    public static Context appContext;
    @Override
    public void onCreate() {
        super.onCreate();
        appContext = this;
        NativeLibsLoader.loadLibrary();
    }
}
