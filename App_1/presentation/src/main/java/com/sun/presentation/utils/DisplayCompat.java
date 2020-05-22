package com.sun.presentation.utils;

import android.annotation.TargetApi;
import android.graphics.Point;
import android.os.Build;
import android.view.Display;

public final class DisplayCompat {
    private interface DisplayImpl {
        int getWidth(Display display);

        int getHeight(Display display);
    }
    private static final DisplayImpl IMPL;

    static {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB_MR2) {
            IMPL = new HoneyCombMR2DisplayImpl();
        } else {
            IMPL = new BaseDisplayImpl();
        }
    }

    public static int getWidth(Display display) {
        return IMPL.getWidth(display);
    }

    public static int getHeight(Display display) {
        return IMPL.getHeight(display);
    }

    private DisplayCompat() {
    }

    @SuppressWarnings("deprecation")
    private static class BaseDisplayImpl implements DisplayImpl {
        @Override
        public int getWidth(Display display) {
            return display.getWidth();
        }

        @Override
        public int getHeight(Display display) {
            return display.getHeight();
        }
    }

    @TargetApi(Build.VERSION_CODES.HONEYCOMB_MR2)
    private static class HoneyCombMR2DisplayImpl implements DisplayImpl {
        private Point mPoint = new Point();

        @Override
        public int getWidth(Display display) {
            display.getSize(mPoint);
            return mPoint.x;
        }

        @Override
        public int getHeight(Display display) {
            display.getSize(mPoint);
            return mPoint.y;
        }
    }
}
