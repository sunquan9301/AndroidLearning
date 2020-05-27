package com.sun.presentation.utils;

import android.view.View;

import java.util.Collection;
import java.util.Map;

/**
 * 辅助判断
 * 1.检查各种格式
 * 2.检查交互
 */
public class Check {
    public static final int INVALID_TIME = 100;
    public static final int INVALID_TIME_LONG = 500;

    public static boolean isEmpty(CharSequence str) {
        return isNull(str) || str.length() == 0;
    }

    public static boolean isNotEmpty(CharSequence str) {
        return !isEmpty(str);
    }

    public static boolean isEmpty(Object[] os) {
        return isNull(os) || os.length == 0;
    }

    public static boolean isEmpty(Collection<?> l) {
        return isNull(l) || l.isEmpty();
    }

    public static boolean isEmpty(Map<?, ?> m) {
        return isNull(m) || m.isEmpty();
    }

    public static boolean isNull(Object o) {
        return o == null;
    }

    private static String trim(String s) {
        if (s == null) {
            return s;
        }
        return s.replaceAll("[ 　]+", "");
    }

    public static void checkQuickClick(View view, int time) {
        switchClickState(false, view);
        view.postDelayed(() -> {
            switchClickState(true, view);
        }, time);
    }

    public static boolean checkUrl(String url) {
        boolean reault = false;
        if (url != null) {
            if (url.toLowerCase().startsWith("http:") || url.toLowerCase().startsWith("https:")
                    || url.toLowerCase().startsWith("rtsp:") || url.toLowerCase().startsWith("ftp:")) {
                reault = true;
            }
        }
        return reault;
    }

    public static boolean isipv4(String ipv4) {
        if (ipv4 == null || ipv4.length() == 0) {
            return false;//字符串为空或者空串
        }
        String[] parts = ipv4.split("\\.");
        if (parts.length != 4) {
            return false;
        }
        for (int i = 0; i < parts.length; i++) {
            try {
                int n = Integer.parseInt(parts[i]);
                if (n < 0 || n > 255) {
                    return false;
                }
            } catch (NumberFormatException e) {
                return false;
            }
        }
        return true;
    }

    public static boolean isUrlOk(String url) {
        return url != null && (url.startsWith("http://") || url.startsWith("https://"));
    }

    public static void switchClickState(boolean isEnable, View view) {
        view.setEnabled(isEnable);
        view.setClickable(isEnable);
    }

}