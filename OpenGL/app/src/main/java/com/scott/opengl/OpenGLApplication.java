package com.scott.opengl;

import android.app.Application;
import android.content.Context;

import com.scott.NativeLibsLoader;
import com.scott.basic.AppContext;

public class OpenGLApplication extends Application {
    public static Context appContext;
    @Override
    public void onCreate() {
        super.onCreate();
        appContext = this;
        AppContext.basicContext = appContext;
        NativeLibsLoader.loadLibrary();
    }
}
