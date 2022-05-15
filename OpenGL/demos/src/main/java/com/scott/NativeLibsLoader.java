package com.scott;

import android.util.Log;

import java.util.ArrayList;
import java.util.List;

public class NativeLibsLoader {
    private static boolean sLibraryLoaded = false;
    private static final String TAG = "NativeLibsLoader";
    private static ILibraryLoader mLibraryLoader;

    public synchronized static void loadLibrary() {
        if (sLibraryLoaded) {
            return;
        }
        List<String> list = new ArrayList<>();
        list.add("medianative");
        if (mLibraryLoader != null) {
            mLibraryLoader.onLoadNativeLibs(list);
            sLibraryLoaded = true;
            return;
        }
        for (String soName : list) {
            safeLoadSo(soName);
        }
        sLibraryLoaded = true;
    }

    public static void safeLoadSo(String soName) {
        try {
            System.loadLibrary(soName);
        } catch (Throwable ignore) {
            Log.e(TAG, "loadLibrary Load native library failed : " + ignore.getMessage());
        }

    }

    public static void setLibraryLoad(ILibraryLoader iLibraryLoader) {
        mLibraryLoader = iLibraryLoader;
    }

    public interface ILibraryLoader {
        /**
         * @param list 需要加载的lib库列表
         */
        void onLoadNativeLibs(List<String> list);
    }
}
