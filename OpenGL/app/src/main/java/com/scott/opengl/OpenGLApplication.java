package com.scott.opengl;

import android.app.Application;
import android.content.Context;

public class OpenGLApplication extends Application {
    public static Context appContext;
    @Override
    public void onCreate() {
        super.onCreate();
        appContext = this;
    }
}
