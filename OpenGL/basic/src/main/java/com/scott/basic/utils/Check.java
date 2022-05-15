package com.scott.basic.utils;

public class Check {

    public static class SClick {

        private static final long DEFAULT_INTERVAL = 500L;

        private static long lastClickTime = 0L;

        /**
         * @return 两次点击之间的时间间隔是否小于500ms
         */
        public static boolean isFastClick() {
            long time = System.currentTimeMillis();
            long timeD = time - lastClickTime;
            if (0 < timeD && timeD < DEFAULT_INTERVAL) {
                return true;
            }
            lastClickTime = time;
            return false;
        }


        /**
         * @return 两次点击之间的时间间隔是否小于500ms
         */
        public static boolean isFastClick(long interval) {
            long time = System.currentTimeMillis();
            long timeD = time - lastClickTime;
            if (0 < timeD && timeD < interval) {
                return true;
            }
            lastClickTime = time;
            return false;
        }

    }
}
