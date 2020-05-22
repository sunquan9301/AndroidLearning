package com.sun.presentation.components;

import android.app.Application;

/**
 * @author sunquan
 * sunquan@bitstarlight.com
 * @date 2018/10/17
 **/
public class PresentationApp {
    private static volatile PresentationApp presentationApp = new PresentationApp();


    public static PresentationApp inst() {
        return presentationApp;
    }


    private Application applicationContext;

    public void init(Application context) {
        this.applicationContext = context;
    }

    public Application getApp() {
        return applicationContext;
    }
}
